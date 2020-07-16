#pragma once

#include "../BasicTypes/Types.h"

typedef struct VectorNode {
    void* Data;
} VectorNode;

typedef struct Vector {
    VectorNode* DataPtr;
    UInt Size;
    UInt Capacity;
} Vector;
