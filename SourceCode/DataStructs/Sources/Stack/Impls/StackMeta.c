#define WANT_TO_EXTEND_STACK

#include <ClassInstance.h>
#include <ClassOriented/ClassOriented.h>

#include "../StackMeta.h"
#include "../StackStruct.h"

StackNode Root = { Null, Null };

static Constructor(Stack, stack) {
    //not use
}

static ParamConstructor(Stack, stack, valueClassMeta) {
    self->Meta = (ClassMeta*)valueClassMeta;
    self->Size = 0U;
    self->Top = &Root;
}

static CopyConstructor(Stack, dst, src) {
    //not use
}

static Destructor(Stack, stack) {
    StackNode* beforeNode = Null;
    for (beforeNode = self->Top->BeforeNode; beforeNode;
        self->Top = beforeNode, beforeNode = beforeNode->BeforeNode) {
        FreeInstance(self->Top->Data, self->Meta);
        FreeInstance(self->Top, Null);
    }
}

ClassMeta StackMetadata = MakeClassMeta(Stack);

C_API ClassMeta* StackMeta() {
    return &StackMetadata;
}
