#include "common.h"
extern f32 sqrtf(f32 x);
extern f32 fabsf(f32 x);
extern s32 func_00211310();
extern s32 func_00211328();
extern s32 func_003126C8();
extern s32 func_00312638();
extern s32 func_001FA858();
extern s32 func_001FAFD8();
extern s32 func_001FADF8();
extern s32 func_0025C2D8();
extern s32 CamShake_Tick();
extern f32 func_00272F60();
extern f32 func_001FA620();
extern f32 func_001FA588();
extern s32 func_00312680(u8 *dst, u8 *src, f32 s);
extern s32 func_001FB568();
extern s32 func_0025C458();
extern s32 func_001FB6A0();
extern f32 BtlUtil_WrapAngle(f32 a);
extern s32 func_00211220();

s32 func_001FBF58(u8 *c) {
    u8 sp[0xD0];
    u8 *s2 = c + 0x150;
    u8 *s0, *s1, *s6, *s7;
    s32 s4, s5 = 0, fp = 0, ret;
    f32 f20, f0, f2, ff;

    if (func_00211310(c, 14, 0x20)) {
        s7 = sp + 0x10;
        s6 = sp + 0x20;
        func_003126C8(sp, c + 0x180);
        func_003126C8(s7, c + 0x1A0);
        func_003126C8(s6, c + 0x1B0);
        s0 = s2 + 0x80;
    } else {
        s7 = sp + 0x10;
        s6 = sp + 0x20;
        if (*(s32 *)(s2 + 0x148) > 0 || (*(s32 *)(s2 + 0x150) & 0x80)) {
            func_001FA858(c, sp, s7, s6);
        } else if (func_00211310(c, 0, 1)) {
            func_001FAFD8(c, sp, s7, s6);
            s5 = 1;
            fp = 1;
        } else {
            func_001FADF8(c, sp, s7, s6);
            s5 = 1;
        }
        s0 = s2 + 0x80;
    }
    func_0025C2D8(s0, sp + 0x30, sp + 0x40);
    *(f32 *)(sp + 0x0) = *(f32 *)(sp + 0x0) + *(f32 *)(sp + 0x30);
    *(f32 *)(sp + 0x4) = *(f32 *)(sp + 0x4) + *(f32 *)(sp + 0x34);
    *(f32 *)(sp + 0x8) = *(f32 *)(sp + 0x8) + *(f32 *)(sp + 0x38);
    CamShake_Tick(s0);
    f20 = func_00272F60();
    f0 = sqrtf(fabsf(*(f32 *)(sp + 0x0) * *(f32 *)(sp + 0x0) + *(f32 *)(sp + 0x8) * *(f32 *)(sp + 0x8)));
    if (f20 < f0) {
        f2 = f20 / f0;
        *(f32 *)(sp + 0x8) = *(f32 *)(sp + 0x8) * f2;
        *(f32 *)(sp + 0x0) = *(f32 *)(sp + 0x0) * f2;
    }
    f0 = sqrtf(fabsf(*(f32 *)(sp + 0x20) * *(f32 *)(sp + 0x20) + *(f32 *)(sp + 0x28) * *(f32 *)(sp + 0x28)));
    if (f20 < f0) {
        f2 = f20 / f0;
        *(f32 *)(sp + 0x28) = *(f32 *)(sp + 0x28) * f2;
        *(f32 *)(sp + 0x20) = *(f32 *)(sp + 0x20) * f2;
    }
    s4 = (func_00211310(c, 14, 0x40) == 0);
    if (func_00211328(c, 14, 0x80)) s4 = 0;
    f20 = func_001FA620(c, sp, s6);
    if (s4) {
        s1 = s2 + 0x30;
        *(f32 *)(sp + 0x50) = *(f32 *)(sp + 0x0) - *(f32 *)(s2 + 0x30);
        *(f32 *)(sp + 0x54) = *(f32 *)(sp + 0x4) - *(f32 *)(s2 + 0x34);
        *(f32 *)(sp + 0x58) = *(f32 *)(sp + 0x8) - *(f32 *)(s2 + 0x38);
        func_00312680(sp + 0x50, sp + 0x50, f20);
        func_00312638(s1, s1, sp + 0x50);
        s0 = s2 + 0x60;
    } else {
        s1 = s2 + 0x30;
        func_003126C8(s1, sp);
        *(f32 *)(s2 + 0xA0) = func_001FA588(c, sp, s6);
        s0 = s2 + 0x60;
    }
    func_003126C8(s0, s6);
    if (s5) func_001FB568(c, s1, s7);
    ret = func_0025C458(s2 + 0x40, s1, s0, s2 + 0xA4, s2 + 0xAC);
    *(u8 *)(s2 + 0xA8) = (u8)ret;
    if (ret && fp) func_001FB6A0(c, s7);
    if (s4) {
        s1 = s2 + 0x50;
        ff = BtlUtil_WrapAngle(*(f32 *)(sp + 0x10) - *(f32 *)(s2 + 0x50));
        *(f32 *)(sp + 0x60) = ff;
        ff = BtlUtil_WrapAngle(*(f32 *)(sp + 0x14) - *(f32 *)(s2 + 0x54));
        *(f32 *)(sp + 0x64) = ff;
        ff = BtlUtil_WrapAngle(*(f32 *)(sp + 0x18) - *(f32 *)(s2 + 0x58));
        *(f32 *)(sp + 0x68) = ff;
        func_00312680(sp + 0x60, sp + 0x60, f20);
        func_00312638(s1, s1, sp + 0x60);
        ret = func_00211220(s1, s1);
    } else {
        ret = func_003126C8(s2 + 0x50, s7);
    }
    f0 = *(f32 *)(s2 + 0x50) + *(f32 *)(sp + 0x40);
    f2 = *(f32 *)(s2 + 0x54) + *(f32 *)(sp + 0x44);
    ff = *(f32 *)(s2 + 0x58) + *(f32 *)(sp + 0x48);
    *(s32 *)(s2 + 0x5C) = 0;
    *(f32 *)(s2 + 0x6C) = 1.0f;
    *(f32 *)(s2 + 0x50) = f0;
    *(f32 *)(s2 + 0x54) = f2;
    *(f32 *)(s2 + 0x58) = ff;
    *(f32 *)(s2 + 0x3C) = 1.0f;
    *(f32 *)(s2 + 0x4C) = 1.0f;
    return ret;
}
