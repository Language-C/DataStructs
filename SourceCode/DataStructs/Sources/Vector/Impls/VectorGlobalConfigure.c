#include <stdlib.h>

#include "../VectorGlobalConfigure.h"

static UInt InitializationCapacity = 32U;
static float MemoryGrowthRate = 2.0f;

static MemFreeFunction Free = free;
static MemMallocFunction Malloc = malloc;

C_API void VectorSetInitializationCapacity(UInt newCapacity) {
    InitializationCapacity = newCapacity > 0 ? newCapacity : InitializationCapacity;
}

C_API void VectorResetInitializationCapacity() {
    InitializationCapacity = 32U;
}

C_API UInt VectorGetInitializationCapacity(void) {
    return InitializationCapacity;
}

C_API void VectorSetMemFreeFunc(MemFreeFunction func) {
    Free = func;
}

C_API MemFreeFunction VectorGetMemFreeFunc() {
    return Free;
}

C_API void VectorSetMemMallocFunc(MemMallocFunction func) {
    Malloc = func;
}

C_API MemMallocFunction VectorGetMemMallocFunc() {
    return Malloc;
}

C_API Bool VectorSetMemoryGrowthRate(float newRate) {
    if (newRate > 0) {
        MemoryGrowthRate = newRate;
        return True;
    }
    return False;
}

C_API float VectorGetMemoryGrowthRate() {
    return MemoryGrowthRate;
}
