﻿/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IL2C - A translator for ECMA-335 CIL/MSIL to C language.
// Copyright (c) 2016-2019 Kouji Matsui (@kozy_kekyo, @kekyo2)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections;

namespace System.Runtime.InteropServices
{
    public abstract class NativeAttribute : Attribute
    {
        protected NativeAttribute(string includeFileName)
        {
            this.IncludeFileName = includeFileName;
        }

        internal NativeAttribute(object arg0, IDictionary props)
        {
            this.IncludeFileName = (string)arg0;
            this.SymbolName = (string)props["SymbolName"];
            this.Compilation = (CompilationOption)props["Compilation"];
        }

        public string IncludeFileName { get; }
        public string SymbolName { get; set; }
        public CompilationOption Compilation { get; set; }
    }
}
