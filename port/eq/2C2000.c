#include "common.h"

void func_002C20D0(s32 arg0, s32 arg1);

s32 func_002C2000(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s0;
    u8 *s1;
    s32 s2;

    s0 = (u8 *)arg1;
    s1 = (u8 *)arg0;
    s2 = arg2;
    if (s2 < 4) {
        return 0;
    }
    for (;;) {
        if (s0[0] != 0xFF) {
            s2 -= 1;
        } else if ((s0[1] & 0xF8) != 0xF8) {
            s2 -= 1;
        } else {
            func_002C20D0(arg0, (s32)s0);
            if (s1[0] == 0) {
                s2 -= 1;
            } else if (s1[2] == 0xF) {
                s2 -= 1;
            } else if (s1[3] != 3) {
                return (s32)s0;
            } else {
                s2 -= 1;
            }
        }
        s0 += 1;
        if (s2 < 4) {
            return 0;
        }
    }
}
