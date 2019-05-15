﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IL2C.ArtifactCollector
{
    internal static class Collectors
    {
        public static Task RecreateDirectoryAsync(string path)
        {
            return Task.Run(() =>
            {
                if (Directory.Exists(path))
                {
                    Directory.Move(path, path + ".old");
                    Directory.Delete(path + ".old", true);
                }

                Directory.CreateDirectory(path);
            });
        }

        private static Task CopyFileAsync(string from, string to)
        {
            return Task.Run(() =>
            {
                var toDirectory = Path.GetDirectoryName(to);
                var count = 10;
                while (!Directory.Exists(toDirectory))
                {
                    try
                    {
                        Directory.CreateDirectory(toDirectory);
                    }
                    catch (IOException)
                    {
                        count--;
                        if (count <= 0)
                        {
                            throw;
                        }
                    }
                }

                File.Copy(from, to, true);
            });
        }

        private static async Task CopyArtifactsAsync(string artifactsDir, string targetDirectoryPath, bool includeCommitId)
        {
            // 0.4.70-beta+e458a2c794 --> 0.4.70-beta.e458a2c794
            var semver2Ids = ThisAssembly.AssemblyInformationalVersion.Split('+');
            var semver2Id = string.Join(".", semver2Ids);

            var nupkgPaths = Directory.GetFiles(targetDirectoryPath, "*.nupkg", SearchOption.AllDirectories).
                Where(p => !includeCommitId || p.Contains(semver2Id)).    // HACK: Check contains current semver2 id
                GroupBy(p => p.Replace(".symbols", string.Empty)).
                Select(g => Tuple.Create(g.Key, g.OrderByDescending(p => p.Length).ToArray())).
                ToDictionary(entry => entry.Item1, entry => entry.Item2);

            foreach (var nupkgPath in nupkgPaths.Select(entry => entry.Value.First()))
            {
                var sanitized = nupkgPath.Replace(".symbols", string.Empty);
                sanitized = (semver2Ids.Length >= 2) ?
                    sanitized.Replace("." + semver2Ids[1], string.Empty) :    // HACK: Drop semver2 id
                    sanitized;
                var targetNupkgFileName = Path.GetFileName(sanitized);
                var targetPath = Path.Combine(artifactsDir, targetNupkgFileName);

                if (File.Exists(targetPath))
                {
                    File.Move(targetPath, targetPath + ".orig");
                    File.Delete(targetPath + ".orig");
                }

                await CopyFileAsync(nupkgPath, targetPath);

                Program.WriteLine(
                    "AritfactCollector: Package collected: File={0}, Built={1}",
                    targetNupkgFileName,
                    Path.GetFileName(nupkgPath));
            }
        }

        public static async Task BuildCsprojAndCollectArtifactsAsync(string solutionDir, string artifactsDir, IEnumerable<string> csprojPaths)
        {
            foreach (var path in csprojPaths)
            {
                var workingPath = Path.GetDirectoryName(path);
                var result = await Executor.ExecuteAsync(
                    workingPath,
                    new string[0],
                    "dotnet",
                    "pack", "--no-build", "--configuration", "Release", "--include-symbols", "/p:NoPackageAnalysis=true", $"\"{path}\"");
                Program.WriteLine(result.Item2);
                if (result.Item1 != 0)
                {
                    throw new Exception($"Csproj failed: Path={path}, ExitCode={result.Item2}");
                }
            }

            await Task.WhenAll(csprojPaths.
                Select(path => Path.GetDirectoryName(Path.GetFullPath(path))).
                Distinct().
                Select(path => CopyArtifactsAsync(artifactsDir, path, true)));
        }

        public static async Task BuildNuspecAndCollectArtifactsAsync(string solutionDir, string artifactsDir, IEnumerable<string> nuspecPaths)
        {
            var nugetPath = Path.Combine(solutionDir, ".nuget", "nuget.exe");

            foreach (var path in nuspecPaths)
            {
                var outputDirectory = Path.Combine(Path.GetDirectoryName(path), "bin", "Release");
                var workingPath = Path.GetDirectoryName(path);
                var result = await Executor.ExecuteAsync(
                    workingPath,
                    new string[0],
                    nugetPath,
                    "pack", "-Version", ThisAssembly.AssemblyInformationalVersion, "-NoPackageAnalysis", "-Prop", "Configuration=Release", "-OutputDirectory", $"\"{outputDirectory}\"", $"\"{path}\"");
                Program.WriteLine(result.Item2);
                if (result.Item1 != 0)
                {
                    throw new Exception($"Nuspec failed: Path={path}, ExitCode={result.Item1}");
                }
            }

            await Task.WhenAll(nuspecPaths.
                Select(path => Path.GetDirectoryName(Path.GetFullPath(path))).
                Distinct().
                Select(path => CopyArtifactsAsync(artifactsDir, path, false)));
        }

        private static async Task CopyResourceWithReplacementsAsync(string resourceName, string path, IReadOnlyDictionary<string, string> replacements)
        {
            using (var sr = new StreamReader(
                typeof(Collectors).Assembly.GetManifestResourceStream(resourceName),
                Encoding.UTF8, true))
            {
                var arduinoProperties = new StringBuilder(await sr.ReadToEndAsync());
                foreach (var entry in replacements)
                {
                    arduinoProperties.Replace(entry.Key, entry.Value);
                }
                File.WriteAllText(path, arduinoProperties.ToString(), Encoding.UTF8);
            }
        }

        public static async Task CollectArduinoArtifactsAsync(string solutionDir, string artifactsDir)
        {
            var arduinoBasePath = Path.Combine(artifactsDir, "Arduino");
            await RecreateDirectoryAsync(arduinoBasePath);

            await CopyResourceWithReplacementsAsync(
                "IL2C.ArtifactCollector.Arduino.properties",
                Path.Combine(arduinoBasePath, "library.properties"),
                new Dictionary<string, string>
                {
                    { "{version}", ThisAssembly.AssemblyFileVersion },
                    { "{semver2}", ThisAssembly.AssemblyInformationalVersion }
                });
 
            var fromIncludeDir = Path.Combine(solutionDir, "IL2C.Runtime", "include");
            var toIncludeDir = Path.Combine(arduinoBasePath, "include");
            await Task.WhenAll(
                Directory.EnumerateFiles(fromIncludeDir, "*.h", SearchOption.AllDirectories).
                Select(path => CopyFileAsync(path, Path.Combine(toIncludeDir, path.Substring(fromIncludeDir.Length + 1)))));

            var fromSrcDir = Path.Combine(solutionDir, "IL2C.Runtime", "src");
            var toSrcDir = Path.Combine(arduinoBasePath, "src");
            await Task.WhenAll(
                Directory.EnumerateFiles(fromSrcDir, "*.c", SearchOption.AllDirectories).
                Concat(Directory.EnumerateFiles(fromSrcDir, "*.h", SearchOption.AllDirectories)).
                Select(path => CopyFileAsync(path, Path.Combine(toSrcDir, path.Substring(fromSrcDir.Length + 1)))));
        }
    }
}
