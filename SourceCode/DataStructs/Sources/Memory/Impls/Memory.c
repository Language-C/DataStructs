#include "../Memory.h"

C_API Bool MemCopy(void* const dst, rsize_t const dstSize, void* const src, rsize_t const srcSize) {
    return (dst && src && dst != src) &&
        (dstSize > 0 && srcSize > 0) &&
        (0 == memcpy_s(dst, dstSize, src, srcSize)) ? True : False;
}
