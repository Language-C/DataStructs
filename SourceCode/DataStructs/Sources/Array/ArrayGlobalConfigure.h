#pragma once

#include "../BasicTypes/Types.h"

typedef struct ArrayGlobalConfigure {
    MemMallocFunction Malloc;
    MemFreeFunction Free;
    UInt InitializationCapacity
} ArrayGlobalConfigure;

C_API ArrayGlobalConfigure* ArrayGetGlobalConfig();
