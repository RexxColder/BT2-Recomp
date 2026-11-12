#include "common.h"

s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_0036CC20[] __attribute__((section(".data")));

s32 func_0011EC10(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 *p;
    s32 off;
    s32 i;
    s32 v;
    s32 r;
    s32 s0v;

    s0v = (arg3 & 0xFFFF) & 0x10;
    if (arg2 < 0 || !(arg2 < 0x2D)) {
        off = 0;
    } else {
        off = arg2 * 8;
    }
    p = (s16 *)(D_0036CC20 + off);
    for (i = 0; i < 4; i++) {
        v = *p;
        p += 1;
        if (v == arg1) {
            r = func_00126058(arg0, 2, 2);
            if (r != 0 || s0v != 0) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
