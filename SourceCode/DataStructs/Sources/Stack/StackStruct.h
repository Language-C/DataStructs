#pragma once

#ifdef WANT_TO_EXTEND_STACK

#include <ClassMeta.h>

typedef struct StackNode {
    struct StackNode* BeforeNode;
    void* Data;
} StackNode;

typedef struct Stack {
    StackNode* Top;
    ClassMeta* Meta;
    Sizetype Size;
} Stack;

#ifdef self
#undef self
#endif // self
#define self ((Stack*)(stack))

#ifdef selfPtr
#undef selfPtr
#endif // selfPtr
#define selfPtr ((Stack*)(*stack))

#endif // WANT_TO_EXTEND_STACK
