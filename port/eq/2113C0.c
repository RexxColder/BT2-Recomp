#include "common.h"

/* 0x002113C0: w = (s32 *)(arg0 + arg1 * 4 + 0x2B0): if (arg3 & 0xFF) == 0, *w &= ~arg2, else *w |= arg2;
 * then (arg0 + arg1 * 4 + 0x2F4) |= arg2. */
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *w = (s32 *)(arg0 + arg1 * 4 + 0x2B0);
    s32 *x = (s32 *)(arg0 + arg1 * 4 + 0x2F4);

    if ((arg3 & 0xFF) == 0) {
        *w = *w & ~arg2;
    } else {
        *w = *w | arg2;
    }
    *x = *x | arg2;
}
