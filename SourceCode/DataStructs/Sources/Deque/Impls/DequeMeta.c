#define WANT_TO_EXTEBD_DEQUE

#include <ClassOriented/ClassOriented.h>
#include <ClassInstance.h>

#include "../DequeStruct.h"
#include "../DequeMeta.h"

static Constructor(Deque, Deque) {
    //not use
}

static ParamConstructor(Deque, deque, meta) {
    self->Capacity = 32;
    self->Meta = (ClassMeta*)meta;
    self->Head = 0;
    self->Tail = 0;
    self->Data = (void**)NewInstances(self->Capacity, VoidMeta());
}

static CopyConstructor(Deque, dst, src) {
    // not use
}

static Destructor(Deque, deque) {
    void** end = &(self->Data[self->Tail]);
    void** begin = &(self->Data[self->Head]);
    void** dataTail = &(self->Data[self->Capacity]);

    if (self->Tail < self->Head) {
        //Free All Y from begin to end
        // ---------------------------
        //| Y | Y |End| N | N |BEG| Y |
        // ---------------------------
        while (begin < dataTail) {
            FreeInstance(*begin, self->Meta);
            begin++;
        }
        begin = self->Data;
    }
    while (begin != end) {
        FreeInstance(*begin, self->Meta);
        begin++;
    }

    FreeInstances(self->Data, self->Capacity, VoidMeta());
}

ClassMeta DequeMetadata = MakeClassMeta(Deque);

const ClassMeta* DequeMeta() {
    return &DequeMetadata;
}
