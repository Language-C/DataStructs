#pragma once

#ifdef WANT_TO_EXTEND_ARRAY

#include <Types.h>
#include <ClassMeta.h>

typedef struct Array {
    Sizetype Capacity;
    const ClassMeta* Configure;
    char* Data;
} Array;

typedef struct ArrayParams {
    Sizetype Capacity;
    const ClassMeta* Configure;
} ArrayParams;

#ifdef self
#undef self
#endif // self

#define self ((Array*)(array))

#ifdef selfPtr
#undef selfPtr
#endif // selfPtr
#define selfPtr ((Array*)(*array))

#endif // WANT_TO_EXTEND_ARRAY
