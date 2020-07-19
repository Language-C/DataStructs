#include <stdlib.h>

#include "../ClassGlobalConfigure.h"

ClassGlobalConfigure GlobalConfig = {
    free, malloc
};

C_API const ClassGlobalConfigure* ClassGlobalConfig() {
    return &GlobalConfig;
}
