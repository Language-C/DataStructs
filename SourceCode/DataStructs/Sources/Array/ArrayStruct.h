#pragma once

#include "../BasicTypes/Types.h"

typedef struct ArrayConfigure {
    UInt BytesOfValueClass;
} ArrayConfigure;

typedef struct Array {
    char* Data;
    ArrayConfigure * Configure;
    UInt  Capacity;
} Array;
