#include "common.h"

extern u8 *gBtlStage;
extern u8 D_002C3630[];
extern u8 D_00344A00[];
extern f32 D_00386F04, D_00386F08, D_00386F0C, D_00386F10, D_00386F14, D_00386F18, D_00386F1C, D_00386F20;
extern f32 D_00386F24, D_00386F28, D_00386F2C, D_00386F30, D_00386F34, D_00386F38, D_00386F3C, D_00386F40;
extern f32 D_00386F44, D_00386F48, D_00386F4C, D_00386F50, D_00386F54, D_00386F58, D_00386F5C, D_00386F60;
extern f32 D_00386F64;

extern f32 cosf(f32 x);
extern f32 sinf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern s32 func_003126C8();
extern s32 func_00312638();
extern s32 func_00312650();
extern s32 func_00312680(u8 *a, u8 *b, f32 f);
extern u8 *func_00269A40(u8 *a, s32 b);
extern s32 func_00260CB8();
extern s32 sceVu0ApplyMatrix();
extern f32 func_0029DFD0(u8 *a);
extern f32 func_0026A3E0(u8 *a);
extern f32 func_0026A440(f32 x);
extern s32 Vec3_RotateAxis(u8 *a, u8 *b, u8 *c, f32 f);
extern void Vec3_RotateX(u8 *a, u8 *b, f32 f);
extern void Vec3_RotateY(u8 *a, u8 *b, f32 f);
extern s32 sceVu0InversMatrix();
extern s32 func_0029A278();
extern s32 sceVu0Normalize();
extern void Quat_FromVectors(u8 *a, u8 *b, u8 *c, f32 f);
extern s32 Quat_FromMtx();
extern s32 Quat_Inverse();
extern s32 Quat_Mul();
extern s32 Quat_ToMtx();
extern s32 sceVu0MulMatrix();

#define FP(p, o) (*(f32 *)((p) + (o)))

s32 func_0026A478(u8 *a0, u8 *a1, u8 *a2, u8 *a3)
{
    u8 sp[0x220];
    f32 f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31;
    f32 t0, t1, t2;
    s32 s6, s0;
    u8 *base, *p2, *p3, *s1p, *s2, *s3, *s7, *s6p, *fp, *v, *st, *tp;
    f32 *vf;

    *(u8 **)(sp + 0x160) = a2;
    *(u8 **)(sp + 0x164) = a3;
    f23 = 1.0f;
    f24 = f23;
    f25 = 30.0f;
    if (*(s32 *)(a0 + 0xAF0) & 0x1000000) {
        f25 = 60.0f;
        f24 = 2.0f;
        f23 = 0.5f;
    }
    s6 = *(s8 *)(a1 + 0x21);
    s0 = *(s8 *)(a1 + 0x20);
    base = *(u8 **)(a0 + 0x95C);
    s3 = base + 0xC;
    s2 = base + 0x4;
    s1p = s3 + (s0 + 0x230);
    f21 = D_00386F04;
    f30 = D_00386F08;
    f31 = D_00386F0C;
    f22 = D_00386F10;
    *(s32 *)(sp + 0x70) = 0;
    *(f32 *)(sp + 0x74) = cosf((f32)*(s8 *)s1p / 180.0f * f21);
    *(f32 *)(sp + 0x78) = sinf((f32)*(s8 *)s1p / 180.0f * f21);
    *(s32 *)(sp + 0x7C) = 0;
    {
        u8 *a2p = s2 + s0 * 4;
        u8 *q0 = s2 + (s0 + 0x280);
        u8 *q3 = s3 + (s0 + 0x280);
        f32 g1 = (f32)*(s8 *)q0;
        f32 g0 = (f32)*(s8 *)q3;
        f29 = FP(a2p, 0x240);
        f28 = FP(a2p, 0x260);
        f26 = g1 / 180.0f * f21;
        f27 = g0 / 180.0f * f21;
    }
    func_003126C8(sp + 0x50, a1);
    fp = func_00269A40(a0, s6);
    if (fp == 0) {
        return 0x340000;
    }
    func_003126C8(sp, D_002C3630);
    s2 = sp + 0x20;
    func_003126C8(s2, D_002C3630);
    s3 = sp + 0x30;
    func_003126C8(s3, D_002C3630);
    f20 = f24 * f22;
    s7 = sp + 0x40;
    if (*(u8 **)(a1 + 0x24) == 0) {
        func_00260CB8(a0, s7, s6);
        *(s32 *)(sp + 0x4C) = 0;
        sceVu0ApplyMatrix(s7, a0 + 0xA00, s7);
        func_00312680(s7, s7, f20);
        func_00312638(s2, s2, s7);
    }
    s6p = a0 + 0x14F0;
    func_00312680(s7, s6p, f20);
    func_00312638(s2, s2, s7);
    {
        f32 d = func_0029DFD0(s2);
        if (D_00386F14 / f25 < d) {
            func_003126C8(s2, D_002C3630);
        }
    }
    func_00312650(sp, sp, s2);
    st = gBtlStage;
    if (st != 0) {
        u8 *s1 = *(u8 **)(st + 4);
        u8 *s0p = s1 + 0x20;
        f32 d = func_0029DFD0(s0p);
        f32 f3 = D_00386F18;
        FP(sp, 0x30) = FP(s0p, 0) / d * FP(s1, 0x2C) * f3;
        FP(sp, 0x34) = FP(s1, 0x24) / d * FP(s1, 0x2C) * f3;
        *(s32 *)(sp + 0x3C) = 0;
        FP(sp, 0x38) = FP(s1, 0x28) / d * FP(s1, 0x2C) * f3;
    } else if (*(s32 *)(a0 + 0xAF0) & 0x1000000) {
        func_003126C8(s3, D_00344A00);
    }
    v = *(u8 **)(a1 + 0x24);
    if (v == 0) {
        FP(a1, 0x28) = func_0026A440(FP(a1, 0x28) + f23 * D_00386F1C);
        t0 = FP(a1, 0x2C);
        FP(a1, 0x2C) = func_0026A440(t0 + f23 * D_00386F20);
        t0 = FP(a1, 0x30);
        t1 = t0 + f23 * D_00386F24;
    } else {
        f20 = D_00386F28;
        FP(a1, 0x28) = func_0026A440(FP(v, 0x28) - f20);
        FP(a1, 0x2C) = func_0026A440(FP(v, 0x2C) - f20);
        t1 = FP(v, 0x30) - f20;
    }
    {
        u8 *s0p = a0 + 0x1500;
        FP(a1, 0x30) = func_0026A440(t1);
        f21 = 0.0f;
        f21 = sinf(FP(a1, 0x28)) * 0.25f + 0.25f + f21;
        f20 = 0.125f;
        f21 = f21 + (sinf(FP(a1, 0x2C)) * f20 + f20);
        t0 = sinf(FP(a1, 0x30)) * f20 + f20;
        func_00312680(s3, s3, f21 + t0);
        func_00312680(s7, s2, 0.5f * f24);
        func_00312650(s3, s3, s7);
        func_00312638(s3, s3, s0p);
        s1p = sp + 0x80;
        FP(sp, 0x80) = 1.0f;
        *(s32 *)(sp + 0x84) = 0;
        *(s32 *)(sp + 0x88) = 0;
        *(s32 *)(sp + 0x8C) = 0;
        v = func_00269A40(a0, 3);
        if (v) {
            func_003126C8(s1p, v);
        }
        t0 = func_0029DFD0(s6p);
        t0 = t0 + t0;
        f22 = t0 * f24;
        t0 = func_0029DFD0(s0p);
        f22 = f22 + t0 * 4.0f;
    }
    if (*(u8 *)(a1 + 0x23) & 1) {
        f21 = D_00386F2C;
        t0 = func_0026A3E0(a0);
        f20 = f22 * D_00386F34;
        FP(a1, 0x34) = func_0026A440(FP(a1, 0x34) + f20 * (t0 * f21 + D_00386F30) * f23);
        t0 = func_0026A3E0(a0);
        FP(a1, 0x38) = func_0026A440(FP(a1, 0x38) + f20 * (t0 * f21 + D_00386F38) * f23);
        t0 = func_0026A3E0(a0);
        f20 = f20 * (t0 * f21 + D_00386F3C) * f23;
        t1 = FP(a1, 0x3C) + f20;
    } else {
        f21 = D_00386F40;
        t0 = func_0026A3E0(a0);
        f20 = f22 * D_00386F48;
        FP(a1, 0x34) = func_0026A440(FP(a1, 0x34) - f20 * (t0 * f21 + D_00386F44));
        t0 = func_0026A3E0(a0);
        FP(a1, 0x38) = func_0026A440(FP(a1, 0x38) - f20 * (t0 * f21 + D_00386F4C));
        t0 = func_0026A3E0(a0);
        f20 = f20 * (t0 * f21 + D_00386F50);
        t1 = FP(a1, 0x3C) - f20;
    }
    FP(a1, 0x3C) = func_0026A440(t1);
    f23 = 0.5f;
    f21 = sinf(FP(a1, 0x34)) * f23 + 0.0f;
    t0 = sinf(FP(a1, 0x38)) * f23;
    f20 = (f22 * f28) * f23;
    f21 = f21 + t0;
    t1 = f21 * f20;
    if (t1 < -f30) t1 = -f30;
    if (f30 < t1) t1 = D_00386F54;
    Vec3_RotateAxis(s3, s3, s1p, t1);
    f21 = sinf(FP(a1, 0x3C)) + 0.0f;
    t1 = f21 * f20;
    if (t1 < -f31) t1 = -f31;
    if (f31 < t1) t1 = D_00386F58;
    Vec3_RotateY(s3, s3, t1);
    func_00312638(sp, sp, s3);
    f21 = D_00386F5C;
    FP(sp, 4) = FP(sp, 4) + f29;
    sceVu0InversMatrix(sp + 0x90, *(u8 **)(sp + 0x160));
    *(s32 *)(sp + 0xC) = 0;
    sceVu0ApplyMatrix(sp, sp + 0x90, sp);
    f20 = func_0029DFD0(sp) * D_00386F60;
    if (f20 < f21) f20 = f21;
    if (f23 < f20) f20 = f23;
    s6p = sp + 0x70;
    func_0029A278(s1p, s6p, sp + 0x50);
    s3 = a1 + 0x10;
    s2 = sp + 0x10;
    sceVu0Normalize(s2, sp);
    Quat_FromVectors(sp + 0xD0, s1p, s2, f20);
    func_0029A278(s2, s1p, sp + 0xD0);
    Quat_FromMtx(sp + 0xE0, *(u8 **)(sp + 0x160));
    Quat_Inverse(sp + 0xF0, sp + 0xE0);
    Quat_Mul(sp + 0x100, sp + 0xF0, s3);
    func_0029A278(s2, s2, sp + 0x100);
    func_003126C8(s3, sp + 0xE0);
    t0 = atan2f(FP(sp, 0x78), FP(sp, 0x74));
    FP(sp, 0x110) = t0;
    t1 = atan2f(FP(sp, 0x18), FP(sp, 0x14));
    FP(sp, 0x114) = t1;
    f20 = func_0026A440(t1 - FP(sp, 0x110));
    if (f20 < f26) {
        Vec3_RotateX(s2, s2, f26 - f20);
    }
    if (f27 < f20) {
        Vec3_RotateX(s2, s2, f27 - f20);
    }
    f20 = sinf(D_00386F64);
    t0 = sinf(f21);
    t1 = FP(sp, 0x10);
    if (t1 < f20) {
        t1 = f20;
        FP(sp, 0x10) = f20;
    }
    if (t0 < t1) {
        FP(sp, 0x10) = t0;
    }
    sceVu0Normalize(s2, s2);
    sceVu0Normalize(s7, s2);
    Quat_FromVectors(sp + 0x60, s6p, s7, 1.0f);
    func_003126C8(fp + 0x90, sp + 0x60);
    func_003126C8(a1, sp + 0x60);
    *(s32 *)(fp + 0xD0) &= ~1;
    Quat_ToMtx(sp + 0x120, sp + 0x60);
    return sceVu0MulMatrix(*(u8 **)(sp + 0x164), *(u8 **)(sp + 0x160), sp + 0x120);
}
