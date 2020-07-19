#include "../ClassMeta.h"

C_API Bool ClassMetaIsValid(const ClassMeta* const config) {
    if (!config) {
        return False;
    }

    if (config->BytesOfValueClass == 0) {
        return False;
    }

    if (!config->Constructor) {
        return False;
    }

    if (!config->CopyConstruct) {
        return False;
    }

    return True;
}