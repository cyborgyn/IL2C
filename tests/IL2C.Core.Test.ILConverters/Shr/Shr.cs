﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace IL2C.ILConverters
{
    // Arithmetic Shift right (with sign)
    // Warning!!! MSIL always operates for bit storage on Int32, or Int64
    // and as it seems, smaller unsigned values (uint8 & uint16) will never
    // be able to set the int32 highest bit => they will operate as logical shift right.
    // On the other hand: uint32 and uint64 are still operated as arithmetic shift.
    [TestCase((byte)123, "ShrByte", (byte)123, 0)]
    [TestCase((byte)0, "ShrByte", (byte)1, 1)]
    [TestCase((byte)(Byte.MaxValue - 1) / 2, "ShrByte", (byte)Byte.MaxValue, 1)]
    [TestCase((byte)(Byte.MaxValue - 1) / 4, "ShrByte", (byte)Byte.MaxValue, 2)]
    
    [TestCase((sbyte)123, "ShrSByte", (sbyte)123, 0)]
    [TestCase((sbyte)0, "ShrSByte", (sbyte)1, 1)]
    [TestCase((sbyte)-1, "ShrSByte", (sbyte)-1, 1)]
    [TestCase((sbyte)-1, "ShrSByte", (sbyte)-5, 10)]
    [TestCase((sbyte)(SByte.MaxValue - 1) / 2, "ShrSByte", (sbyte)SByte.MaxValue, 1)]
    [TestCase((sbyte)(SByte.MaxValue - 1) / 4, "ShrSByte", (sbyte)SByte.MaxValue, 2)]

    [TestCase((short)123, "ShrShort", (short)123, 0)]
    [TestCase((short)0, "ShrShort", (short)1, 1)]
    [TestCase((short)-1, "ShrShort", (short)-1, 1)]
    [TestCase((short)-1, "ShrShort", (short)-5, 10)]
    [TestCase((short)(Int16.MaxValue - 1) / 2, "ShrShort", (short)Int16.MaxValue, 1)]
    [TestCase((short)(Int16.MaxValue - 1) / 4, "ShrShort", (short)Int16.MaxValue, 2)]

    [TestCase((ushort)123, "ShrUshort", (ushort)123, 0)]
    [TestCase((ushort)0, "ShrUshort", (ushort)1, 1)]
    [TestCase((ushort)(UInt16.MaxValue - 1) / 2, "ShrUshort", (ushort)UInt16.MaxValue, 1)]
    [TestCase((ushort)(UInt16.MaxValue - 1) / 4, "ShrUshort", (ushort)UInt16.MaxValue, 2)]

    [TestCase((int)123, "ShrInt", (int)123, 0)]
    [TestCase((int)0, "ShrInt", (int)1, 1)]
    [TestCase((int)-1, "ShrInt", (int)-1, 1)]
    [TestCase((int)-1, "ShrInt", (int)-5, 10)]
    [TestCase((int)(Int32.MaxValue - 1) / 2, "ShrInt", (int)Int32.MaxValue, 1)]
    [TestCase((int)(Int32.MaxValue - 1) / 4, "ShrInt", (int)Int32.MaxValue, 2)]

    [TestCase((uint)123, "ShrUInt", (uint)123, 0)]
    [TestCase((uint)0, "ShrUInt", (uint)1, 1)]
    [TestCase((uint)UInt32.MaxValue, "ShrUInt", (uint)UInt32.MaxValue, 1)]
    [TestCase((uint)UInt32.MaxValue, "ShrUInt", (uint)UInt32.MaxValue, 2)]

    [TestCase((long)123, "ShrLong", (long)123, 0)]
    [TestCase((long)0, "ShrLong", (long)1, 1)]
    [TestCase((long)-1, "ShrLong", (long)-1, 1)]
    [TestCase((long)-1, "ShrLong", (long)-5, 10)]
    [TestCase((long)(Int64.MaxValue - 1) / 2, "ShrLong", (long)Int64.MaxValue, 1)]
    [TestCase((long)(Int64.MaxValue - 1) / 4, "ShrLong", (long)Int64.MaxValue, 2)]

    [TestCase((ulong)123, "ShrUlong", (ulong)123, 0)]
    [TestCase((ulong)0, "ShrUlong", (ulong)1, 1)]
    [TestCase((ulong)UInt64.MaxValue, "ShrUlong", (ulong)UInt64.MaxValue, 1)]
    [TestCase((ulong)UInt64.MaxValue, "ShrUlong", (ulong)UInt64.MaxValue, 2)]

    //[TestCase((int)(Int32.MaxValue - 1) / 2, "ShrIntByIntptr", (int)Int32.MaxValue, 1)]
    //[TestCase((int)(Int32.MaxValue - 1) / 4, "ShrIntByIntptr", (int)Int32.MaxValue, 2)]

    //[TestCase((long)(Int64.MaxValue - 1) / 2, "ShrUlongByUIntptr", (long)Int64.MaxValue, 1)]
    //[TestCase((long)(Int64.MaxValue - 1) / 4, "ShrUlongByUIntptr", (long)Int64.MaxValue, 2)]
    public sealed class Shr
    {
        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern byte ShrByte(byte v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern sbyte ShrSByte(sbyte v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern short ShrShort(short v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern ushort ShrUshort(ushort v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern int ShrInt(int v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern uint ShrUInt(uint v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern long ShrLong(long v, int num);

        [MethodImpl(MethodImplOptions.ForwardRef)]
        public static extern ulong ShrUlong(ulong v, int num);

        //[MethodImpl(MethodImplOptions.ForwardRef)]
        //public static extern int ShrIntByIntptr(int v, IntPtr num);

        //[MethodImpl(MethodImplOptions.ForwardRef)]
        //public static extern ulong ShrUlongByUIntptr(ulong v, UIntPtr num);
    }
}
