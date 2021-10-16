/////////////////////////////////////////////////////////////////////////////////////////////////
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

#ifndef System_StringFunctions_H__
#define System_StringFunctions_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////
// String special functions

#if defined(IL2C_USE_LINE_INFORMATION)
extern System_String* il2c_new_string__(const wchar_t* pString, const char* pFile, int line);
extern System_String* il2c_new_string_with_length__(const wchar_t* pString, uint32_t length, const char* pFile, int line);
extern System_String* il2c_new_string_from_utf8__(const char* pUtf8String, const char* pFile, int line);
#define il2c_new_string(pString) il2c_new_string__(pString, __FILE__, __LINE__)
#define il2c_new_string_with_length(pString, length) il2c_new_string_with_length__(pString, length, __FILE__, __LINE__)
#define il2c_new_string_from_utf8(pUtf8String) il2c_new_string_from_utf8__(pUtf8String, __FILE__, __LINE__)
#else
extern System_String* il2c_new_string__(const wchar_t* pString);
extern System_String* il2c_new_string_with_length__(const wchar_t* pString, uint32_t length);
extern System_String* il2c_new_string_from_utf8__(const char* pUtf8String);
#define il2c_new_string(pString) il2c_new_string__(pString)
#define il2c_new_string_with_length(pString, length) il2c_new_string_with_length__(pString, length)
#define il2c_new_string_from_utf8(pUtf8String) il2c_new_string_from_utf8__(pUtf8String)
#endif

extern const wchar_t* il2c_c_str(System_String* str);

extern int32_t il2c_get_utf8_length(const char* pUtf8String, bool detectInvalidChars);
extern wchar_t* il2c_utf16_from_utf8_and_get_last(wchar_t* pDest, const char* pUtf8String);

#define IL2C_STRING_FORMAT_SUCCEEDED (0)
#define IL2C_STRING_FORMAT_INVALID (-1)
#define IL2C_STRING_FORMAT_ARGUMENT_ABSOLUTE_LIMIT (-2)

typedef int8_t (*IL2C_FORMAT_TOKEN_WRITER)(
    const wchar_t* pTokenFrom, uint32_t tokenLength, void* pState);
typedef int8_t(*IL2C_FORMAT_ARGUMENT_WRITER)(
    uint16_t argumentIndex, const wchar_t* pFormatFrom, uint32_t formatLength, void* pState);
extern int8_t il2c_format_string__(
    const wchar_t* pFormat,
    IL2C_FORMAT_TOKEN_WRITER pWriter, IL2C_FORMAT_ARGUMENT_WRITER pArgumentWriter,
    void* pState);

/////////////////////////////////////////////////
// Literal string generator macro.

typedef const struct
{
    // IL2C_REF_HEADER
    void* pNext;                  // Const string will not collect by GC, so this link is always NULL.
    IL2C_RUNTIME_TYPE type;       // Const string always fixed runtime type pointer from "System_String_RUNTIME_TYPE__."
    interlock_t characteristic;   // Const string always marked (IL2C_CHARACTERISTIC_CONST | IL2C_CHARACTERISTIC_INITIALIZED)

    // Instance's vptr
    System_String_VTABLE_DECL__* vptr0__;   // Const string always fixed VTable pointer from "System_String_VTABLE__."

    wchar_t* string_body__;
} IL2C_CONST_STRING_DECL;

#define IL2C_CONST_STRING(name, string_body) \
    static IL2C_CONST_STRING_DECL name##_CONST_STRING__ = { \
        NULL, il2c_typeof(System_String), /* IL2C_CHARACTERISTIC_CONST | IL2C_CHARACTERISTIC_INITIALIZED */ (interlock_t)0xc0000000UL, &System_String_VTABLE__, string_body }; \
    System_String* const name = ((System_String*)&(name##_CONST_STRING__.vptr0__))

// C4197: "top-level volatile in cast is ignored" is caused by IL2C_CONST_STRING()
#if defined(_MSC_VER)
#pragma warning(disable:4197)
#endif

#ifdef __cplusplus
}
#endif

#endif
