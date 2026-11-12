#include "common.h"

void *memcpy(void *, const void *, unsigned int);
extern u8 D_00377AC0 __attribute__((section(".data")));

/* 0x002ACA20: copies the 0x160-byte table D_00377AC0 (44 pairs of words: key, value) and returns the value
 * paired with arg0 (the first key equal to arg0), or 0x33D4 when no key matches. */
s32 func_002ACA20(s32 arg0) {
    u8 tbl[0x160];
    s32 k;

    memcpy(tbl, &D_00377AC0, 0x160);
    for (k = 0; k < 0x2C; k++) {
        if (arg0 == *(s32 *)(tbl + k * 8)) {
            return *(s32 *)(tbl + k * 8 + 4);
        }
    }
    return 0x33D4;
}
