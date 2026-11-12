#include "common.h"

s32 func_002C1BD0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C1C38(s32 arg0, s32 arg1);
s32 func_002C1CB8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C1F58(s32 arg0, s32 arg1, s32 arg2);

void func_002C1AC8(s32 arg0, s32 arg1, s32 arg2) {
    s32 s3;
    s32 s4;
    s32 s6;
    s32 s7;
    s32 v;
    s32 r2;
    s32 tmp;
    s32 s0;
    s32 step;

    s3 = arg1;
    s4 = arg0;
    s6 = s4 + s3;
    s7 = *(s32 *)(arg2 + 0x10);
    for (;;) {
        if (s3 <= 0) {
            return;
        }
        v = func_002C1BD0(s4, s3, 0x40000);
        if (v == 0) {
            return;
        }
        if (((u32)(*(u8 *)(v + 3) + 0x40) & 0xFF) < 0x20U) {
            r2 = func_002C1C38(v, s6 - v);
            tmp = s6 - r2;
            s0 = (tmp < s7) ? tmp : s7;
            if (func_002C1CB8(r2, s0, arg2) != 0) {
                return;
            }
            if (func_002C1F58(r2, s0, arg2) != 0) {
                return;
            }
        }
        step = (v - s4) + 1;
        s3 -= step;
        s4 += step;
    }
}
