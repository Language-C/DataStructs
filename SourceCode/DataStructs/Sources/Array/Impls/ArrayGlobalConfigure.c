#include <stdlib.h>

#include "../ArrayGlobalConfigure.h"

ArrayGlobalConfigure ArrayGlobalConfig = {
    malloc,
    free,
    32U
};

C_API ArrayGlobalConfigure* ArrayGetGlobalConfig() {
    return &ArrayGlobalConfig;
}
