#include "../ClassInstance.h"
#include "../ClassGlobalConfigure.h"

static void AfterCreateInstances(char* instances, const Sizetype size,
    const ClassMeta* const meta) {
    char* end = &instances[meta->BytesOfValueClass * size];

    for (; instances < end; instances += meta->BytesOfValueClass) {
        meta->Constructor(instances);
    }
}

static void BeforeFreeInstances(char* instances, const Sizetype size,
    const ClassMeta* const meta) {
    char* end = &(instances[meta->BytesOfValueClass * size]);

    for (; instances < end; instances += meta->BytesOfValueClass) {
        meta->Destructor(instances);
    }
}

C_API void* NewInstance(const ClassMeta* const meta) {
    void* instance = Null;

    if (!meta || meta->BytesOfValueClass == 0) {
        return Null;
    }

    instance = ClassGlobalConfig()->Malloc(meta->BytesOfValueClass);
    if (instance && meta->Constructor) {
        meta->Constructor(instance);
    }
    return instance;
}

C_API void* NewInstanceWithParams(const ClassMeta* const meta, const void* const params) {
    void* instance = Null;

    if (!meta || meta->BytesOfValueClass == 0) {
        return Null;
    }

    instance = ClassGlobalConfig()->Malloc(meta->BytesOfValueClass);
    if (instance && meta->ParamConstructor) {
        meta->ParamConstructor(instance, params);
    }
    return instance;
}

C_API void* NewInstances(const Sizetype size, const ClassMeta* const meta) {
    char* instances = Null;

    if (size == 0 || !meta || meta->BytesOfValueClass == 0) {
        return Null;
    }

    instances = (char*)ClassGlobalConfig()->Malloc(meta->BytesOfValueClass * size);
    if (instances && meta && meta->Constructor) {
        AfterCreateInstances(instances, size, meta);
    }

    return instances;
}

C_API void FreeInstance(void* const instance, const ClassMeta* const meta) {
    if (instance) {
        if (meta && meta->Destructor) {
            meta->Destructor(instance);
        }
        ClassGlobalConfig()->Free(instance);
    }
}

C_API void FreeInstances(void* const instances, const Sizetype size,
    const ClassMeta* const meta) {
    if (instances && size > 0) {
        if (meta && meta->Destructor) {
            BeforeFreeInstances((char*)instances, size, meta);
        }
        ClassGlobalConfig()->Free(instances);
    }
}
