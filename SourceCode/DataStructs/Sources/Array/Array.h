#pragma once

#include <ClassMeta.h>

#include "ArrayMeta.h"

C_API void* ArrayCreate(const Sizetype capacity,
    const ClassMeta* const meta);

C_API void ArrayDestroy(void** const array);

C_API void ArrayFill(void* const array, const void* const data);

C_API Bool ArrayIsValid(const void* const array);

C_API void* ArrayGet(void* const array, const Sizetype idx);
C_API Bool ArraySet(void* const array, const Sizetype idx, void* const data);
