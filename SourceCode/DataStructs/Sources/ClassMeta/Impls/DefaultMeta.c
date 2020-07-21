#include <ClassOriented/ClassOriented.h>

#include "../ClassMeta.h"

ClassMeta VoidMetadata = {
    sizeof(void*),
    Null,
    Null,
    Null,
    Null
};

C_API ClassMeta* VoidMeta() {
    return &VoidMetadata;
}