#pragma once

#include "../ArrayMeta.h"
#include <ClassInstance.h>

#define WANT_TO_EXTEND_ARRAY
#include "../ArrayStruct.h"
#include "../../ClassOriented/ClassOriented.h"

static CopyConstructor(Array, dst, src) {
}

static Constructor(Array, array) {
}

static ParamConstructor(Array, array, params) {
    self->Capacity = ((ArrayParams*)params)->Capacity;
    self->Meta = ((ArrayParams*)params)->Meta;

    self->Data = (char*)NewInstances(self->Capacity, self->Meta);
}

static Destructor(Array, array) {
    if (self->Data) {
        FreeInstances(self->Data, self->Capacity, self->Meta);
    }
}

ClassMeta ArrayConfigure = MakeClassMeta(Array);

C_API const ClassMeta* ArrayMeta() {
    return &ArrayConfigure;
}
