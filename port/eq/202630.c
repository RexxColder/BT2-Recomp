#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212820(s32 arg0);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
s32 BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 BtlKiBlast_GetHitsOf_240980(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
void func_00210000(s32 arg0, s32 arg1);
void func_00212DD8(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211418(s32 arg0, s32 arg1);
s32 func_00240040(s32 arg0);
extern f32 D_003858EC;

s32 func_00202630(s32 arg0, void *arg1) {
    s32 sp[4];
    s32 s0;
    s32 s1;
    s32 v;
    f32 f20;
    f32 w;

    s0 = (s32)arg1;
    s1 = func_00211288(arg0);
    if (*(s32 *)(s0 + 0xC) != 0) {
        return 0;
    }
    if (*(s32 *)(s0 + 0x54) == 1) {
        return 0;
    }
    if (*(s32 *)(s0 + 0x68) == 0) {
        return 0;
    }
    if (func_00240040(s0) & 2) {
        return 0;
    }
    if (func_00211310(s1, 3, 0x100) == 0) {
        return 0;
    }
    if (func_00212820(s1) == 0) {
        return 0;
    }
    f20 = func_00200550(s1, s0, (s32)sp);
    w = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos(s1) + 0x14) - f20);
    if (((w < 0.0f) ? -w : w) < D_003858EC) {
        return 0;
    }
    v = BtlKiBlast_GetHitsOf_240980(s0);
    if (v >= 0x10 || v < 0xE) {
        func_00210000(s0 + 0x20, 0x13);
    } else {
        func_00210000(s0 + 0x20, (BtlChar_FrameMod(2) == 0) ? 0xD : 0xC);
    }
    func_00212DD8(s1, 0xB);
    func_002113C0(s1, 0x10, 0x02000000, 1);
    *(s32 *)(s1 + 0x1478) = *(s32 *)(s1 + 0x1478) + 1;
    func_00211418(s1, 0x02000000);
    return 1;
}
