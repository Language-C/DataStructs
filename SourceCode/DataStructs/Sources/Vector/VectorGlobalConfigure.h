#pragma once

#include "../BasicTypes/Types.h"

C_API void VectorSetInitializationCapacity(UInt);
C_API void VectorResetInitializationCapacity();
C_API UInt VectorGetInitializationCapacity(void);

C_API void VectorSetMemFreeFunc(MemFreeFunction func);
C_API MemFreeFunction VectorGetMemFreeFunc();

C_API void VectorSetMemMallocFunc(MemMallocFunction func);
C_API MemMallocFunction VectorGetMemMallocFunc();

C_API Bool  VectorSetMemoryGrowthRate(float newRate);
C_API float VectorGetMemoryGrowthRate();
