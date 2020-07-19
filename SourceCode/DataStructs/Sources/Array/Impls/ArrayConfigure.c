#pragma once

#include "../ArrayConfigure.h"
#include "../ArrayGlobalConfigure.h"
#include "../../ClassOriented/ClassOriented.h"

#define WANT_TO_EXTEND_ARRAY
#include "../ArrayStruct.h"

static CopyConstructor(Array, dst, src) {
}

static Constructor(Array, array) {
}

static ParamConstructor(Array, array, params) {
    self->Capacity = ((ArrayParams*)params)->Capacity;
    self->Configure = ((ArrayParams*)params)->Configure;

    self->Data = (char*)ArrayGetGlobalConfig()->Malloc(
        self->Configure->BytesOfValueClass * self->Capacity);
}

static Destructor(Array, array) {
    if (self->Data) {
        ArrayGetGlobalConfig()->Free(self->Data);
    }
}

ClassMeta ArrayConfigure = MakeClassMeta(Array);

C_API const ClassMeta* ArrayConfig() {
    return &ArrayConfigure;
}