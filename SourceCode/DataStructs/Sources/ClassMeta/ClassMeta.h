#pragma once

#include "../BasicTypes/Types.h"

typedef struct ClassMeta {
    UInt BytesOfValueClass;

    ClassConstructor Constructor;
    ClassParamConstructor ParamConstructor;

    ClassCopyConstructor CopyConstruct;

    ClassDestructor Destructor;
} ClassMeta;

C_API Bool ClassMetaIsValid(const ClassMeta* const config);

#define MakeClassMeta(clazz) {\
    sizeof(clazz),\
    clazz##Constructor, \
    clazz##ParamConstructor,\
    clazz##CopyConstructor, \
    clazz##Destructor\
}
