#include "common.h"

s32 func_0024ACE8(s32 arg0, s32 *arg1, s32 arg2) {
    s32 t0 = *arg1;
    s32 t2 = 1;
    s32 st;
    s32 v0 = t0 + 1;

    for (;;) {
        if (v0 < 7) {
            *arg1 = v0;
        } else {
            *arg1 = 0;
        }
        st = *arg1;
        if (t0 == st) {
            t2 = 0;
            break;
        }
        if ((u32)(*(s32 *)(arg0 + (arg2 * 7 + st) * 0x2C) - 0x83) >= 3) {
            break;
        }
        v0 = st + 1;
    }
    return t2;
}
