#include "../ClassInstance.h"
#include "../ClassGlobalConfigure.h"

static void AfterCreateInstances(char* instances, const Sizetype size,
    const ClassMeta* const config) {
    char* end = &instances[config->BytesOfValueClass * size];

    if (config->Constructor) {
        for (; instances < end; instances += config->BytesOfValueClass) {
            config->Constructor(instances);
        }
    }
}

static void BeforeFreeInstances(char* instances, const Sizetype size,
    const ClassMeta* const config) {
    char* end = &(instances[config->BytesOfValueClass * size]);

    if (config->Destructor) {
        for (; instances < end; instances += config->BytesOfValueClass) {
            config->Destructor(instances);
        }
    }
}

C_API void* NewInstance(const ClassMeta* const config) {
    void* instance = Null;

    if (!config || config->BytesOfValueClass == 0) {
        return Null;
    }

    instance = ClassGlobalConfig()->Malloc(config->BytesOfValueClass);
    if (instance && config->Constructor) {
        config->Constructor(instance);
    }
    return instance;
}

C_API void* NewInstanceWithParams(const ClassMeta* const config, void* const params) {
    void* instance = Null;

    if (!config || config->BytesOfValueClass == 0) {
        return Null;
    }

    instance = ClassGlobalConfig()->Malloc(config->BytesOfValueClass);
    if (instance && config->ParamConstructor) {
        config->ParamConstructor(instance, params);
    }
    return instance;
}

C_API void* NewInstances(const Sizetype size, const ClassMeta* const config) {
    char* instances = Null;

    if (size == 0 || !config || config->BytesOfValueClass == 0) {
        return Null;
    }

    instances = (char*)ClassGlobalConfig()->Malloc(config->BytesOfValueClass * size);
    if (instances) {
        AfterCreateInstances(instances, size, config);
    }

    return instances;
}

C_API void FreeInstance(void* const instance, const ClassMeta* const config) {
    if (instance) {
        if (config && config->Destructor) {
            config->Destructor(instance);
        }
        ClassGlobalConfig()->Free(instance);
    }
}

C_API void FreeInstances(void* const instances, const Sizetype size,
    const ClassMeta* const config) {
    if (instances && size > 0) {
        BeforeFreeInstances((char*)instances, size, config);
        ClassGlobalConfig()->Free(instances);
    }
}
