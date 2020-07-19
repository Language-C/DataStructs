#pragma once

#include <Types.h>

typedef struct ClassGlobalConfigure {
    MemFreeFunction Free;
    MemMallocFunction Malloc;
} ClassGlobalConfigure;

C_API const ClassGlobalConfigure* ClassGlobalConfig();