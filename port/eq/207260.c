#include "common.h"

/* 0x00207260: floor(log2(a0)) for a0 >= 2 (number of halvings after the first), 0 if a0 < 2. */
s32 func_00207260(s32 a0) {
    s32 n = a0 >> 1;
    s32 count = 0;
    if (n == 0) {
        return 0;
    }
    do {
        n >>= 1;
        count++;
    } while (n != 0);
    return count;
}
