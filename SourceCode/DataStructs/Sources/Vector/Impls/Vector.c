#include <memory.h>

#include "../Vector.h"
#include "../VectorGlobalConfigure.h"

C_API Vector* VectorCreate() {
    return VectorCreateWithCapacity(VectorGetInitializationCapacity());
}

C_API Vector* VectorCreateWithCapacity(UInt capacity) {
    if (capacity == 0) {
        return Null;
    }

    Vector *self = (Vector*)VectorGetMemMallocFunc()(sizeof(Vector));
    if (!self) {
        return Null;
    }

    self->DataPtr = (VectorNode*)VectorGetMemMallocFunc()(sizeof(VectorNode) * capacity);
    if (!self->DataPtr) {
        VectorGetMemFreeFunc()(self);
        return Null;
    }

    self->Size = 0;
    self->Capacity = capacity;
    memset(self->DataPtr, 0, capacity * sizeof(VectorNode));

    return self;
}

C_API void VectorDestroy(Vector** selfPtr) {
    VectorGetMemFreeFunc()((*selfPtr)->DataPtr);
    VectorGetMemFreeFunc()((*selfPtr));
    *selfPtr = Null;
}

C_API void VectorDestroyWithFreeElements(Vector** selfPtr) {
    VectorClear(*selfPtr);
    VectorDestroy(selfPtr);
}

C_API UInt VectorLen(Vector *self) {
    return self->Size;
}

C_API UInt VectorCapacity(Vector *self) {
    return self->Capacity;
}

C_API Bool VectorReSetCapacity(Vector *self, UInt newCapacity) {
    if (newCapacity <= self->Capacity) {
        return False;
    }

    VectorNode* ptr = (VectorNode*)VectorGetMemMallocFunc()(sizeof(VectorNode) * newCapacity);
    if (ptr == Null) {
        return False;
    }
    memcpy_s(ptr, newCapacity * sizeof(VectorNode), self->DataPtr, self->Size * sizeof(VectorNode));
    memset(&ptr[self->Size], 0, (newCapacity - self->Size) * sizeof(VectorNode));

    VectorGetMemFreeFunc()(self->DataPtr);

    self->DataPtr = ptr;
    self->Capacity = newCapacity;
    return True;
}

C_API void VectorClear(Vector* self) {
    int i;

#pragma omp parallel for
    for (i = 0; i < (int)self->Size; ++i) {
        if (self->DataPtr[i].Data) {
            VectorGetMemFreeFunc()(self->DataPtr[i].Data);
            self->DataPtr[i].Data = Null;
        }
    }
    self->Size = 0U;
}

C_API Bool VectorIsEmpty(Vector* self) {
    return self->Size == 0U ? True : False;
}

C_API Bool VectorAdd(Vector *self, void* data) {
    if (self->Size == self->Capacity) {
        VectorReSetCapacity(self, (UInt)(VectorGetMemoryGrowthRate() * self->Capacity + 0.5f));
    }

    (self->DataPtr)[self->Size].Data = data;
    ++self->Size;
    return True;
}

C_API Bool VectorAddArray(Vector *self, void** data, UInt size) {
    char** ptr = (char**)data;
    int i;

#pragma omp parallel for
    for (i = 0; i < (int)size; ++i) {
        VectorAdd(self, ptr[i]);
    }
    return True;
}

C_API NullUInt VectorGetIdxOfFirst(Vector *self, void* data) {
    NullUInt result = NullUIntCreateInvalid();
    VectorNode * node = self->DataPtr;

    while (node < &(self->DataPtr[self->Size])) {
        if (node->Data == data) {
            result.Value = (UInt)((node - self->DataPtr) / sizeof(VectorNode));
            result.Valid = True;
            break;
        }
        ++node;
    }
    return result;
}

C_API Bool  VectorUpdateByIdx(Vector *self, UInt idx, void* data) {
    if (idx + 1 > self->Size) {
        return False;
    }
    self->DataPtr[idx].Data = data;
    return True;
}

C_API void* VectorGetByIdx(Vector *self, UInt idx) {
    if (idx + 1 > self->Size) {
        return Null;
    }
    return self->DataPtr[idx].Data;
}

C_API void* VectorRemoveByIdx(Vector *self, UInt idx) {
    if (idx + 1 > self->Size) {
        return Null;
    }
    void* tmp = self->DataPtr[idx].Data;
    self->DataPtr[idx].Data = self->DataPtr[--self->Size].Data;
    return tmp;
}

C_API Bool VectorRemoveAndFreeByIdx(Vector *self, UInt idx) {
    if (idx + 1 > self->Size) {
        return False;
    }
    void* tmp = self->DataPtr[idx].Data;
    self->DataPtr[idx].Data = self->DataPtr[--self->Size].Data;

    VectorGetMemFreeFunc()(tmp);
    return True;
}

C_API void VectorEachWithNoParam(Vector *self, NoParamCallback callback) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size])) {
        callback(node->Data);
        ++node;
    }
}

C_API void  VectorEachWithOneParam(Vector *self, OneParamCallback callback, void* param) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size])) {
        callback(node->Data, param);
        ++node;
    }
}

C_API void  VectorEachWithTwoParams(Vector *self,
    TwoParamsCallback callback, void* param1, void* param2) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size])) {
        callback(node->Data, param1, param2);
        ++node;
    }
}

C_API void VectorEachWithThreeParams(Vector *self,
    ThreeParamsCallback callback, void* param1, void* param2, void* param3) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size]))
    {
        callback(node->Data, param1, param2, param3);
        ++node;
    }
}
