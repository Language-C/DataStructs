#pragma once

#ifdef WANT_TO_EXTEBD_DEQUE

#include <Types.h>
#include <ClassMeta.h>

typedef struct Deque {
    void** Data;
    const ClassMeta* Meta;
    Sizetype Head, Tail;
    Sizetype Capacity;
}Deque;

#ifdef self
#undef self
#endif // self
#define self ((Deque*)deque)

#ifdef selfPtr
#undef selfPtr
#endif // selfPtr
#define selfPtr ((Deque*)*deque)

#endif // WANT_TO_EXTEBD_Deque
