#include <stdlib.h>

#include "../ArrayGlobalConfigure.h"

ArrayGlobalConfigure ArrayGlobalConfig = {
    malloc,
    free
};

C_API ArrayGlobalConfigure* ArrayGetGlobalConfig() {
    return &ArrayGlobalConfig;
}
