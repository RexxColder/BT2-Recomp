#include "common.h"

extern f32 D_00385A7C, D_00385A80, D_00385A84, D_00385A88, D_00385A8C;

s32 func_00211310(u8 *a0, s32 a1, s32 a2);
void func_00215068(u8 *a0, s32 a1, s32 a2, f32 f12, f32 f13);
void BtlOpp_GetDelta(u8 *a0, u8 *a1);
f32 func_0029DFD0(u8 *a0);
f32 func_002086B0(s32 a0);
f32 func_00210D10(u8 *a0);
u8 *BtlChar_GetPos(u8 *a0);
void func_003126C8(u8 *a0, u8 *a1);
void func_002109C8(u8 *a0, u8 *a1);
void func_00312680(u8 *a0, u8 *a1, f32 f12);
f32 sceVu0InnerProduct(u8 *a0, u8 *a1);
f32 atan2f(f32 y, f32 x);
f32 func_00207E80(u8 *a0);
f32 func_00207E88(u8 *a0);
f32 BtlUtil_WrapAngle(f32 f12);
f32 BtlOpp_GetHalfHeightDiff(u8 *a0);
void func_00210970(u8 *a0, u8 *a1);
void sceVu0Normalize(u8 *a0, u8 *a1);
f32 Mathf_Asin(f32 f12);

#define F(p, o) (*(f32 *)((p) + (o)))

/* Step pos[off] toward target by at most maxstep (three-way, as in the asm). */
static void step_to(u8 *a0, s32 off, f32 target, f32 maxstep) {
    f32 d = target - F(BtlChar_GetPos(a0), off);
    f32 f20 = __builtin_fabsf(d);
    if (maxstep < f20) f20 = maxstep;
    if (d < -f20) {
        u8 *p = BtlChar_GetPos(a0);
        F(p, off) = F(p, off) - f20;
    } else if (f20 < d) {
        u8 *p = BtlChar_GetPos(a0);
        F(p, off) = F(p, off) + f20;
    } else {
        u8 *p = BtlChar_GetPos(a0);
        F(p, off) = target;
    }
}

void func_00215550(u8 *a0, s32 a1, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18) {
    u8 sp[0x60];
    u8 *s0, *s1, *s3, *p, *q, *r;
    f32 f20, f21, f22, f23, f0, f1, f2, f3;
    f32 f24 = f12, f26 = f13, f29 = f14, f25 = f15, f28 = f16, f27 = f17, f30 = f18;

    a1 &= 0xFF;
    if (!func_00211310(a0, 0, 1)) {
        func_00215068(a0, 5, 13, f27, f30);
        return;
    }
    BtlOpp_GetDelta(a0, sp);
    f21 = func_0029DFD0(sp);
    f0 = func_002086B0(*(s32 *)(a0 + 0x1534));
    f21 = f21 - f0;
    f0 = func_00210D10(a0);
    f21 = f21 - f0;
    if (f21 < 0.0f) f21 = 0.0f;
    s1 = sp + 0x10;
    p = BtlChar_GetPos(a0);
    func_003126C8(s1, p + 0x50);
    s0 = sp + 0x20;
    func_002109C8(a0, s0);
    f23 = func_0029DFD0(s1);
    f22 = func_0029DFD0(s0);
    f0 = D_00385A7C;
    if (f0 < f23 && f0 < f22) {
        func_00312680(s1, s1, 1.0f / f23);
        func_00312680(s0, s0, 1.0f / f22);
        f0 = sceVu0InnerProduct(s1, s0);
        f24 = f24 - f22 * f0;
        f0 = D_00385A80;
    }
    f22 = D_00385A84;
    if (f0 < f24) f22 = f21 / f24;
    p = BtlChar_GetPos(a0);
    F(p, 0xB4) = atan2f(F(sp, 0), F(sp, 8));
    f0 = func_00207E80(a0);
    f21 = f22 * 0.5f * f26 * f0;
    f2 = -f25;
    if (f21 < f2) f21 = f2;
    if (f25 < f21) f21 = f25;
    step_to(a0, 0xBC, f21, f26);
    s1 = BtlChar_GetPos(a0);
    s0 = BtlChar_GetPos(a0);
    q = BtlChar_GetPos(a0);
    F(s1, 0xB4) = BtlUtil_WrapAngle(F(s0, 0xB4) + F(q, 0xBC));
    s0 = BtlChar_GetPos(a0);
    q = BtlChar_GetPos(a0);
    f2 = BtlUtil_WrapAngle(F(s0, 0xB4) - F(q, 0x14));
    f1 = D_00385A88;
    f20 = __builtin_fabsf(f2) * f30;
    if (f20 < f1) f20 = f1;
    if (f27 < f20) f20 = f27;
    if (f2 < -f20) {
        s1 = BtlChar_GetPos(a0);
        s0 = BtlChar_GetPos(a0);
        F(s0, 0x14) = BtlUtil_WrapAngle(F(BtlChar_GetPos(a0), 0x14) - f20);
    } else if (f20 < f2) {
        s1 = BtlChar_GetPos(a0);
        s0 = BtlChar_GetPos(a0);
        F(s0, 0x14) = BtlUtil_WrapAngle(F(BtlChar_GetPos(a0), 0x14) + f20);
    } else {
        s1 = BtlChar_GetPos(a0);
        s0 = BtlChar_GetPos(a0);
        F(s0, 0x14) = F(BtlChar_GetPos(a0), 0xB4);
    }
    if (a1 == 0) {
        *(s32 *)(BtlChar_GetPos(a0) + 0xB0) = 0;
        return;
    }
    s3 = sp + 0x30;
    f20 = D_00385A8C;
    func_003126C8(s3, sp);
    f0 = BtlOpp_GetHalfHeightDiff(a0);
    F(sp, 0x34) = F(sp, 0x34) + f0;
    f21 = 0.0f;
    s1 = sp + 0x40;
    p = BtlChar_GetPos(a0);
    func_003126C8(s1, p + 0x40);
    s0 = sp + 0x50;
    func_00210970(a0, s0);
    if (f20 < func_0029DFD0(s1)) {
        if (f20 < func_0029DFD0(s0)) {
            sceVu0Normalize(s1, s1);
            sceVu0Normalize(s0, s0);
            f3 = sceVu0InnerProduct(s1, s0);
            f0 = F(sp, 0x54);
            f1 = F(sp, 0x34);
            if (f21 < f3) f0 = f0 * f3;
            else f0 = f0 * f3 * 0.5f;
            F(sp, 0x34) = f1 + f0;
        }
    }
    sceVu0Normalize(s3, s3);
    f1 = -1.0f;
    f0 = F(sp, 0x34);
    if (f0 < f1) {
        f0 = f1;
        F(sp, 0x34) = f1;
    }
    f1 = 1.0f;
    if (f1 < f0) F(sp, 0x34) = f1;
    s0 = BtlChar_GetPos(a0);
    f0 = Mathf_Asin(F(sp, 0x34));
    F(s0, 0xB0) = -f0;
    f0 = func_00207E88(a0);
    f2 = -f28;
    f1 = -(f22 * 0.5f) * f29;
    f21 = f1 * f0;
    if (f21 < f2) f21 = f2;
    if (f28 < f21) f21 = f28;
    step_to(a0, 0xB8, f21, f29);
    s1 = BtlChar_GetPos(a0);
    s0 = BtlChar_GetPos(a0);
    q = BtlChar_GetPos(a0);
    f0 = F(s0, 0xB0);
    F(s1, 0xB0) = BtlUtil_WrapAngle(f0 + F(q, 0xB8));
    f1 = 1.0f;
    if (f22 < f1) {
        r = BtlChar_GetPos(a0);
        F(r, 0xB0) = F(r, 0xB0) * f22;
    }
}
