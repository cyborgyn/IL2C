#include "il2c_private.h"

/////////////////////////////////////////////////////////////
// System.UInt32

System_String* System_UInt32_ToString(uint32_t* this__)
{
    wchar_t buffer[14];

    il2c_ultow(*this__, buffer, 10);
    return il2c_new_string(buffer);
}

int32_t System_UInt32_GetHashCode(uint32_t* this__)
{
    il2c_assert(this__ != NULL);

    return *this__;
}

bool System_UInt32_Equals(uint32_t* this__, uint32_t obj)
{
    il2c_assert(this__ != NULL);

    return *this__ == obj;
}

bool System_UInt32_Equals_1(uint32_t* this__, System_Object* obj)
{
    il2c_assert(this__ != NULL);

    if (obj == NULL)
    {
        return false;
    }

    uint32_t rhs = *il2c_unbox(obj, System_UInt32);
    return *this__ == rhs;
}

bool System_UInt32_TryParse(System_String* s, uint32_t* result)
{
    // TODO: NullReferenceException
    il2c_assert(s != NULL);

    il2c_assert(result != NULL);
    il2c_assert(s->string_body__ != NULL);

    wchar_t* endPtr;

    *result = il2c_wcstoul(s->string_body__, &endPtr, 10);
    return ((s->string_body__ != endPtr) && (errno == 0)) ? true : false;
}

/////////////////////////////////////////////////
// VTable and runtime type info declarations

IL2C_DECLARE_TRAMPOLINE_VFUNC_FOR_VALUE_TYPE(System_UInt32);
IL2C_DECLARE_TRAMPOLINE_VTABLE_FOR_VALUE_TYPE(System_UInt32);
IL2C_DECLARE_RUNTIME_TYPE(System_UInt32, "System.UInt32", IL2C_TYPE_UNSIGNED_INTEGER, System_ValueType);
