#define WANT_TO_EXTEND_STACK

#include <ClassInstance.h>

#include "../Stack.h"
#include "../StackMeta.h"
#include "../StackStruct.h"

ClassMeta NodeMeta = MakeNullMeta(StackNode);

C_API void* StackCreate(const ClassMeta* const meta) {
    return NewInstanceWithParams(StackMeta(), meta);
}

C_API void StackDestroy(void** const stack) {
    if (stack) {
        FreeInstance(selfPtr, StackMeta());
        selfPtr = Null;
    }
}

C_API void* StackTop(const void* const stack) {
    return self->Top->Data;
}

C_API Sizetype StackSize(const void* const stack) {
    return self->Size;
}
C_API Bool StackIsEmpty(const void* const stack) {
    return self->Size == 0 ? True : False;
}

C_API Bool StackPush(void* const stack, void* const data) {
    StackNode* node = NewInstance(&NodeMeta);
    if (!node) {
        return False;
    }
    node->BeforeNode = self->Top;
    node->Data = data;
    self->Top = node;
    self->Size++;
    return True;
}

C_API void StackPop(void* const stack) {
    StackNode* before = self->Top->BeforeNode;
    if (before) {
        FreeInstance(self->Top->Data, self->Meta);
        FreeInstance(self->Top, &NodeMeta);
        self->Top = before;
    }
}
