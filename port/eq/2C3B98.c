#include "common.h"

s32 func_002C3C78(s32 arg0, s32 arg1);
s32 func_002C3CB8(u8 *arg0, s32 arg1);
s32 func_002DC538(s32 arg0);

void func_002C3B98(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 a0;

    s0 = arg2;
    s1 = arg1;
    *arg3 = 0;
    s2 = *(s32 *)(arg0 + 0x28);
    if (s0 >= s2 + 3) {
        if (func_002C3C78(s1, s2) != 0) {
            *arg3 = s2;
            return;
        }
    }
    s2 = 0;
    if (s0 >= 4) {
        do {
            a0 = s1;
            s1 += 1;
            if (func_002DC538(a0) & 0xD0000) {
                *arg3 = s2;
                return;
            }
            s0 -= 1;
            s2 += 1;
        } while (s0 >= 4);
    }
    if ((u32)(s0 - 1) < 3U) {
        if (func_002C3CB8(arg0, s1 + s0) != 0) {
            s2 += s0;
        }
    }
    *arg3 = s2;
}
