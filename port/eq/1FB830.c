#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlCam;
extern f32 D_00385814, D_00385818, D_0038581C, D_00385820, D_00385824, D_00385828, D_0038582C;
extern f32 D_00385830, D_00385834, D_00385838, D_0038583C, D_00385840, D_00385844, D_00385848;
extern f32 D_0038584C, D_00385850, D_00385854;

s32 BtlObjXf_Update(u8 *a0);
void func_003126C8(u8 *a0, s32 a1);
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
s32 func_00211360(u8 *a0, s32 a1, s32 a2);
void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);
void BtlOpp_GetDelta(u8 *a0, u8 *a1);
f32 atan2f(f32 y, f32 x);
f32 BtlUtil_WrapAngle(f32 f12);
f32 func_001FB810(u8 *a0);
s32 BtlPad_Test48(u8 *a0, s32 a1);
s32 BtlPad_Test4C(u8 *a0, s32 a1);
f32 BtlOpp_GetDistance(u8 *a0);
f32 func_00207E70(u8 *a0);
f32 func_00207E78(u8 *a0);
f32 func_00207E80(u8 *a0);

#define F(p, o) (*(f32 *)((p) + (o)))
#define W(p, o) (*(s32 *)((p) + (o)))

void func_001FB830(u8 *a0) {
    u8 sp[0x20];
    s32 v, t, s1, v1;
    f32 f0, f1, f2, f3, f20, f21, f22, f23, f24;
    u8 *cam;

    v = BtlObjXf_Update(a0);
    if (v != 0x155) {
        t = (v < 0x156) ? 0x133 : 0x177;
        if (v != t) func_003126C8(a0 + 0x1C0, *(s32 *)(*(u8 **)(a0 + 0x1530) + 0xF40));
    }
    if (*(u64 *)(D_003876A0 + 0x4D8) & 0x3800) return;

    if (func_00211310(a0, 0, 1)) {
        BtlOpp_GetDelta(a0, sp);
        f0 = atan2f(F(sp, 0), F(sp, 8));
        f20 = BtlUtil_WrapAngle(f0 - F(a0, 0x150));
        if (!func_00211310(a0, 14, 0x40)) f20 = f20 * 0.25f;
        f0 = BtlUtil_WrapAngle(F(a0, 0x150) + f20);
        F(a0, 0x154) = f20;
        F(a0, 0x150) = f0;
        if (func_00211310(a0, 9, 0x1000)) {
            W(a0, 0x160) = 0;
            W(a0, 0x164) = 0;
            W(a0, 0x168) = 0;
            goto tail;
        }
        s1 = 0;
        f22 = func_001FB810(a0);
        f0 = D_00385814;
        if (f22 < f0) f22 = f0;
        if (func_00211360(a0, 0, 1)) {
            f1 = F(a0, 0x158);
            if (0.0f < f1) {
                F(a0, 0x158) = f22;
                f24 = -f22;
            } else {
                f24 = -f22;
                F(a0, 0x158) = f24;
            }
        } else {
            f24 = -f22;
        }
        if (BtlPad_Test48(a0, 0x16)) { F(a0, 0x158) = f24; s1 = 1; }
        if (BtlPad_Test48(a0, 0x17)) { F(a0, 0x158) = f22; s1 = 1; }
        f21 = F(a0, 0x154);
        if (D_00385818 < f21) f21 = f21 - D_0038581C;
        if (f21 < D_00385820) f21 = f21 + D_00385824;
        v1 = W(a0, 0x1538);
        cam = gBtlCam + v1 * 768;
        if (cam[0x2C0] == 0) {
            func_002113C0(a0, 9, 0x2000, 0);
        } else {
            f1 = F(a0, 0x158);
            if (0.0f < f1) {
                f0 = D_00385828;
                if (f21 < f0) f21 = f0;
            } else {
                f0 = D_0038582C;
                if (f0 < f21) f21 = f0;
            }
            f20 = BtlOpp_GetDistance(a0);
            cam = gBtlCam + W(a0, 0x1538) * 768;
            if (D_00385830 < F(cam, 0x2C4) || 40.0f < f20)
                func_002113C0(a0, 9, 0x2000, 0);
            if (!func_00211310(a0, 9, 0x2000)) {
                f2 = F(a0, 0x158);
                f0 = __builtin_fabsf(f2 + f21);
                if (f22 < f0) {
                    cam = gBtlCam + W(a0, 0x1538) * 768;
                    if (F(cam, 0x2C4) < D_00385834 && f20 < 40.0f) {
                        if (0.0f < f2) F(a0, 0x158) = f24;
                        else F(a0, 0x158) = f22;
                        f21 = 0.0f;
                        func_002113C0(a0, 9, 0x2000, 1);
                    }
                }
            }
        }
        if (s1) func_002113C0(a0, 9, 0x2000, 1);
        if (func_00211310(a0, 9, 0xE00)) {
            f0 = F(a0, 0x158);
            f23 = D_00385838;
            f20 = (f22 - __builtin_fabsf(f0)) * 0.5f;
            if (func_00211310(a0, 14, 0x40)) {
                f20 = f22 + f22;
                f23 = f20;
            }
            if (func_00211310(a0, 9, 0x200)) {
                if (F(a0, 0x158) < 0.0f) f20 = -f20;
            }
            if (func_00211310(a0, 9, 0x400)) f20 = -f20;
            if (f23 < f20) f20 = f23;
            if (f20 < -f23) f20 = -f23;
            if (0.0f < f20) {
                if (f21 < f20) f21 = f20;
            } else {
                if (f20 < f21) f21 = f20;
            }
        }
        f0 = F(a0, 0x158) + f21;
        F(a0, 0x158) = f0;
        if (f0 < f24) F(a0, 0x158) = f24;
        f0 = F(a0, 0x158);
        if (f22 < f0) F(a0, 0x158) = f22;
        F(a0, 0x15C) = f22;
        W(a0, 0x160) = 0;
        W(a0, 0x164) = 0;
        W(a0, 0x168) = 0;
    } else {
        f21 = 0.0f;
        f20 = f21;
        if (!func_00211310(a0, 9, 0x80000)) {
            f2 = F(a0, 0x154);
        } else {
            if (BtlPad_Test48(a0, 0x16) || BtlPad_Test48(a0, 0x17)) {
                f0 = func_00207E70(a0) * D_0038583C;
                f20 = f0 + f0;
            } else if (BtlPad_Test48(a0, 8)) {
                f20 = func_00207E80(a0) * D_00385840;
            }
            if (BtlPad_Test48(a0, 0x14) || BtlPad_Test48(a0, 0x15)) {
                f21 = func_00207E78(a0) * D_00385844;
            }
            f2 = F(a0, 0x154);
        }
        if (__builtin_fabsf(f2) < __builtin_fabsf(f20)) f0 = (f20 - f2) * D_00385848;
        else f0 = (f20 - f2) * 0.5f;
        F(a0, 0x154) = f2 + f0;
        f2 = BtlUtil_WrapAngle(F(a0, 0x150) + F(a0, 0x154));
        f1 = F(a0, 0x168);
        f3 = D_0038584C;
        F(a0, 0x150) = f2;
        if (f3 < f1) {
            f0 = f1 - f3;
            f1 = f2 + f3;
            F(a0, 0x168) = f0;
            F(a0, 0x150) = f1;
        } else if (f1 < D_00385850) {
            f0 = f1 + f3;
            f1 = f2 - f3;
            F(a0, 0x168) = f0;
            F(a0, 0x150) = f1;
        } else {
            f0 = f2 + f1;
            W(a0, 0x168) = 0;
            F(a0, 0x150) = f0;
        }
        f1 = F(a0, 0x164);
        f3 = D_00385854;
        f0 = (f21 - f1) * f3;
        f2 = F(a0, 0x160);
        f1 = f1 + f0;
        f2 = f2 + f1;
        F(a0, 0x164) = f1;
        F(a0, 0x160) = f2;
        if (f2 < -0.5f) F(a0, 0x160) = -0.5f;
        f0 = F(a0, 0x160);
        if (0.0f < f0) F(a0, 0x160) = 0.0f;
    }
tail:
    if (BtlPad_Test4C(a0, 0x20)) {
        v = W(a0, 0x204) + 1;
        W(a0, 0x204) = v;
        W(a0, 0x204) = v % 3;
    }
}
