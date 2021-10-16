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

#ifndef System_String_H__
#define System_String_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////
// System.String

typedef struct System_String System_String;

typedef System_Object_VTABLE_DECL__ System_String_VTABLE_DECL__;

struct System_String
{
    System_String_VTABLE_DECL__* vptr0__;
    const wchar_t* string_body__;
};

extern System_String_VTABLE_DECL__ System_String_VTABLE__;

IL2C_DECLARE_RUNTIME_TYPE(System_String);

extern System_String** System_String_Empty_REF__;

typedef struct System_IFormatProvider System_IFormatProvider;

extern /* virtual */ System_String* System_String_ToString(System_String* this__);
extern bool System_String_Equals__System_String(System_String* this__, System_String* obj);
extern /* virtual */ bool System_String_Equals__System_Object(System_String* this__, System_Object* obj);
extern /* virtual */ int32_t System_String_GetHashCode(System_String* this__);
extern /* static */ System_String* System_String_Concat__System_String_System_String(System_String* str0, System_String* str1);
extern /* static */ System_String* System_String_Concat__System_Object_System_Object(System_Object* arg0, System_Object* arg1);
extern /* static */ System_String* System_String_Concat__System_String_System_String_System_String(System_String* str0, System_String* str1, System_String* str2);
extern System_String* System_String_Substring__System_Int32(System_String* this__, int32_t startIndex);
extern System_String* System_String_Substring__System_Int32_System_Int32(System_String* this__, int32_t startIndex, int32_t length);
extern wchar_t System_String_get_Chars__System_Int32(System_String* this__, int32_t index);
extern int32_t System_String_get_Length(System_String* this__);
extern /* static */ bool System_String_IsNullOrWhiteSpace__System_String(System_String* value);
extern /* static */ System_String* System_String_Format__System_String_System_Object(System_String* format, System_Object* arg0);
extern /* static */ System_String* System_String_Format__System_String_System_Object_System_Object(System_String* format, System_Object* arg0, System_Object* arg1);
extern /* static */ System_String* System_String_Format__System_String_System_Object_System_Object_System_Object(System_String* format, System_Object* arg0, System_Object* arg1, System_Object* arg2);
extern System_String* System_String_Format__System_String_System_Array__System_Object(System_String* format, /* params */ il2c_arraytype(System_Object)* args);
    
extern /* static */ bool System_String_op_Equality__System_String_System_String(System_String* lhs, System_String* rhs);
extern /* static */ bool System_String_op_Inequality__System_String_System_String(System_String* lhs, System_String* rhs);

#ifdef __cplusplus
}
#endif

#endif
