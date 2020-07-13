#include "../Vector.h"

#include <memory.h>

C_API Vector* VectorCreate() {
    Vector *this = (Vector*)VectorGetMemMallocFunc()(sizeof(Vector));
    if (!this) {
        return Null;
    }

    this->DataPtr = (VectorNode*)VectorGetMemMallocFunc()(sizeof(VectorNode) * VectorGetInitializationCapacity());
    this->Size = 0;
    this->Capacity = VectorGetInitializationCapacity();
    memset(this->DataPtr, 0, this->Capacity * sizeof(VectorNode));
    return this;
}

C_API void VectorDestroy(Vector** this)
{
    VectorGetMemFreeFunc()((*this)->DataPtr);
    VectorGetMemFreeFunc()((*this));
    *this = Null;
}

C_API void VectorDestroyWithFreeElements(Vector** vector) {
    Vector* this = (*vector);
    for (VectorNode* node = this->DataPtr; node < &(this->DataPtr[this->Size]); ++node) {
        if (node->Data){
            VectorGetMemFreeFunc()(node->Data);
        }
    }
    VectorDestroy(vector);
}

C_API unsigned int VectorLen(Vector *this) {
    return this->Size;
}

C_API unsigned int VectorCapacity(Vector *this) {
    return this->Capacity;
}

C_API Bool VectorReSetCapacity(Vector *this, unsigned int newCapacity) {
    if (newCapacity <= this->Capacity) {
        return False;
    }

    VectorNode* ptr = (VectorNode*)VectorGetMemMallocFunc()(sizeof(VectorNode) * newCapacity);
    if (ptr == Null) {
        return False;
    }
    memcpy_s(ptr, newCapacity * sizeof(VectorNode), this->DataPtr, this->Size * sizeof(VectorNode));
    memset(&ptr[this->Size], 0, (newCapacity - this->Size) * sizeof(VectorNode));

    VectorGetMemFreeFunc()(this->DataPtr);

    this->DataPtr = ptr;
    this->Capacity = newCapacity;
    return True;
}

C_API Bool VectorAdd(Vector *this, void* data)
{
    if (this->Size == this->Capacity)
    {
        VectorReSetCapacity(this, (UInt)(VectorGetMemoryGrowthRate() * this->Capacity + 0.5f));
    }

    (this->DataPtr)[this->Size].Data = data;
    ++this->Size;
    return True;
}

C_API Bool VectorAddArray(Vector *this, void** data, unsigned int size)
{
    char** ptr = (char**)data;
    for (unsigned int i = 0; i < size; ++i)
    {
        VectorAdd(this, ptr[i]);
    }
    return True;
}

C_API NullUInt VectorGetIdxOfFirst(Vector *this, void* data)
{
    NullUInt result = NullUIntCreateInvalid();
    VectorNode * node = this->DataPtr;

    while (node < &(this->DataPtr[this->Size]))
    {
        if (node->Data == data)
        {
            result.Value = (UInt)((node - this->DataPtr) / sizeof(VectorNode));
            result.Valid = True;
            break;
        }
        ++node;
    }
    return result;
}

C_API Bool  VectorUpdateByIdx(Vector *this, unsigned int idx, void* data)
{
    if (idx + 1 > this->Size)
    {
        return False;
    }
    this->DataPtr[idx].Data = data;
    return True;
}

C_API void* VectorGetByIdx(Vector *this, unsigned int idx)
{
    if (idx + 1 > this->Size)
    {
        return Null;
    }
    return this->DataPtr[idx].Data;
}

C_API void* VectorRemoveByIdx(Vector *this, unsigned int idx)
{
    if (idx + 1 > this->Size)
    {
        return Null;
    }
    void* tmp = this->DataPtr[idx].Data;
    this->DataPtr[idx].Data = this->DataPtr[--this->Size].Data;
    return tmp;
}

C_API Bool VectorRemoveAndFreeByIdx(Vector *this, unsigned int idx)
{
    if (idx + 1 > this->Size)
    {
        return False;
    }
    void* tmp = this->DataPtr[idx].Data;
    this->DataPtr[idx].Data = this->DataPtr[--this->Size].Data;

    VectorGetMemFreeFunc()(tmp);
    return True;
}

C_API void VectorEachWithNoParam(Vector *this, VectorNoParamCallback callback)
{
    VectorNode * node = this->DataPtr;
    while (node < &(this->DataPtr[this->Size]))
    {
        callback(node->Data);
        ++node;
    }
}

C_API void  VectorEachWithOneParam(Vector *this, VectorOneParamCallback callback, void* extraData)
{
    VectorNode * node = this->DataPtr;
    while (node < &(this->DataPtr[this->Size]))
    {
        callback(node->Data, extraData);
        ++node;
    }
}

C_API void  VectorEachWithTwoParams(Vector *this, VectorTwoParamsCallback callback, void* param1, void* param2)
{
    VectorNode * node = this->DataPtr;
    while (node < &(this->DataPtr[this->Size]))
    {
        callback(node->Data, param1, param2);
        ++node;
    }
}

C_API void  VectorEachWithThreeParams(Vector *this, VectorThreeParamsCallback callback, void* param1, void* param2, void* param3)
{
    VectorNode * node = this->DataPtr;
    while (node < &(this->DataPtr[this->Size]))
    {
        callback(node->Data, param1, param2, param3);
        ++node;
    }
}
