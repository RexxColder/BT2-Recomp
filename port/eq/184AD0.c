#include "common.h"

f32 Rand_FloatRange(f32 farg0, f32 farg1, s64 a0, s64 a1, s64 a2, s64 a3, s64 t0, s64 t1, s64 t2, s64 t3,
                    s64 k0, s64 k1, s64 k2, s64 k3, s64 k4, s64 k5, s64 k6, s64 k7);
f32 sinf(f32 x);
f32 cosf(f32 x);
void Mtx_RotateX(f32 farg0, s32 arg0, s32 arg1);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Normalize(s32 arg0, s32 arg1);
f32 EftMath_WrapAngle(f32 farg0);
extern f32 D_00384BA0;

void func_00184AD0(void *arg0, void *arg1, void *arg2, s32 p3, s32 p4, s32 p5, s32 p6, s64 p7,
                   f32 f0, f32 f1, f32 f2) {
    s32 sp[16];
    u8 *s0;
    u8 *in;
    u8 *s1;
    f32 fr;
    f32 f20;
    f32 sv;
    f32 cv;

    s0 = (u8 *)arg0;
    in = (u8 *)arg1;
    s1 = (u8 *)arg2;

    /* ints: a0..a3 = in+0x28, in, in+0x30, in+0x10; t0..t2 = in+0, in+8, in+0x38; t3 = p7 (pass-through);
       9th..16th on the stack = in+0, +8, +0x10, +0x18, +0x20, +0x28, +0x30, +0x38 */
    fr = Rand_FloatRange(*(f32 *)(s1 + 0x3C), *(f32 *)(s1 + 0x3C) + *(f32 *)(s1 + 0x40),
                         *(s64 *)(in + 0x28), (s64)(s32)arg1, *(s64 *)(in + 0x30), *(s64 *)(in + 0x10),
                         *(s64 *)(in + 0x00), *(s64 *)(in + 0x08), *(s64 *)(in + 0x38), p7,
                         *(s64 *)(in + 0x00), *(s64 *)(in + 0x08), *(s64 *)(in + 0x10), *(s64 *)(in + 0x18),
                         *(s64 *)(in + 0x20), *(s64 *)(in + 0x28), *(s64 *)(in + 0x30), *(s64 *)(in + 0x38));
    f20 = *(f32 *)(s1 + 0x44) + fr;

    sv = sinf(f1);
    *(s32 *)(s0 + 4) = 0;
    *(f32 *)(s0 + 0) = sv * f20;
    cv = cosf(f1);
    *(f32 *)(s0 + 8) = cv * f20;
    Mtx_RotateX(f0, (s32)sp, (s32)sp);
    func_00129C50((s32)s0, (s32)sp, (s32)s0);
    Vec3_Normalize((s32)(s0 + 0x10), (s32)s0);
    *(f32 *)(s0 + 0xAC) = EftMath_WrapAngle(f2 * D_00384BA0);
}
