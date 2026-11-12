#include "common.h"

s32 func_002DCE50();

u8 *func_002DD0F0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 v1;
    s32 mask;
    s32 r;
    u8 b;

    s0 = arg1;
    s1 = arg0;
    s2 = arg1 + arg2;
    v1 = 0;
    mask = arg3;

    if (!(s0 < s2)) {
        return s0;
    }
    b = *s0;
    for (;;) {
        s0 += 1;
        *s1 = b;
        s1 += 1;
        if (v1 == 1) {
            v1 = (b != 0) ? 0 : 2;
        } else if (v1 == 0) {
            if (b == 0) {
                v1 = 1;
            }
        } else if (v1 == 2) {
            if (b == 1) {
                v1 = 3;
            } else if (b != 0) {
                v1 = 0;
            }
        } else if (v1 == 3) {
            r = func_002DCE50((s32)(s0 - 4));
            if ((mask & r) != 0) {
                return s0;
            }
            v1 = 0;
        }
        if (!(s0 < s2)) {
            break;
        }
        b = *s0;
    }
    return s0;
}
