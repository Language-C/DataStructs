#pragma once

#include "../BasicTypes/Types.h"

typedef struct ArrayGlobalConfigure {
    MemMallocFunction Malloc;
    MemFreeFunction Free;
} ArrayGlobalConfigure;

C_API ArrayGlobalConfigure* ArrayGetGlobalConfig();
