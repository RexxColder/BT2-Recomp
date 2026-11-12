#include "m2c_macros.h"

extern void StgAabb_SetEmpty(s32 arg0);
extern void ColBox_AddPointKeepW(s32 arg0, s32 arg1);

void ColBounds_OfObb(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 a1;

    StgAabb_SetEmpty(arg0);
    s0 = arg1 + 0x110;
    s1 = 7;
    a1 = s0;
    do {
        s0 += 0x10;
        s1 -= 1;
        ColBox_AddPointKeepW(arg0, a1);
        a1 = s0;
    } while (s1 >= 0);
}
