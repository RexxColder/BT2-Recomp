#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
f32 BtlCharApi_GetHeight(s32 arg0);
void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlPad_Test48(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
void func_002100C0(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212820(s32 arg0);
f32 func_00217330(s32 arg0);
s32 func_0023BDA8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023C780(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
extern f32 D_0038601C;
extern f32 D_00386020;
extern f32 D_00386024;
extern f32 D_00386028;
extern f32 D_0038602C;
extern f32 D_00386030;
extern f32 D_00386034;

s32 func_00222308(s32 arg0) {
    s32 v;
    s32 r;
    s32 s2;
    f32 f20;
    f32 f;

    v = BtlObjXf_Update(arg0);
    if (v == 0xD1) {
        goto block9;
    }
    if (v < 0xD2) {
        if (v != 0xCE) {
            return -1;
        }
        goto block9;
    }
    if (v >= 0xFD) {
        return -1;
    }
    if (v < 0xFB) {
        return -1;
    }

    f = func_001FA318(arg0);
    if (D_00386028 < f) {
        r = func_0023C798(arg0, 3);
        if (r == -1) {
            s2 = func_0023BDA8(arg0, 0x420000);
            if (s2 == r) {
                goto block37;
            }
            BtlAnim_SetBlend(D_00386030, arg0);
            return s2;
        }
        BtlAnim_SetBlend(D_0038602C, arg0);
        return r;
    }

block37:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00386034, arg0);
    func_002113C0(arg0, 0, 2, 1);
    return func_0023C710(arg0);

block9:
    f20 = func_00217330(arg0);
    if (BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534)) < f20) {
        if (D_0038601C < func_001FA318(arg0)) {
            BtlAnim_SetBlend(D_00386020, arg0);
            return func_0023C780(arg0);
        }
        return -1;
    }

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00386024, arg0);
    if (func_00212820(arg0) == 0) {
        goto L22460;
    }
    if (func_00211310(arg0, 1, 0x80000) != 0) {
        goto L22464;
    }
    if (BtlPad_Test48(arg0, 0xC) != 0) {
        func_002113C0(arg0, 0, 2, 1);
        return 0x28;
    }
    if (BtlPad_Test48(arg0, 0xD) != 0) {
        return 0x27;
    }

L22460:
L22464:
    func_002100C0(arg0, 2);
    return func_0023C780(arg0);
}
