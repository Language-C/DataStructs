#include <ClassInstance.h>

#include "../Array.h"

#define WANT_TO_EXTEND_ARRAY
#include "../ArrayStruct.h"

static Bool ArrayParamsIsValid(const ArrayParams* const params) {
    return params && params->Meta && params->Capacity > 0 ? True : False;
}

C_API void* ArrayCreate(const Sizetype capacity, const ClassMeta* const meta) {
    void* array = Null;
    ArrayParams params = { capacity, meta };

    if (!ArrayParamsIsValid(&params)) {
        return Null;
    }

    self = NewInstanceWithParams(ArrayMeta(), &params);
    if (!ArrayIsValid(self)) {
        FreeInstance(self, ArrayMeta());
        self = Null;
    }
    return self;
}

C_API void ArrayFill(void* const array, const void* const data) {
    char* begin;
    const char* end = &(self->Data[self->Capacity * self->Meta->BytesOfValueClass]);

    for (begin = self->Data;
        begin < end;
        begin += self->Meta->BytesOfValueClass) {
        self->Meta->CopyConstruct(begin, data);
    }
}

C_API void ArrayDestroy(void** const array) {
    if (!array || !selfPtr) {
        return;
    }
    FreeInstance(selfPtr, ArrayMeta());
    selfPtr = Null;
}

C_API Bool ArrayIsValid(const void* const array) {
    return self && self->Meta && self->Data &&
        (self->Capacity > 0) ? True : False;
}

C_API void* ArrayGet(void* const array, const Sizetype idx) {
    if (idx + 1 > self->Capacity) {
        return Null;
    }

    return &(self->Data[idx * self->Meta->BytesOfValueClass]);
}

C_API Bool ArraySet(void* const array,
    const Sizetype idx, void* const data) {
    if (idx + 1 > self->Capacity) {
        return False;
    }
    self->Meta->CopyConstruct(&self->Data[idx * self->Meta->BytesOfValueClass], data);
    return True;
}
