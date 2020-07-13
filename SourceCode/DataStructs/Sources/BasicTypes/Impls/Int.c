#include "../Int.h"

C_API NullUInt NullUIntCreateInvalid()
{
    NullUInt result;
    result.Valid = False;
    result.Value = 0;
    return result;
}

C_API NullUInt NullUIntCreate(UInt value, Bool valid)
{
    NullUInt result;
    result.Valid = valid;
    result.Value = value;
    return result;
}