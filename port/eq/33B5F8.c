#include "common.h"

/* 0x0033B5F8 __fixdfdi (libgcc): double -> s64 truncated toward zero (the soft-float dpcmp/dpsub/__fixunsdfdi chain
 * of the original gives the same result for in-range values). */
s64 __fixdfdi(double arg0) {
    return (s64)arg0;
}
