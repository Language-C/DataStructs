#include <memory.h>

#include "../Array.h"
#include "../ArrayGlobalConfigure.h"

C_API Array* ArrayCreateWithoutInitialize(ArrayConfigure* configure) {
    if (configure->BytesOfValueClass == 0) {
        return Null;
    }

    Array* self = ArrayGetGlobalConfig()->Malloc(sizeof(Array));
    if (!self) {
        return Null;
    }

    self->Capacity = ArrayGetGlobalConfig()->InitializationCapacity;
    self->Data = (char*)ArrayGetGlobalConfig()->Malloc(configure->BytesOfValueClass * self->Capacity);
    if (!self->Data) {
        ArrayGetGlobalConfig()->Free(self);
        return Null;
    }

    self->Configure = configure;
    return self;
}

C_API Array* ArrayCreate(ArrayConfigure* configure) {
    Array* self = ArrayCreateWithoutInitialize(configure);
    if (self) {
        memset(self->Data, 0, configure->BytesOfValueClass * self->Capacity);
    }
    return self;
}