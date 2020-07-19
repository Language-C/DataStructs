#pragma once

#include <ClassMeta.h>

C_API void* ArrayCreate(Sizetype const capacity, const ClassMeta* const configure);

C_API void ArrayDestroy(void** const array);

C_API void ArrayFill(void* const array, const void* const data);

C_API Bool ArrayIsValid(const void* const array);

C_API void* ArrayGet(const void* const array, const Sizetype idx);
C_API Bool ArraySet(const void* const array,
    const Sizetype idx, const void* const data);
