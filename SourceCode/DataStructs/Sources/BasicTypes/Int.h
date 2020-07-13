#pragma once

#include "Micros.h"
#include "Bool.h"

typedef unsigned int UInt;
typedef char Char;
typedef unsigned char UChar;
typedef int Int;
typedef float Float;
typedef double Double;
typedef long long Int64;

typedef struct NullInt_
{
    Bool Valid;
    Int Value;
} NullInt;

typedef struct NullUInt_
{
    Bool Valid;
    UInt Value;
} NullUInt;

C_API NullUInt NullUIntCreateInvalid();
C_API NullUInt NullUIntCreate(UInt value, Bool valid);