#include "../VectorConfigure.h"

#include <stdlib.h>

static UInt InitializationCapacity = 32U;
static float MemoryGrowthRate = 2.0f;

static VectorMemFreeFunction Free = free;
static VectorMemMallocFunction Malloc = malloc;

C_API void VectorSetInitializationCapacity(UInt newCapacity) {
    InitializationCapacity = newCapacity > 0 ? newCapacity : InitializationCapacity;
}

C_API void VectorResetInitializationCapacity() {
    InitializationCapacity = 32U;
}

C_API UInt VectorGetInitializationCapacity(void) {
    return InitializationCapacity;
}

C_API void VectorSetMemFreeFunc(VectorMemFreeFunction func) {
    Free = func;
}

C_API VectorMemFreeFunction VectorGetMemFreeFunc() {
    return Free;
}

C_API void VectorSetMemMallocFunc(VectorMemMallocFunction func) {
    Malloc = func;
}

C_API VectorMemMallocFunction VectorGetMemMallocFunc() {
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
