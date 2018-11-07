#ifndef __System_Exception_H__
#define __System_Exception_H__

#pragma once

#include <il2c.h>

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////
// System.Exception

typedef struct System_Exception System_Exception;

typedef __System_Object_VTABLE_DECL__ __System_Exception_VTABLE_DECL__;

struct System_Exception
{
    __System_Exception_VTABLE_DECL__* vptr0__;
};

extern __System_Exception_VTABLE_DECL__ __System_Exception_VTABLE__;
extern IL2C_RUNTIME_TYPE_DECL __System_Exception_RUNTIME_TYPE__;

#define __System_Exception_IL2C_MarkHandler__ IL2C_DEFAULT_MARK_HANDLER

extern void System_Exception__ctor(System_Exception* this__);

/////////////////////////////////////////////////
// Exception special functions

extern void il2c_throw__(jmp_buf unwind_target, System_Exception* ex);
#define il2c_throw(ex) \
    il2c_throw__(unwind_target__, (System_Exception*)ex)

#define il2c_try \
    do { jmp_buf unwind_target__; if (!setjmp(unwind_target__))

#define il2c_catch(ex) \
    else

#define il2c_end_try \
    } while (0)

#define il2c_leave(label) \
    goto label

#ifdef __cplusplus
}
#endif

#endif
