#pragma once

#include "Vector.h"

C_API Vector* VectorDup(Vector* self, StructDupFunc structDupFunc);

C_API void VectorClearAndFreeElements(Vector* self);

C_API Vector* VectorCollect(Vector* self, void* callback);
C_API void    VectorCollectToSelf(Vector* self, void* callback);

// remove who == Null
C_API Vector* VectorCompact(Vector* self);

// add src Vector to the end of self
C_API Vector* VectorConcat(Vector* self, Vector* src);
// dst = src1 + src2
C_API Vector* VectorConcatToNewVector(Vector* src1, Vector* src2);

// count the data inner Vector
C_API Vector* VectorCount(Vector* self, void* data);

C_API Vector* VectorAnd(Vector* vector1, Vector vector2);
C_API Vector* VectorOr(Vector* vector1, Vector vector2);