#include "common.h"

s32 func_002C23D0(void *a0);
s32 func_002C2428(void *a0, void *a1);
s32 func_002C2480(void *a0, void *a1, void *a2);

s32 func_002C2318(void *arg0, s32 arg1, void *arg2, void *arg3, void *arg4) {
    u8 *s0;
    u8 *s1;
    s32 r4;

    s0 = (u8 *)arg2 - 6;
    s1 = (u8 *)arg3 + 6;
    *(s32 *)arg4 = 0;
    if (arg1 != 2) {
        return 0;
    }
    if (func_002C23D0(s0) != 0) {
        s0 -= 0xC;
    } else {
        s0 -= 2;
        s1 += 2;
        if (func_002C23D0(s0) == 0) {
            return 0;
        }
        s0 -= 0xC;
    }
    s1 += 0xC;
    if (func_002C2428(s0, s1) == 0) {
        return 0;
    }
    r4 = func_002C2480(arg0, s0, s1);
    *(s32 *)arg4 = r4;
    return 1;
}
