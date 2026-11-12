#include "common.h"

s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlMember_HasBlast(s32 arg0, s32 arg1);
s32 func_00202DC0(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023F460(s32 arg0, s32 arg1);
s32 func_0023F478(s32 arg0, s32 arg1);
extern s32 D_00387F2C;
extern u8 *D_003876A0;
extern u8 *D_003876A4;

s32 func_0023D9D0(s32 arg0, s32 arg1) {
    s32 s1;
    s32 temp_a1;
    s32 var_v0_2;
    s32 a2;

    if (func_00211310(arg0, 0xA, 0x10) != 0) {
        return 0;
    }
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x2C) != 0) {
        return 0;
    }
    if (*(u8 *)(func_00202DC0(arg0) + 9) == 0) {
        return 0;
    }
    s1 = func_0023F460(arg0, arg1);
    temp_a1 = func_0023F478(arg0, arg1);
    if (s1 == 0xFF) {
        return 0;
    }
    if (BtlMember_HasBlast(arg0, temp_a1) == 0) {
        return 0;
    }
    if (s1 >= 0x62) {
        var_v0_2 = (s1 * 4) + 0x25E4;
    } else {
        var_v0_2 = (s1 * 4) + 0x25E8;
    }
    a2 = *(s16 *)(D_00387F2C + var_v0_2 + 2) > 0;
    if (*(s32 *)(D_003876A0 + 0xB8) == 4) {
        if (*(s32 *)(D_003876A4 + 0x484) == 0x14) {
            if (((s1 ^ 0x10) == 0) || ((s1 ^ 0x11) == 0)) {
                a2 = 1;
            }
        }
    }
    return a2 != 0;
}
