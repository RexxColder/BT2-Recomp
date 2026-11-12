#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FD1F0(s32 arg0);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 BtlChar_GetPos(s32 arg0);
s32 func_00240040(s32 arg0);
s32 func_002402A8(s32 arg0);
s32 BtlKiBlast_GetHitsOf_240980(s32 arg0);
s32 BtlChar_FrameMod(s32 arg0);
void func_00210000(s32 arg0, s32 arg1);
void func_00203310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_00240CA0(s32 arg0);
void Vec3_DiffToEuler_20E478(f32 farg0, s32 arg0, s32 arg1);
void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_0038589C;
extern f32 D_003858A0;

s32 func_00200680(u8 *arg0, u8 *arg1) {
    u8 sp[0x10];
    f32 f20;
    f32 w;
    s32 s0;
    s32 s1;
    s32 hits;

    if (func_00211310((s32)arg0, 3, 2) != 0) {
        return 0;
    }
    s1 = func_001FD1F0((s32)arg0);
    f20 = func_00200550((s32)arg0, (s32)arg1, (s32)sp);
    if (s1 != 9) {
        w = BtlUtil_WrapAngle(*(f32 *)((u8 *)BtlChar_GetPos((s32)arg0) + 0x14) - f20);
        /* asm 0x200704: c.lt.s |w|, D ; bc1t -> epilogue with v0 = 0 */
        if ((w < 0.0f ? -w : w) < D_0038589C) {
            return 0;
        }
    }
    if ((func_00240040((s32)arg1) & 1) && s1 != 9) {
        return 0;
    }
    s0 = func_002402A8((s32)arg1);
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
    hits = BtlKiBlast_GetHitsOf_240980((s32)arg1);
    if (hits == 0xE) {
        func_00210000((s32)(arg1 + 0x20), 0x42);
    } else if (hits == 0xF) {
        func_00210000((s32)(arg1 + 0x20), (BtlChar_FrameMod(2) == 0) ? 0xD : 0xC);
    } else {
        func_00210000((s32)(arg1 + 0x20), (BtlChar_FrameMod(2) == 0) ? 0x11 : 0x1B);
    }
    f20 = D_003858A0;
    Vec3_DiffToEuler_20E478(func_00240CA0((s32)arg1), (s32)arg0, (s32)sp);
    func_001FBE80((s32)arg0, 3.0f, f20);
    BtlChar_Vibrate((s32)arg0, 1.0f, f20);
    *(s32 *)(arg0 + 0x1474) = *(s32 *)(arg0 + 0x1474) + 1;
    return 1;
}
