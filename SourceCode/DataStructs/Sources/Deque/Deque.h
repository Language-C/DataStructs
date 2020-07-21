#pragma once

#include <Types.h>
#include <ClassMeta.h>

C_API void* DequeCreate(const ClassMeta* const meta);
C_API void DequeDestroy(void** deque);

C_API Bool DequePushBack(void* const deque, void* const data);
C_API Bool DequePushFront(void* const deque, void* const data);

C_API void DequePopBack(void* const deque);
C_API void DequePopFront(void* const deque);

C_API Bool DequeIsEmpty(const void* const deque);
C_API Sizetype DequeSize(const void* const deque);

C_API void* DequePickFront(const void* const deque);
C_API void* DequePickFront(const void* const deque);