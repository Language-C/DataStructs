#pragma once

#include <ClassMeta.h>

C_API void* NewInstance(const ClassMeta* const config);
C_API void* NewInstanceWithParams(const ClassMeta* const config, void* const params);
C_API void* NewInstances(const Sizetype size, const ClassMeta* const config);

C_API void FreeInstance(void* const instance, const ClassMeta* const config);
C_API void FreeInstances(void* const instances, const Sizetype size,
    const ClassMeta* const config);