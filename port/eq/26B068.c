#include "common.h"

extern s32 func_00269A40();
extern f32 func_0029DFD0();
extern void func_00312680(s32 dst, s32 src, f32 scale);
extern void func_003126C8();
extern void func_00312638();
extern void func_00312650();
extern void func_00260CB8();
extern f32 func_0026B030(f32 a);
extern f32 func_0026A3E0();
extern void func_0029A278();
extern f32 sinf();
extern f32 cosf();
extern void sceVu0ApplyMatrix();
extern void sceVu0InterVector(s32 dst, s32 a, s32 b, f32 t);
extern void sceVu0InversMatrix();
extern void sceVu0Normalize();
extern f32 sceVu0InnerProduct();
extern s32 sceVu0MulMatrix();
extern void Vec3_RotateAxis(s32 out, s32 v, s32 axis, f32 angle);
extern void Vec3_RotateY(s32 out, s32 v, f32 angle);
extern void Quat_FromVectors(s32 out, s32 a, s32 b, f32 t);
extern void Quat_Slerp(s32 out, s32 a, s32 b, f32 t);
extern void Quat_LimitAngle(s32 out, s32 q, f32 limit);
extern f32 Quat_GetAngle();
extern void Quat_FromAxisAngle(s32 out, f32 x, f32 y, f32 z, f32 angle);
extern void Quat_SlerpIdentity(s32 out, s32 q, f32 t);
extern void Quat_ToMtx();

extern f32 D_00386F78;
extern f32 D_00386F7C;
extern f32 D_00386F80;
extern f32 D_00386F84;
extern f32 D_00386F88;
extern f32 D_00386F8C;
extern f32 D_00386F90;
extern f32 D_00386F94;
extern f32 D_00386F98;
extern f32 D_00386F9C;
extern f32 D_00386FA0;
extern f32 D_00386FA4;
extern f32 D_00386FA8;
extern f32 D_00386FAC;
extern f32 D_00386FB0;
extern f32 D_00386FB4;
extern f32 D_00386FB8;
extern f32 D_00386FBC;
extern u8 *gBtlStage;
extern u8 D_002C3630[] __attribute__((section(".data")));
extern u8 D_00344A00[] __attribute__((section(".data")));

#define SP(o) ((s32)(sp + (o)))
#define SF(o) (*(f32 *)(sp + (o)))

s32 func_0026B068(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 sp[0x210];
    f32 f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30, f31;
    f32 f0, f1, f2, f12;
    s32 fp, s7;
    u8 *T, *P, *node, *s0, *s2, *s3, *s6;
    s32 i;
    s32 flag;

    f24 = 1.0f;
    f27 = 1.0f;
    f28 = 30.0f;
    flag = (*(s32 *)(arg0 + 0xAF0) & 0x1000000) != 0;
    i = *(s8 *)(arg1 + 0x20);
    s7 = *(s8 *)(arg1 + 0x21);
    if (flag) {
        f28 = 60.0f;
        f27 = 2.0f;
        f24 = 0.5f;
    }
    *(s32 *)(sp + 0x130) = arg2;
    *(s32 *)(sp + 0x134) = arg3;
    T = *(u8 **)(arg0 + 0x95C);
    P = T + 0xC + 4 * i;
    SF(0x70) = *(f32 *)P;
    SF(0x74) = -*(f32 *)(P + 0x30);
    SF(0x78) = -*(f32 *)(P + 0x60);
    *(s32 *)(sp + 0x7C) = 0;
    SF(0x13C) = *(f32 *)(P + 0x180);
    SF(0x140) = *(f32 *)(T + 8 + 4 * i + 0x1C0);
    SF(0x144) = *(f32 *)(T + 8 + 4 * i + 0x1F0);
    SF(0x150) = *(f32 *)(P + 0xC0);
    f31 = *(f32 *)(P + 0xF0);
    f29 = *(f32 *)(P + 0x150);
    fp = *(u8 *)(T + i + 0xC + 0x90);
    f26 = (f32)(s32) * (u8 *)(T + i + 8 + 0x220) * D_00386F7C;
    SF(0x148) = ((f32)(s32) * (u8 *)(T + i + 0xC + 0x1B0) / 180.0f) * D_00386F78;
    SF(0x14C) = ((f32)(s32) * (s16 *)(T + 8 + 2 * i + 0xA0) / 180.0f) * D_00386F78;
    f30 = ((f32)(s32) * (u8 *)(T + i + 0xC0) / 180.0f) * D_00386F78;
    f25 = ((f32)(s32) * (u8 *)(T + i + 0x150) / 180.0f) * D_00386F78;
    f21 = ((f32)(s32) * (s8 *)(T + i + 0xC + 0x120) / 180.0f) * D_00386F78;
    f22 = ((f32)(s32) * (s16 *)(T + 8 + 2 * i + 0x130) / 180.0f) * D_00386F78;
    f23 = D_00386F80;

    f1 = func_0029DFD0(SP(0x70));
    if (D_00386F84 < f1) {
        func_00312680(SP(0x70), SP(0x70), 1.0f / f1);
    }
    func_003126C8(SP(0x40), arg1);
    node = (u8 *)func_00269A40(arg0, s7);
    *(u8 **)(sp + 0x138) = node;
    if (node == 0) {
        return 0;
    }
    s0 = D_002C3630;
    func_003126C8(SP(0x0), s0);
    func_003126C8(SP(0x10), s0);
    func_003126C8(SP(0x20), s0);
    f20 = f27 * f23;
    s2 = sp + 0x30;
    if (*(s32 *)(arg1 + 0x24) == 0) {
        func_00260CB8(arg0, s2, s7);
        *(s32 *)(sp + 0x3C) = 0;
        sceVu0ApplyMatrix(s2, arg0 + 0xA00, s2);
        func_00312680(s2, s2, f20);
        func_00312638(SP(0x10), SP(0x10), s2);
    }
    func_00312680(s2, arg0 + 0x14F0, f20);
    func_00312638(SP(0x10), SP(0x10), s2);
    f0 = func_0029DFD0(SP(0x10));
    f1 = D_00386F88 / f28;
    if (f1 < f0) {
        func_003126C8(SP(0x10), s0);
    }
    func_00312650(SP(0x0), SP(0x0), SP(0x10));
    if (gBtlStage != 0) {
        s0 = *(u8 **)(gBtlStage + 4);
        f0 = func_0029DFD0(s0 + 0x20);
        SF(0x20) = ((*(f32 *)(s0 + 0x20) / f0) * *(f32 *)(s0 + 0x2C)) * f23;
        SF(0x24) = ((*(f32 *)(s0 + 0x24) / f0) * *(f32 *)(s0 + 0x2C)) * f23;
        *(s32 *)(sp + 0x2C) = 0;
        SF(0x28) = ((*(f32 *)(s0 + 0x28) / f0) * *(f32 *)(s0 + 0x2C)) * f23;
    } else if (*(s32 *)(arg0 + 0xAF0) & 0x1000000) {
        func_003126C8(SP(0x20), D_00344A00);
    }
    s0 = *(u8 **)(arg1 + 0x24);
    if (s0 == 0) {
        f12 = D_00386F8C;
        f0 = *(f32 *)(arg1 + 0x28);
        f12 = (f21 + f12) * f24;
        *(f32 *)(arg1 + 0x28) = func_0026B030(f0 + f12);
        f12 = D_00386F90;
        f1 = *(f32 *)(arg1 + 0x2C);
        f12 = (f21 + f12) * f24;
        *(f32 *)(arg1 + 0x2C) = func_0026B030(f1 + f12);
        f12 = D_00386F94;
        f1 = *(f32 *)(arg1 + 0x30);
        f12 = (f21 + f12) * f24;
        f12 = f1 + f12;
    } else {
        f20 = D_00386F98;
        *(f32 *)(arg1 + 0x28) = func_0026B030(*(f32 *)(s0 + 0x28) - f20);
        *(f32 *)(arg1 + 0x2C) = func_0026B030(*(f32 *)(s0 + 0x2C) - f20);
        f12 = *(f32 *)(s0 + 0x30) - f20;
    }
    s0 = arg0 + 0x1500;
    *(f32 *)(arg1 + 0x30) = func_0026B030(f12);
    f20 = 0.0f;
    f21 = 0.125f;
    f0 = sinf(*(f32 *)(arg1 + 0x28) + f22);
    f0 = f0 * 0.25f + 0.25f;
    f20 = f0 + f20;
    f0 = sinf(*(f32 *)(arg1 + 0x2C) + f22);
    f0 = f0 * f21 + f21;
    f20 = f20 + f0;
    f0 = sinf(*(f32 *)(arg1 + 0x30) + f22);
    f0 = f0 * f21 + f21;
    func_00312680(SP(0x20), SP(0x20), f20 + f0);
    func_00312680(s2, SP(0x10), 0.5f * f27);
    func_00312650(SP(0x20), SP(0x20), s2);
    func_00312638(SP(0x20), SP(0x20), s0);
    SF(0x80) = 1.0f;
    *(s32 *)(sp + 0x84) = 0;
    *(s32 *)(sp + 0x88) = 0;
    node = (u8 *)func_00269A40(arg0, 3);
    *(s32 *)(sp + 0x8C) = 0;
    if (node != 0) {
        func_003126C8(SP(0x80), node);
    }
    f0 = func_0029DFD0(arg0 + 0x14F0);
    f22 = f0 * f27;
    f0 = func_0029DFD0(s0);
    f0 = f0 * 3.0f;
    s0 = *(u8 **)(arg1 + 0x24);
    f22 = f22 + f0;
    if (s0 == 0) {
        f21 = D_00386F9C;
        f0 = func_0026A3E0(arg0);
        f1 = D_00386FA0;
        f0 = f0 * f21;
        f20 = D_00386FA4;
        f12 = *(f32 *)(arg1 + 0x34);
        f20 = f22 * f20;
        f0 = f0 + f1;
        f0 = f20 * f0;
        f0 = f0 * f24;
        f0 = func_0026B030(f12 + f0);
        *(f32 *)(arg1 + 0x34) = f0;
        f0 = func_0026A3E0(arg0);
        f1 = D_00386FA8;
        f0 = f0 * f21;
        f12 = *(f32 *)(arg1 + 0x38);
        f0 = f0 + f1;
        f0 = f20 * f0;
        f0 = f0 * f24;
        f0 = func_0026B030(f12 + f0);
        *(f32 *)(arg1 + 0x38) = f0;
        f0 = func_0026A3E0(arg0);
        f1 = D_00386FAC;
        f0 = f0 * f21;
        f12 = *(f32 *)(arg1 + 0x3C);
        f0 = f0 + f1;
        f20 = f20 * f0;
        f20 = f20 * f24;
        f12 = f12 + f20;
    } else {
        f20 = D_00386FB0;
        *(f32 *)(arg1 + 0x34) = func_0026B030(*(f32 *)(s0 + 0x34) - f20);
        *(f32 *)(arg1 + 0x38) = func_0026B030(*(f32 *)(s0 + 0x38) - f20);
        f12 = *(f32 *)(s0 + 0x3C) - f20;
    }
    *(f32 *)(arg1 + 0x3C) = func_0026B030(f12);
    f23 = 0.5f;
    f20 = -f25;
    f0 = sinf(*(f32 *)(arg1 + 0x34));
    f0 = f0 * f23;
    f21 = f0 + 0.0f;
    f0 = sinf(*(f32 *)(arg1 + 0x38));
    f0 = f0 * f23;
    f1 = D_00386FB4;
    f21 = f21 + f0;
    f22 = (f22 * f29) * f1;
    f12 = f21 * f22;
    if (f12 < f20) f12 = f20;
    if (f25 < f12) f12 = f25;
    Vec3_RotateAxis(SP(0x20), SP(0x20), SP(0x80), f12);
    f0 = sinf(*(f32 *)(arg1 + 0x3C));
    f21 = f0 + 0.0f;
    f12 = f21 * f22;
    if (f12 < f20) f12 = f20;
    if (f25 < f12) f12 = f25;
    Vec3_RotateY(SP(0x20), SP(0x20), f12);
    func_00312638(SP(0x0), SP(0x0), SP(0x20));
    s0 = arg1 + 0x10;
    sceVu0InterVector(s0, SP(0x10), s0, f31);
    func_00312680(s2, s0, SF(0x150));
    func_00312638(SP(0x0), SP(0x0), s2);
    SF(0x4) = SF(0x4) + SF(0x144);
    sceVu0InversMatrix(SP(0x90), *(s32 *)(sp + 0x130));
    *(s32 *)(sp + 0xC) = 0;
    sceVu0ApplyMatrix(SP(0x0), SP(0x90), SP(0x0));
    func_00312680(s2, SP(0x70), SF(0x140));
    func_00312638(SP(0x0), SP(0x0), s2);
    sceVu0Normalize(s2, SP(0x0));
    Quat_FromVectors(SP(0x50), SP(0x70), s2, SF(0x13C));
    if (0.0f < f26) {
        f0 = func_0029DFD0(SP(0x0));
        f2 = D_00386FB8;
        f1 = 1.0f;
        f0 = f0 * f2;
        f1 = f1 - f26;
        f0 = f0 * f26;
        f1 = f1 * f23;
        f12 = f1 + f0;
        if (f12 < f2) f12 = f2;
        if (f23 < f12) f12 = f23;
        Quat_Slerp(SP(0x60), SP(0x40), SP(0x50), f12);
    } else {
        Quat_Slerp(SP(0x60), SP(0x40), SP(0x50), f23);
    }
    Quat_LimitAngle(SP(0x60), SP(0x60), SF(0x148));
    if (0.0f < f30) {
        if (fp == 1) {
            SF(0x80) = -SF(0x78);
            SF(0x88) = SF(0x70);
            SF(0x84) = 0.0f;
            SF(0x8C) = 0.0f;
        } else if (fp == 2) {
            SF(0x84) = -SF(0x70);
            SF(0x80) = SF(0x74);
            SF(0x88) = 0.0f;
            SF(0x8C) = 0.0f;
        } else if (fp == 0) {
            SF(0x88) = -SF(0x74);
            SF(0x84) = SF(0x78);
            SF(0x80) = 0.0f;
            SF(0x8C) = 0.0f;
        }
        Quat_FromVectors(SP(0xD0), SP(0x80), SP(0x60), 1.0f);
        f20 = Quat_GetAngle(SP(0xD0));
        f0 = sceVu0InnerProduct(SP(0x70), SP(0xD0));
        if (f0 < 0.0f) f20 = -f20;
        f20 = func_0026B030(f20 + SF(0x14C));
        f0 = D_00386FBC - f30;
        if (f0 < __builtin_fabsf(f20)) {
            if (!(0.0f < f20)) f0 = -f0;
            f20 = f0 - f20;
            f21 = cosf(f20);
            if (0.0f < f21) {
                Quat_FromAxisAngle(SP(0xE0), SF(0x70), SF(0x74), SF(0x78), f20);
                func_0029A278(SP(0x60), SP(0x60), SP(0xE0));
                Quat_SlerpIdentity(SP(0x60), SP(0x60), f21);
            } else {
                func_003126C8(SP(0x60), D_002C3630);
            }
        }
    }
    node = *(u8 **)(sp + 0x138);
    func_003126C8(node + 0x90, SP(0x60));
    func_003126C8(arg1, SP(0x60));
    node = *(u8 **)(sp + 0x138);
    *(s32 *)(node + 0xD0) = *(s32 *)(node + 0xD0) & ~1;
    Quat_ToMtx(SP(0xF0), SP(0x60));
    return sceVu0MulMatrix(*(s32 *)(sp + 0x134), *(s32 *)(sp + 0x130), SP(0xF0));
}
