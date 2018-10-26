#include "il2c_private.h"

/////////////////////////////////////////////////////////////
// System.Boolean

IL2C_CONST_STRING(System_Boolean_True, L"True");
IL2C_CONST_STRING(System_Boolean_False, L"False");
System_String* System_Boolean_ToString(bool* this__)
{
    return *this__ ? System_Boolean_True : System_Boolean_False;
}

int32_t System_Boolean_GetHashCode(bool* this__)
{
    il2c_assert(this__ != NULL);

    return *this__;
}

bool System_Boolean_Equals(bool* this__, bool obj)
{
    il2c_assert(this__ != NULL);

    return *this__ == obj;
}

bool System_Boolean_Equals_1(bool* this__, System_Object* obj)
{
    il2c_assert(this__ != NULL);

    if (obj == NULL)
    {
        return false;
    }

    bool rhs = *il2c_unbox(obj, System_Boolean);
    return *this__ == rhs;
}

bool System_Boolean_TryParse(System_String* s, bool* result)
{
    // TODO: NullReferenceException
    il2c_assert(s != NULL);

    il2c_assert(result != NULL);
    il2c_assert(s->string_body__ != NULL);

    if (wcsicmp(il2c_c_str(s), il2c_c_str(System_Boolean_True)) == 0)
    {
        *result = true;
        return true;
    }
    if (wcsicmp(il2c_c_str(s), il2c_c_str(System_Boolean_False)) == 0)
    {
        *result = false;
        return true;
    }

    *result = false;
    return false;
}

/////////////////////////////////////////////////
// VTable and runtime type info declarations

IL2C_DECLARE_OBJECT_VTABLE(System_Boolean);
IL2C_DECLARE_RUNTIME_TYPE(System_Boolean, "System.Boolean", IL2C_TYPE_INTEGER, System_ValueType);
