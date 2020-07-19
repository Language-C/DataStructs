#pragma once

#define Constructor(clazz, param) \
    void clazz##Constructor(void* const param)
#define ParamConstructor(clazz, selfName, params) \
    void clazz##ParamConstructor(void* const selfName, const void* const params)
#define CopyConstructor(clazz, dst, src) \
    void clazz##CopyConstructor(void* const dst, const void* const src)

#define Destructor(clazz, selfName) \
    void clazz##Destructor(void* const selfName)
