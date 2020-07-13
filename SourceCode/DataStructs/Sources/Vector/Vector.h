#pragma once

#include "VectorConfigure.h"

typedef struct VectorNode
{
    void *Data;
} VectorNode;

typedef struct Vector
{
    VectorNode *DataPtr;
    unsigned int Size;
    unsigned int Capacity;
} Vector;

C_API Vector* VectorCreate();

C_API void    VectorDestroy(Vector**);
C_API void    VectorDestroyWithFreeElements(Vector**);

C_API unsigned int VectorLen(Vector *vector);
C_API unsigned int VectorCapacity(Vector *vector);
C_API Bool         VectorReSetCapacity(Vector *vector, unsigned int newSize);

C_API void*    VectorGetByIdx(Vector *vector, unsigned int idx);
C_API NullUInt VectorGetIdxOfFirst(Vector *vector, void* data);

C_API Bool  VectorAdd(Vector *vector, void* data);
C_API Bool  VectorAddArray(Vector *vector, void** data, unsigned int size);

C_API Bool  VectorUpdateByIdx(Vector *vector, unsigned int idx, void* data);

C_API void* VectorRemoveByIdx(Vector *vector, unsigned int idx);
C_API Bool  VectorRemoveAndFreeByIdx(Vector *vector, unsigned int idx);

C_API void VectorEachWithNoParam(Vector *vector, VectorNoParamCallback callback);
C_API void VectorEachWithOneParam(Vector *vector, VectorOneParamCallback callback, void* param);
C_API void VectorEachWithTwoParams(Vector *vector, VectorTwoParamsCallback callback, void* param1, void* param2);
C_API void VectorEachWithThreeParams(Vector *vector, VectorThreeParamsCallback callback, void* param1, void* param2, void* param3);

#define VectorEach VectorEachWithNoParam
#define VectorEachWithParam VectorEachWithOneParam
#define VectorEachWithMultParams VectorEachWithThreeParams
