#include "common.h"

s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlMember_HasBlast(s32 arg0, s32 arg1);
s32 func_00202DC0(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212690(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023F4A8(s32 arg0, s32 arg1);
s32 func_0023F4C0(s32 arg0, s32 arg1);
s32 func_0023F500(s32 arg0, s32 arg1);
extern s32 D_00387F2C;

s32 func_0023DAE8(s32 arg0, s32 arg1) {
    s32 s1;
    s32 s3;
    s32 temp_v0;
    s32 var_v0_2;

    if (func_00211310(arg0, 0xA, 0x10) != 0) {
        return 0;
    }
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x2C) != 0) {
        return 0;
    }
    if (*(u8 *)(func_00202DC0(arg0) + 9) == 0) {
        return 0;
    }
    s1 = func_0023F4A8(arg0, arg1);
    s3 = func_0023F4C0(arg0, arg1);
    temp_v0 = func_0023F500(arg0, arg1);
    if (s1 == 0xFF) {
        return 0;
    }
    if (s3 == 0xFF) {
        return 0;
    }
    if (BtlMember_HasBlast(arg0, temp_v0) == 0) {
        return 0;
    }
    if (func_00212690(arg0, arg1, 0, 0) == 0) {
        return 0;
    }
    if (s1 >= 0x62) {
        var_v0_2 = (s1 * 4) + 0x25E4;
    } else {
        var_v0_2 = (s1 * 4) + 0x25E8;
    }
    return *(s16 *)(D_00387F2C + var_v0_2 + 2) > 0;
}
