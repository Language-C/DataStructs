#pragma once

#include "ArrayStruct.h"

C_API Array* ArrayCreate(ArrayConfigure* configure);
C_API Array* ArrayCreateWithoutInitialize(ArrayConfigure* configure);