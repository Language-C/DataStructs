#pragma once

#include "../BasicTypes/Types.h"

typedef void(*VectorMemFreeFunction)(void*);
typedef void*(*VectorMemMallocFunction)(size_t);

// Decl callback function type
typedef void(*VectorNoParamCallback)(void* node);
typedef void(*VectorOneParamCallback)(void* node, void* param);
typedef void(*VectorTwoParamsCallback)(void* node, void* param1, void* param2);
typedef void(*VectorThreeParamsCallback)(void* node, void* param1, void* param2, void* param3);

C_API void VectorSetInitializationCapacity(unsigned int);
C_API void VectorResetInitializationCapacity();
C_API unsigned int VectorGetInitializationCapacity(void);

C_API void VectorSetMemFreeFunc(VectorMemFreeFunction func);
C_API VectorMemFreeFunction VectorGetMemFreeFunc();

C_API void VectorSetMemMallocFunc(VectorMemMallocFunction func);
C_API VectorMemMallocFunction VectorGetMemMallocFunc();

C_API Bool  VectorSetMemoryGrowthRate(float newRate);
C_API float VectorGetMemoryGrowthRate();
