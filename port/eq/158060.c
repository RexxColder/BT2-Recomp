#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 EftShot_TestBits(u8 *arg0, s32 arg1);
extern u8 D_0036E1D8[] __attribute__((section(".data")));

/* 0x00158060(obj): copies the six words at D_0036E1D8 to the stack and returns the OR of those words for which
 * EftShot_TestBits(obj, word) is nonzero. */
s32 func_00158060(u8 *arg0) {
    s32 tab[6];
    s32 res = 0;
    s32 i;

    memcpy(tab, D_0036E1D8, 0x18);
    for (i = 0; i < 6; i++) {
        if (EftShot_TestBits(arg0, tab[i]) != 0) {
            res |= tab[i];
        }
    }
    return res;
}
