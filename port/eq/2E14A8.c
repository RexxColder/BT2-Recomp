#include "common.h"

u8 *func_002DCFE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002DCE50(u8 *arg0);

s32 func_002E14A8(s32 arg0, s32 arg1) {
    u8 *s0;
    u8 *s2;
    s32 s1;
    s32 v1;

    s1 = arg1;
    s2 = (u8 *)arg0;
    s0 = func_002DCFE8(arg0, arg1, 0x40);
    if (s0 == NULL) {
        return 0;
    }
    s0 += 4;
    v1 = (s32)(s0 - s2);
    s2 = s0;
    s1 -= v1;
    if (s1 <= 0) {
        return 0;
    }
    s0 = func_002DCFE8((s32)s2, s1, -1);
    if (s0 == NULL) {
        return 0;
    }
    if ((func_002DCE50(s0) & 0x10) == 0) {
        return 0;
    }
    s0 += 4;
    s1 -= (s32)(s0 - s2);
    if (s1 <= 0) {
        return 0;
    }
    return ((s0[0] >> 4) == 1);
}
