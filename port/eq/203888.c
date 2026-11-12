#include "common.h"

u8 *BtlMember_GetActiveGauge(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_00203888(s32 arg0, s32 arg1, s32 arg2) {
    u8 *g;
    s32 v;
    s32 s0;

    g = BtlMember_GetActiveGauge(arg0, arg1, arg2);
    s0 = 0;
    if (arg2 != 0 || func_00211310(arg0, 0, 0x800) == 0) {
        v = *(s32 *)(g + 0xC) - arg1;
        *(s32 *)(g + 0xC) = v;
        if (v < 0) {
            *(s32 *)(g + 0xC) = 0;
            s0 = 1;
        }
        *(s32 *)(g + 0x1C) = 0;
        return s0;
    }
    return 0;
}
