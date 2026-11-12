#include "common.h"

extern f32 D_003858A4;
extern f32 D_003858A8;

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FD1F0(s32 arg0);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
u8 *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00211288(s32 arg0);
s32 func_00241F80(s32 arg0, s32 arg1);
s32 func_00241E30(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00203310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00241F00(s32 arg0, s32 arg1);
s32 BtlChar_FrameMod(s32 arg0);
void func_00210000(s32 arg0, s32 arg1);
f32 func_00241F50(s32 arg0, s32 arg1);
void Vec3_DiffToEuler_20E478(f32 farg0, s32 arg0, s32 arg1);
void func_001FBE80(f32 farg0, s32 arg0, f32 farg1);
void BtlChar_Vibrate(f32 farg0, s32 arg0, f32 farg1);

s32 func_00200890(u8 *arg0, u8 *arg1) {
    u8 sp[0x10];
    f32 f20;
    f32 wrap;
    f32 d8;
    s32 s1;
    s32 s0;
    s32 s4;
    s32 s5;
    s32 temp_v0;
    s32 v1;

    if (func_00211310((s32)arg0, 3, 8) != 0) {
        return 0;
    }
    if (*(s32 *)(arg1 + 0x64) == 0) {
        return 0;
    }
    s1 = func_001FD1F0((s32)arg0);
    f20 = func_00200550((s32)arg0, (s32)arg1, (s32)sp);
    if (s1 != 9) {
        wrap = BtlUtil_WrapAngle(*(f32 *)(BtlChar_GetPos((s32)arg0) + 0x14) - f20);
        if (wrap < 0.0f) {
            wrap = -wrap;
        }
        if (wrap < D_003858A4) {
            return 0;
        }
    }
    temp_v0 = *(s32 *)(arg1 + 0x64);
    s5 = *(s32 *)(temp_v0 + 4);
    s4 = func_00211288(*(s32 *)temp_v0);
    if (func_00241F80(s4, s5) & 0x200000) {
        return 0;
    }
    s0 = func_00241E30(s4, s5);
    if (s1 == 7) {
        return 0;
    }
    if (s1 < 8) {
        if (s1 == 0) {
            return 0;
        }
    } else if (s1 == 8) {
        s0 = s0 / 2;
    }
    func_002113C0((s32)arg0, 4, 0x200, 1);
    func_00203310((s32)arg0, s0, 0xC);
    v1 = func_00241F00(s4, s5);
    if (v1 == 1) {
        s32 r = BtlChar_FrameMod(2);
        func_00210000((s32)(arg1 + 0x20), (r == 0) ? 0x11 : 0x1B);
    } else if (v1 == 2) {
        func_00210000((s32)(arg1 + 0x20), 0x47);
    } else if (v1 == 3) {
        func_00210000((s32)(arg1 + 0x20), 0x4A);
    }
    wrap = func_00241F50(s4, s5);
    d8 = D_003858A8;
    Vec3_DiffToEuler_20E478(wrap, (s32)arg0, (s32)sp);
    func_001FBE80(3.0f, (s32)arg0, d8);
    BtlChar_Vibrate(1.0f, (s32)arg0, d8);
    return 1;
}
