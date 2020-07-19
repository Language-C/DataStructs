#include <ClassInstance.h>

#include "../Array.h"
#include "../ArrayConfigure.h"
#include "../ArrayGlobalConfigure.h"

#define WANT_TO_EXTEND_ARRAY
#include "../ArrayStruct.h"

C_API void* ArrayCreate(Sizetype const capacity,
    const ClassMeta* const configure) {
    void* array = Null;
    ArrayParams params = { capacity, configure };

    if (capacity < 1 || !ClassMetaIsValid(configure)) {
        return Null;
    }

    self = NewInstanceWithParams(ArrayConfig(), &params);
    if (!ArrayIsValid(self)) {
        FreeInstance(self, ArrayConfig());
        self = Null;
    }
    return self;
}

C_API void ArrayFill(void* const array, const void* const data) {
    char* begin;
    const char* end = &(self->Data[self->Capacity * self->Configure->BytesOfValueClass]);

    for (begin = self->Data;
        begin < end;
        begin += self->Configure->BytesOfValueClass) {
        self->Configure->CopyConstruct(begin, data);
    }
}

C_API void ArrayDestroy(void** const array) {
    if (!array || !selfPtr) {
        return;
    }

    ArrayGetGlobalConfig()->Free(selfPtr->Data);
    ArrayGetGlobalConfig()->Free(selfPtr);
    selfPtr = Null;
}

C_API Bool ArrayIsValid(const void* const array) {
    return self && self->Configure && self->Data &&
        (self->Capacity > 0) ? True : False;
}

C_API void* ArrayGet(const void* const array, const Sizetype idx) {
    if (idx + 1 > self->Capacity) {
        return Null;
    }

    return &(self->Data[idx * self->Configure->BytesOfValueClass]);
}

C_API Bool ArraySet(const void* const array,
    const Sizetype idx, const void* const data) {
    if (idx + 1 > self->Capacity) {
        return False;
    }
    self->Configure->CopyConstruct(&self->Data[idx * self->Configure->BytesOfValueClass], data);
    return True;
}