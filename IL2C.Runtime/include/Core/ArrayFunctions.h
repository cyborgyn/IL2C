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

#ifndef System_ArrayFunctions_H__
#define System_ArrayFunctions_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////
// Array special functions

// It made identical type expression for array type.
#define il2c_arraytype(elementTypeName) \
    System_Array

#define il2c_array_item0ptr__(array) \
    (((uint8_t*)array) + sizeof(System_Array))
static inline void* il2c_array_itemptr__(
    System_Array* array, uint32_t elementSize, intptr_t index)
{
    il2c_assert(array != NULL); // TODO: NullReferenceException

    il2c_assert(array->vptr0__ == &System_Array_VTABLE__);
    il2c_assert(array->elementType__ != NULL);
    il2c_assert(array->length >= 0);
    il2c_assert(elementSize == il2c_sizeof__(array->elementType__));

    if (il2c_unlikely__((index < 0) || (index >= array->length)))
    {
        il2c_throw_indexoutofrangeexception__();
    }

    return il2c_array_item0ptr__(array) + ((intptr_t)elementSize) * index;
}
#define il2c_array_itemptr(array, elementTypeName, index) \
    (il2c_array_itemptr__(array, sizeof(elementTypeName), index))
#define il2c_array_item(array, elementTypeName, index) \
    (*(elementTypeName*)il2c_array_itemptr(array, elementTypeName, index))

#if defined(IL2C_USE_LINE_INFORMATION)
extern System_Array* il2c_new_array__(
    IL2C_RUNTIME_TYPE elementType, intptr_t length, const char* pFile, int line);
#define il2c_new_array(elementTypeName, length) \
    ((il2c_arraytype(elementTypeName)*)il2c_new_array__(il2c_typeof(elementTypeName), length, __FILE__, __LINE__))
#else
extern System_Array* il2c_new_array__(
    IL2C_RUNTIME_TYPE elementType, intptr_t length);
#define il2c_new_array(elementTypeName, length) \
    ((il2c_arraytype(elementTypeName)*)il2c_new_array__(il2c_typeof(elementTypeName), length))
#endif

#ifdef __cplusplus
}
#endif

#endif