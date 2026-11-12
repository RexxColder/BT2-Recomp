#include "common.h"

/* 0x002B2DF8: t2 = arg0[+8], t3 = arg0[+0xC]; arg1 = t2, arg2 = t3, arg4 = t3 / 2 (truncated), arg3 = the value
 * (t2 / 2 + 0x1F, or + 0x3E when that is negative) rounded down to a multiple of 32. */
void func_002B2DF8(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    s32 t2 = *(s32 *)(arg0 + 0x8);
    s32 t3 = *(s32 *)(arg0 + 0xC);
    s32 q = t2 / 2;
    s32 v0 = q + 0x1F;

    if (v0 < 0) {
        v0 = q + 0x3E;
    }
    v0 = v0 & ~0x1F;
    *arg3 = v0;
    *arg4 = t3 / 2;
    *arg1 = t2;
    *arg2 = t3;
}
