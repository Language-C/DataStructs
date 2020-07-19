#pragma once

#include <stdint.h>

#include "Micros.h"
#include "Bool.h"

typedef unsigned int UInt;
typedef char Char;
typedef unsigned char UChar;
typedef int Int;
typedef float Float;
typedef double Double;
typedef int64_t Int64;
typedef uint64_t UInt64;

typedef size_t Sizetype;

typedef struct NullInt
{
    Bool Valid;
    Int Value;
} NullInt;

typedef struct NullUInt
{
    Bool Valid;
    UInt Value;
} NullUInt;

C_API NullUInt NullUIntCreateInvalid();
C_API NullUInt NullUIntCreate(UInt value, Bool valid);