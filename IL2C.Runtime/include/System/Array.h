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

#ifndef System_Array_H__
#define System_Array_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////
// System.Array

typedef struct System_Array System_Array;

typedef System_Object_VTABLE_DECL__ System_Array_VTABLE_DECL__;

struct System_Array
{
    System_Array_VTABLE_DECL__* vptr0__;

    IL2C_RUNTIME_TYPE elementType__;
    intptr_t length;
};

#define  System_Array_VTABLE__ System_Object_VTABLE__

IL2C_DECLARE_RUNTIME_TYPE(System_Array);

extern int32_t System_Array_get_Length(System_Array* this__);
extern int32_t System_Array_GetLowerBound__System_Int32(System_Array* this__, int32_t dimension);
extern int32_t System_Array_GetUpperBound__System_Int32(System_Array* this__, int32_t dimension);


#ifdef __cplusplus
}
#endif

#endif
