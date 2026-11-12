#include "common.h"

/* 0x001EBCC0: index of arg1 in the pool array (arg0+0: array of 4-byte entries, arg0+4: capacity s16);
 * returns the capacity when it is not found. */
s32 func_001EBCC0(u8 *arg0, s32 arg1) {
    s32 cap = *(s16 *)(arg0 + 4);
    s32 *entries;
    s32 i;

    if (cap <= 0) {
        return 0;
    }
    entries = *(s32 **)arg0;
    for (i = 0; i < cap; i++) {
        if (entries[i] == arg1) {
            return i;
        }
    }
    return i;
}
