#include "common.h"

void func_002E06C0(s32 arg0, s32 arg1, s32 arg2);

u32 func_002C5860(u8 *arg0, s32 arg1, u32 arg2) {
    s32 s3;
    u32 s0;
    s32 s1;
    s32 s2;
    s32 a1;

    s3 = *(*(s32 **)(arg0 + 0x1FC0));
    if (s3 == 0) {
        return 0;
    }
    s0 = arg2 >> 2;
    if (s0 >= 0x11U) {
        s0 = 0x10U;
    }
    s2 = 0;
    if (s0 != 0) {
        s1 = arg1;
        a1 = 0;
        do {
            s2 += 1;
            func_002E06C0(s3, a1, s1);
            s1 += 4;
            a1 = s2;
        } while (s2 < (s32)s0);
    }
    return s0;
}
