#include "common.h"

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
void func_0028BB60(s32 arg0);
extern u8 *D_003876A0;
extern u8 D_00387ABC;
extern u8 D_00387ABD;

s32 func_00273970(s32 arg0, s32 arg1) {
    s32 s3;
    s32 v;
    u8 *s0;

    s3 = arg0 & 0xFF;
    s0 = D_003876A0;
    if ((u32)(arg1 - 0x3E07) < 2U) {
        if (D_00387ABC != 1) {
            D_00387ABC = 1;
            v = func_00100ED0(arg1, *(s32 *)(s0 + 8), s3 != 0);
            *(s32 *)(s0 + 4) = v;
            *(s32 *)(s0 + 8) = v;
            D_00387ABD = 1;
            return 1;
        }
        *(s32 *)(s0 + 4) = *(s32 *)(s0 + 8);
        D_00387ABD = 1;
        return 0;
    }
    if (D_00387ABD == 0) {
        v = *(s32 *)(s0 + 4);
        if (v != 0) {
            func_0028BB60(v);
            *(s32 *)(s0 + 4) = 0;
        }
    }
    *(s32 *)(s0 + 4) = func_00100ED0(arg1, 0, s3 != 0);
    D_00387ABD = 0;
    return 1;
}
