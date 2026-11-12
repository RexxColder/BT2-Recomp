#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
void Mtx_RotateX(s32 arg0, s32 arg1, f32 farg0);
f32 Rand_FloatRange(f32 farg0, f32 farg1);
s32 Vec3_Normalize(s32 arg0, s32 arg1);
f32 cosf(f32 farg0);
void func_00129C50(s32 arg0, s32 arg1, s32 arg2);
f32 sinf(f32 farg0);
extern f32 D_00384BD8;

void func_00188C48(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2) {
    s32 sp[16];
    f32 f20;

    (void)arg2;
    f20 = *(f32 *)(arg1 + 0x44) + Rand_FloatRange(*(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x3C) + *(f32 *)(arg1 + 0x40));
    *(s32 *)(arg0 + 0x4) = 0;
    *(f32 *)(arg0 + 0x0) = sinf(farg1) * f20;
    *(f32 *)(arg0 + 0xC) = 1.0f;
    *(f32 *)(arg0 + 0x8) = cosf(farg1) * f20;
    Mtx_RotateX((s32)sp, (s32)sp, farg0);
    func_00129C50(arg0, (s32)sp, arg0);
    Vec3_Normalize(arg0 + 0x10, arg0);
    *(f32 *)(arg0 + 0xAC) = EftMath_WrapAngle(farg2 * D_00384BD8);
}
