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

#ifndef System_DelegateFunctions_H__
#define System_DelegateFunctions_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////
// Delegate special functions

#if defined(IL2C_USE_LINE_INFORMATION)
extern System_Delegate* il2c_new_delegate__(
    IL2C_RUNTIME_TYPE delegateType, System_Object* object, intptr_t method, const char* pFile, int line);
#define il2c_new_delegate(typeName, object, method) \
    il2c_new_delegate__(il2c_typeof(typeName), object, method, __FILE__, __LINE__)
#else
extern System_Delegate* il2c_new_delegate__(
    IL2C_RUNTIME_TYPE delegateType, System_Object* object, intptr_t method);
#define il2c_new_delegate(typeName, object, method) \
    il2c_new_delegate__(il2c_typeof(typeName), object, method)
#endif

extern void System_Delegate_MarkHandler__(System_Delegate* this__);

#ifdef __cplusplus
}
#endif

#endif
