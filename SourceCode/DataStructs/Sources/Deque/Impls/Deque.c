#define WANT_TO_EXTEBD_DEQUE

#include <ClassInstance.h>
#include <Memory/Memory.h>

#include "../Deque.h"
#include "../DequeStruct.h"
#include "../DequeMeta.h"

static Bool DequeDataCopyTwice(void* const deque, void** const data, const Sizetype capacity) {
    if (!MemCopy(data, sizeof(void*) * capacity,
        &self->Data[self->Head],
        (self->Capacity - self->Head) * sizeof(void*))) {
        return False;
    }
    if (self->Tail == 0) {
        return True;
    }

    return MemCopy(&data[(self->Capacity - self->Head)],
        sizeof(void*) * (capacity + self->Head - self->Capacity),
        self->Data, sizeof(void*) * (self->Tail + 1));
}

static Bool DequeDataCopy(void* const deque, void** const data, const Sizetype capacity) {
    if (self->Head > self->Tail) {
        return DequeDataCopyTwice(deque, data, capacity);
    }
    return MemCopy(data, sizeof(void*) * capacity,
        &self->Data[self->Head], (self->Tail - self->Head) * sizeof(void*));
}

static Bool DequeResetCapacity(void* const deque, const Sizetype newCapacity) {
    void** tmp = (void**)NewInstances(newCapacity, VoidMeta());
    if (!tmp) {
        return False;
    }
    if (!DequeDataCopy(deque, tmp, newCapacity)) {
        FreeInstances(tmp, newCapacity, VoidMeta());
        return False;
    }
    FreeInstances(self->Data, self->Capacity, VoidMeta());

    self->Tail = DequeSize(deque);
    self->Head = 0;
    self->Capacity = newCapacity;
    self->Data = tmp;
    return True;
}

static void DequeTailDecrease(void* const deque) {
    if (self->Tail == 0) {
        self->Tail = self->Capacity - 1;
    }
    else {
        self->Tail--;
    }
}

static void DequeTailIncrease(void* const deque) {
    self->Tail++;
    if (self->Tail == self->Capacity) {
        self->Tail = 0;
    }
}

static void DequeHeadDecrease(void* const deque) {
    if (self->Head == 0) {
        self->Head = self->Capacity - 1;
    }
    else {
        self->Head--;
    }
}

static void DequeHeadIncrease(void* const deque) {
    self->Head++;
    if (self->Head == self->Capacity) {
        self->Head = 0;
    }
}

static void DequeFreeUpExcessMemory(void* const deque) {
    if (self->Capacity > 32 && DequeSize(self) * 4 < self->Capacity) {
        DequeResetCapacity(self, self->Capacity / 2);
    }
}

static Bool DequeAutoExpansion(void* const deque) {
    if (DequeSize(self) == self->Capacity - 1) {
        if (!DequeResetCapacity(self, self->Capacity * 2)) {
            return False;
        }
    }
    return True;
}

C_API void* DequeCreate(const ClassMeta* const meta) {
    Deque* deque = Null;
    if (!meta) {
        return Null;
    }
    self = NewInstanceWithParams(DequeMeta(), meta);

    if (!self || !(self->Data)) {
        FreeInstance(self, DequeMeta());
        self = Null;
    }
    return self;
}

C_API void DequeDestroy(void** deque) {
    if (!deque) {
        return;
    }
    FreeInstance(selfPtr, DequeMeta());
    selfPtr = Null;
}

C_API Bool DequePushBack(void* const deque, void* const data) {
    if (!DequeAutoExpansion(self)) {
        return False;
    }
    self->Data[self->Tail] = data;
    DequeTailIncrease(self);
    return True;
}

C_API Bool DequePushFront(void* const deque, void* const data) {
    if (!DequeAutoExpansion(self)) {
        return False;
    }
    DequeHeadDecrease(self);
    self->Data[self->Head] = data;
    return True;
}

C_API void DequePopBack(void* const deque) {
    if (DequeSize(self) == 0) {
        return;
    }
    DequeTailDecrease(deque);

    FreeInstance(self->Data[self->Tail], self->Meta);
    self->Data[self->Tail] = Null;

    DequeFreeUpExcessMemory(self);
}

C_API void DequePopFront(void* const deque) {
    if (DequeSize(self) == 0) {
        return;
    }
    FreeInstance(self->Data[self->Head], self->Meta);
    DequeHeadIncrease(self);
    DequeFreeUpExcessMemory(self);
}

C_API Bool DequeIsEmpty(const void* const deque) {
    return self->Tail == self->Head ? True : False;
}

C_API Sizetype DequeSize(const void* const deque) {
    return self->Head > self->Tail ?
        self->Capacity - self->Head + self->Tail : self->Tail - self->Head;
}

C_API void* DequePickFront(const void* const deque) {
    if (DequeSize(self) == 0) {
        return Null;
    }
    return self->Data[self->Head];
}

C_API void* DequePickBack(const void* const deque) {
    if (DequeSize(self) == 0) {
        return Null;
    }
    if (self->Tail == 0) {
        return self->Data[self->Capacity - 1];
    }
    else {
        return self->Data[self->Tail - 1];
    }
}
