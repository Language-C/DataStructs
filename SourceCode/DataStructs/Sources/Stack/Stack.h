#pragma once

#include <Types.h>
#include <ClassMeta.h>

C_API void* StackCreate(const ClassMeta* const meta);
C_API void StackDestroy(void** const stack);

C_API void* StackTop(const void* const stack);
C_API Sizetype StackSize(const void* const stack);
C_API Bool StackIsEmpty(const void* const stack);
C_API Bool StackPush(void* const stack, void* const data);
C_API void StackPop(void* const stack);
