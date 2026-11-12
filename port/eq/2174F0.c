#include "common.h"

/* 0x002174F0: arg1 = low half of arg0; arg2 = high half, or -1 when the high half is 0. */
void func_002174F0(u32 arg0, s32 *arg1, u32 *arg2) {
    u32 hi = arg0 >> 0x10;

    *arg1 = arg0 & 0xFFFF;
    *arg2 = hi;
    if (hi == 0) {
        *arg2 = -1U;
    }
}
