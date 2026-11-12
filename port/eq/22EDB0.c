#include "common.h"

s32 func_00212878();
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212820(s32 arg0);
f32 func_00217360(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);
s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
f32 func_00273048();
s32 func_00203118(s32 arg0);
void BtlAnim_SetBlend(s32 arg0, f32 farg0);
void func_00212DD8(s32 arg0, s32 arg1);
s32 func_0023C780(s32 arg0);
extern f32 D_0038676C;
extern f32 D_00386770;

s32 func_0022EDB0(s32 arg0) {
    u8 *s0;
    u8 *s1;
    u8 *p;
    s32 v;

    s1 = (u8 *)arg0;
    if (func_00212878(arg0) == 0) {
        goto L_EE50;
    }
    if (func_00211310(arg0, 0, 4) == 0) {
        goto L_EF9C;
    }
    p = (u8 *)*(s32 *)(s1 + 0x1530);
    if ((*(s32 *)(p + 0xE80) & 0x80) == 0) {
        goto L_EE38;
    }
    if (func_00212820(arg0) == 0) {
        goto L_EF84;
    }
    if (func_00211310(arg0, 1, 0x80000) != 0) {
        goto L_EF84;
    }
    if (BtlPad_Test48(arg0, 8) == 0) {
        goto L_EF84;
    }
    goto L_EECC;

L_EE38:
    if (func_00211310(arg0, 0, 0x8000) != 0) {
        goto L_EF84;
    }
    goto L_EF9C;

L_EE50:
    if (func_00217360(arg0) < 2.0f) {
        goto L_EE94;
    }
    if (func_00211310(arg0, 0, 4) != 0) {
        goto L_EE94;
    }
    p = (u8 *)*(s32 *)(s1 + 0x1530);
    if ((*(s32 *)(p + 0xE54) & 0x20) != 0) {
        goto L_EE94;
    }
    goto L_EF9C;

L_EE94:
    if (func_00212820(arg0) == 0) {
        goto L_EEEC;
    }
    if (func_00211310(arg0, 1, 0x80000) != 0) {
        goto L_EEEC;
    }
    if (BtlPad_Test48(arg0, 8) == 0) {
        goto L_EEEC;
    }

L_EECC:
    v = func_0023F410(arg0);
    return ((v & 0x1000) == 0) ? 0x29 : 0x27;

L_EEEC:
    p = (u8 *)*(s32 *)(s1 + 0x1530);
    if ((*(s32 *)(p + 0xE80) & 0x40) == 0) {
        goto L_EF80;
    }
    if (func_00211310(arg0, 0, 4) == 0) {
        goto L_EF9C;
    }
    if (BtlMember_IsHealthEmpty_2127F8(arg0) == 0) {
        goto L_EF9C;
    }
    s0 = (u8 *)BtlChar_GetPos(arg0);
    if (!(func_00273048() < *(f32 *)(s0 + 4))) {
        goto L_EF9C;
    }
    if (func_00211310(arg0, 0xA, 0x10) != 0) {
        goto L_EF9C;
    }
    if (func_00203118(arg0) <= 0) {
        goto L_EF9C;
    }
    if (func_00211310(arg0, 0, 0x400000) == 0) {
        goto L_EF9C;
    }
    return 0x33;

L_EF80:
L_EF84:
    func_00212DD8(arg0, 0);
    return 0xA7;

L_EF9C:
    if (BtlPad_Test4C(arg0, 0xB) == 0) {
        goto L_F008;
    }
    if (func_00212820(arg0) == 0) {
        goto L_F004;
    }
    if (func_00211310(arg0, 1, 0x40000) != 0) {
        goto L_F008;
    }
    if ((func_0023F410(arg0) & 0x1000) != 0) {
        goto L_F008;
    }
    p = (u8 *)BtlMember_GetActiveGauge(arg0);
    if (*(u8 *)(p + 0x29) == 0) {
        goto L_F098;
    }
    if (*(s32 *)(s1 + 0xB94) <= 0) {
        goto L_F098;
    }

L_F004:
L_F008:
    if (func_00211310(arg0, 0, 0x100) == 0) {
        goto L_F040;
    }
    BtlAnim_SetBlend(arg0, D_0038676C);
    return func_0023C780(arg0);

L_F040:
    if (func_00211310(arg0, 0, 0x20) == 0) {
        goto L_F064;
    }
    if (func_00212820(arg0) != 0) {
        goto L_F098;
    }

L_F064:
    if (func_00212878() == 0) {
        return -1;
    }
    if (func_00211310(arg0, 0, 0x40) == 0) {
        return -1;
    }
    if (func_00212820(arg0) == 0) {
        return -1;
    }
    goto L_F098;

L_F098:
    BtlAnim_SetBlend(arg0, D_00386770);
    return 0x26;
}
