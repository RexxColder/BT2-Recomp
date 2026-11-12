#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 func_00200550(s32 arg0, s32 arg1, s32 arg2);
s32 BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
s32 func_00211288(s32 arg0);
s32 func_00240FA0(s32 arg0, s32 arg1);
f32 func_00210A98(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA3A8(s32 arg0);
s32 func_00241ED0(s32 arg0, s32 arg1);
s32 func_00241EB0(s32 arg0, s32 arg1);
f32 func_00241F20(s32 arg0, s32 arg1);
void Vec3_DiffToEuler_20E478(f32 farg0, s32 arg1, s32 arg2);
s32 func_00241C98(s32 arg0, s32 arg1);
s32 func_00203C58(s32 arg0, s64 arg1);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00241F00(s32 arg0, s32 arg1);
s32 BtlChar_FrameMod(s32 arg0);
void func_00210000(s32 arg0, s32 arg1);
void func_00212DD8(s32 arg0, s32 arg1);
s32 func_00241DD0(s32 arg0, s32 arg1);
void func_00203310(s32 arg0, s32 arg1, s32 arg2);
void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
void BtlChar_Vibrate(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_003858C0;
extern f32 D_003858C4;
extern f32 D_003858C8;

s32 func_00201250(s32 arg0, s32 arg1) {
    f32 sp[4];
    u8 *s1;
    u8 *s4;
    u8 *p;
    u8 *pos;
    s32 s0;
    s32 s2;
    s32 s3;
    s32 s5;
    s32 v;
    s32 a1r;
    s32 a2;
    f32 f20;
    f32 x;
    f32 ax;

    s1 = (u8 *)arg0;
    s4 = (u8 *)arg1;
    if (func_00211310(arg0, 3, 8) != 0) {
        return 0;
    }
    if (*(s32 *)(s4 + 0x64) == 0) {
        return 0;
    }

    s5 = 1;
    f20 = func_00200550(arg0, arg1, (s32)sp);
    pos = (u8 *)BtlChar_GetPos(arg0);
    x = BtlUtil_WrapAngle(*(f32 *)(pos + 0x14) - f20);
    ax = (x < 0.0f) ? -x : x;
    if (!(ax < D_003858C0)) {
        s5 = 0;
    }

    p = (u8 *)*(s32 *)(s4 + 0x64);
    s2 = *(s32 *)(p + 4);
    s3 = func_00211288(*(s32 *)p);
    if (func_00240FA0(s3, s2) != 4) {
        ax = func_00210A98(s3);
        ax = (ax < 0.0f) ? -ax : ax;
        if (D_003858C4 < ax) {
            return 0;
        }
    }

    v = BtlObjXf_Update(arg0);
    if (func_001FA3A8(v) & 0x100000) {
        s0 = func_00241ED0(s3, s2);
    } else {
        s0 = func_00241EB0(s3, s2);
    }
    if (s0 == 0) {
        s0 = 3;
    }
    if (s0 == 1) {
        return 0;
    }
    if (*(s32 *)(s1 + 0xADC) > 0) {
        s0 = 2;
    }

    if (s0 != 2) {
        *(s32 *)(s1 + 0xB48) = s0;
        *(s32 *)(s1 + 0xB58) = 0;
        *(s32 *)(s1 + 0xB60) = 0;
        *(s32 *)(s1 + 0xB64) = 0;
        *(s32 *)(s1 + 0xB68) = 0;
        *(u8 *)(s1 + 0xB54) = (u8)s5;
        *(f32 *)(s1 + 0xB5C) = f20;
        x = func_00241F20(s3, s2);
        Vec3_DiffToEuler_20E478(x, arg0, (s32)sp);
        if (s0 < 0x1B) {
            if (s0 >= 0x15) {
                *(s32 *)(s1 + 0xB74) = func_00241C98(s3, s2);
                if (func_00203C58(arg0, 0x80000) != 0) {
                    v = *(s32 *)(s1 + 0xB74);
                    v = (v + (s32)(((u32)v) >> 31)) >> 1;
                    *(s32 *)(s1 + 0xB74) = v;
                }
            }
        }
    }

    func_00206958(arg0, 0x800000);
    v = func_00241F00(s3, s2);
    switch (v) {
    case 1:
        v = BtlChar_FrameMod(2);
        func_00210000((s32)(s4 + 0x20), (v == 0) ? 0x11 : 0x1B);
        func_00212DD8(arg0, 0);
        break;
    case 0:
        func_00212DD8(arg0, 0);
        break;
    case 2:
        func_00210000((s32)(s4 + 0x20), 0x47);
        func_00212DD8(arg0, 1);
        break;
    case 3:
        func_00210000((s32)(s4 + 0x20), 0x4A);
        func_00212DD8(arg0, 3);
        break;
    }

    a1r = func_00241DD0(s3, s2);
    a2 = 0;
    if (s2 == 0) {
        a2 = 0x80;
    } else if (s2 == 1) {
        a2 = 0x100;
    }
    f20 = D_003858C8;
    func_00203310(arg0, a1r, a2);
    func_001FBE80(arg0, 3.0f, f20);
    BtlChar_Vibrate(arg0, 1.0f, f20);
    return 1;
}
