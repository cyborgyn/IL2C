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

#ifndef System_Delegate_H__
#define System_Delegate_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////
// System.Delegate

typedef struct System_Delegate System_Delegate;

typedef System_Object_VTABLE_DECL__ System_Delegate_VTABLE_DECL__;

extern System_Delegate_VTABLE_DECL__ System_Delegate_VTABLE__;

IL2C_DECLARE_RUNTIME_TYPE(System_Delegate);

extern /* virtual */ int32_t System_Delegate_GetHashCode(System_Delegate* this__);
extern /* virtual */ bool System_Delegate_Equals__System_Object(System_Delegate* this__, System_Object* obj);
extern /* static */ System_Delegate* System_Delegate_Combine__System_Delegate_System_Delegate(System_Delegate* a, System_Delegate* b);
extern /* static */ System_Delegate* System_Delegate_Remove__System_Delegate_System_Delegate(System_Delegate* source, System_Delegate* value);

#ifdef __cplusplus
}
#endif

#endif
