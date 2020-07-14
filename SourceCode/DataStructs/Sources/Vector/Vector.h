#pragma once

#include "VectorConfigure.h"
#include "VectorStruct.h"

C_API Vector* VectorCreate();

C_API void VectorDestroy(Vector** selfPtr);
C_API void VectorDestroyWithFreeElements(Vector** selfPtr);

C_API UInt VectorLen(Vector* self);

C_API UInt VectorCapacity(Vector* self);
C_API Bool VectorReSetCapacity(Vector* self, UInt newCapacity);

C_API void*    VectorGetByIdx(Vector* self, UInt idx);
C_API NullUInt VectorGetIdxOfFirst(Vector* self, void* data);

C_API Bool  VectorAdd(Vector* self, void* data);
C_API Bool  VectorAddArray(Vector* self, void** data, UInt size);

C_API Bool  VectorUpdateByIdx(Vector* self, UInt idx, void* data);

C_API void* VectorRemoveByIdx(Vector* self, UInt idx);
C_API Bool  VectorRemoveAndFreeByIdx(Vector*, UInt idx);

C_API void VectorEachWithNoParam(Vector* self,
    VectorNoParamCallback callback);

C_API void VectorEachWithOneParam(Vector* self,
    VectorOneParamCallback callback, void* param);

C_API void VectorEachWithTwoParams(Vector* self,
    VectorTwoParamsCallback callback, void* param1, void* param2);

C_API void VectorEachWithThreeParams(Vector* self,
    VectorThreeParamsCallback callback, void* param1, void* param2, void* param3);

#define VectorEach VectorEachWithNoParam
#define VectorEachWithParam VectorEachWithOneParam
#define VectorEachWithMultParams VectorEachWithThreeParams
