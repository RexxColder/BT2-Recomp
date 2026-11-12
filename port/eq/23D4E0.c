#include "common.h"

s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlMember_HasKi(s32 arg0, s32 arg1);
s32 func_00208738(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002411E0(s32 arg0, s32 arg1);
s32 func_00241718(s32 arg0, s32 arg1);
extern u8 *D_003876A0;

s32 func_0023D4E0(s32 arg0, s32 arg1) {
    s32 s2;
    s32 v0;
    s32 v0_2;
    f32 f1;

    v0 = func_00208738(*(s32 *)(arg0 + 0x1534), arg1);
    if (v0 == 0) {
        return 0;
    }
    v0 = func_00211310(arg0, 0, 1);
    if (v0 == 0) {
        return 0;
    }
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x2C) != 0) {
        return 0;
    }
    if (arg1 == 4) {
        v0 = func_00211310(arg0, 0, 0x800);
        if (v0 == 0) {
            return 0;
        }
    }
    s2 = func_002411E0(arg0, arg1);
    v0 = BtlMember_HasKi(arg0, func_00241718(arg0, arg1));
    if (v0 == 0) {
        return 0;
    }
    v0_2 = s2 & 0x400;
    if (s2 & 0x40000) {
        f1 = *(f32 *)(arg0 + 0xAC4);
        if (f1 <= 0.0f) {
            return 0;
        }
    }
    if (v0_2 == 0) {
        return 1;
    }
    if ((u32)(*(s32 *)(D_003876A0 + 0xB8) - 4) < 2u) {
        return 1;
    }
    if (*(s32 *)(BtlMember_GetActiveGauge(arg0) + (arg1 * 4) + 0x30) <= 0) {
        return 1;
    }
    return 0;
}
