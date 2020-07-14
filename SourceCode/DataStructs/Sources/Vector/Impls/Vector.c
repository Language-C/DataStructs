#include "../Vector.h"

#include <memory.h>

C_API Vector* VectorCreate() {
    Vector *self = (Vector*)VectorGetMemMallocFunc()(sizeof(Vector));
    if (!self) {
        return Null;
    }

    self->DataPtr = (VectorNode*)VectorGetMemMallocFunc()(sizeof(VectorNode) * VectorGetInitializationCapacity());
    self->Size = 0;
    self->Capacity = VectorGetInitializationCapacity();
    memset(self->DataPtr, 0, self->Capacity * sizeof(VectorNode));
    return self;
}

C_API void VectorDestroy(Vector** selfPtr) {
    VectorGetMemFreeFunc()((*selfPtr)->DataPtr);
    VectorGetMemFreeFunc()((*selfPtr));
    *selfPtr = Null;
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
    for (UInt i = 0; i < size; ++i) {
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

C_API void VectorEachWithNoParam(Vector *self, VectorNoParamCallback callback) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size])) {
        callback(node->Data);
        ++node;
    }
}

C_API void  VectorEachWithOneParam(Vector *self, VectorOneParamCallback callback, void* param) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size])) {
        callback(node->Data, param);
        ++node;
    }
}

C_API void  VectorEachWithTwoParams(Vector *self,
    VectorTwoParamsCallback callback, void* param1, void* param2) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size])) {
        callback(node->Data, param1, param2);
        ++node;
    }
}

C_API void VectorEachWithThreeParams(Vector *self,
    VectorThreeParamsCallback callback, void* param1, void* param2, void* param3) {
    VectorNode * node = self->DataPtr;
    while (node < &(self->DataPtr[self->Size]))
    {
        callback(node->Data, param1, param2, param3);
        ++node;
    }
}
