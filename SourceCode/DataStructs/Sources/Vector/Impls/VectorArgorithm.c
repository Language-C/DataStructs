#include <memory.h>
#include <omp.h>

#include "../VectorArgorithm.h"

C_API Vector* VectorDup(Vector* self, StructDupFunc structDupFunc) {
    int i;
    Vector *dup = VectorCreateWithCapacity(self->Capacity);
    if (!dup) {
        return Null;
    }

#pragma omp parallel for
    for (i = 0; i < (int)self->Size; ++i) {
        dup->DataPtr[i].Data = structDupFunc(self->DataPtr[i].Data);
    }
    dup->Size = self->Size;

    return dup;
}
