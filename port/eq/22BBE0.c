#include "common.h"

s32 func_00217488(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlChar_GetPos(s32 arg0);
void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00218128(s32 arg0, s32 arg1);
f32 func_00207E80(s32 arg0);
f32 func_00207E88(s32 arg0);
s32 func_001FA1D0(s32 arg0, f32 farg0);
f32 func_002175B0(s32 arg0);
void BtlOpp_GetDelta(s32 arg0, s32 arg1);
f32 atan2f(f32 farg0, f32 farg1);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_00386590;
extern f32 D_00386594;
extern f32 D_00386598;

s32 func_0022BBE0(s32 arg0) {
    f32 sp[4];
    u8 *pos;
    s32 v0;
    f32 f1;
    f32 f20;
    f32 a;
    f32 b;

    if (func_00217488(arg0) == 0x10 && BtlObjXf_Update(arg0) == 0x24) {
        if (BtlPad_Test48(arg0, 7) != 0) {
            if (BtlPad_Test4C(arg0, 4) != 0) {
                pos = (u8 *)BtlChar_GetPos(arg0);
                v0 = 0x13;
                goto L_scale;
            }
            if (BtlPad_Test4C(arg0, 5) != 0) {
                pos = (u8 *)BtlChar_GetPos(arg0);
                v0 = 0x14;
                goto L_scale;
            }
        }
        goto L_BC90;
    }
    goto L_BD78;

L_scale:
    *(f32 *)(pos + 0xC0) = *(f32 *)(pos + 0xC0) * 0.5f;
    return v0;

L_BC90:
    if (BtlPad_Test48(arg0, 0) == 0) {
        goto L_BD28;
    }
    BtlAnim_SetBlend(arg0, D_00386590);
    if (BtlPad_Test48(arg0, 8) == 0) {
        return 0x62;
    }
    a = func_00207E80(arg0);
    f20 = (a < 0.0f) ? -a : a;
    b = func_00207E88(arg0);
    f1 = (b < 0.0f) ? -b : b;
    if (f1 < f20) {
        if (func_00207E80(arg0) < 0.0f) {
            return 0x5E;
        }
        return 0x5F;
    }
    if (func_00207E88(arg0) < 0.0f) {
        return 0x60;
    }
    return 0x61;

L_BD28:
    if (func_00211310(arg0, 0, 0x800) != 0) {
        if (func_00218128(arg0, 5) != 0) {
            if (BtlPad_Test48(arg0, 1) != 0) {
                BtlAnim_SetBlend(arg0, D_00386594);
                return 0x6E;
            }
        }
    }
    goto L_BD78;

L_BD78:
    if (BtlObjXf_Update(arg0) != 0x20) {
        goto L_BE8C;
    }
    if (func_00211310(arg0, 1, 1) != 0) {
        goto L_BE8C;
    }
    if (func_001FA1D0(arg0, 0.5f) == 0) {
        goto L_BE8C;
    }
    if (BtlPad_Test48(arg0, 7) == 0) {
        goto L_BE8C;
    }
    if (BtlPad_Test48(arg0, 8) == 0) {
        if (func_00211310(arg0, 0, 1) != 0) {
            if (func_00217488(arg0) == 0xF) {
                return 0x10;
            }
        }
        goto L_BE8C;
    }
    f20 = func_002175B0(arg0);
    if (func_00217488(arg0) == 0x10) {
        BtlOpp_GetDelta(arg0, (s32)sp);
        f1 = BtlUtil_WrapAngle(f20 - atan2f(sp[0], sp[2]));
    } else {
        pos = (u8 *)BtlChar_GetPos(arg0);
        f1 = BtlUtil_WrapAngle(f20 - *(f32 *)(pos + 0xB4));
    }
    f1 = (f1 < 0.0f) ? -f1 : f1;
    if (1.0f < f1) {
        return 0xF;
    }
    goto L_BE8C;

L_BE8C:
    if (func_001FA288(arg0, 0x25) != 0) {
        BtlAnim_SetBlend(arg0, 0.5f);
        return func_0023C710(arg0);
    }
    if (func_001FA288(arg0, 0x20) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386598);
    return func_0023C710(arg0);
}
