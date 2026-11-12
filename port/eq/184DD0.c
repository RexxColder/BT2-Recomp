#include "common.h"

f32 EftMath_WrapAngle(f32 farg0);
f32 Rand_FloatRange(f32 farg0, f32 farg1);
f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
void func_00129B28(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00384BA4;

void func_00184DD0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, f32 farg0, f32 farg1) {
    s64 loc[4];
    f32 f21;
    f32 f20;
    f32 f0;
    f32 c;
    f32 s;

    loc[0] = *(s64 *)(arg2 + 0);
    loc[1] = *(s64 *)(arg2 + 8);
    loc[2] = *(s64 *)(arg3 + 0);
    loc[3] = *(s64 *)(arg3 + 8);

    f21 = Rand_FloatRange(*(f32 *)(arg1 + 0x10), *(f32 *)(arg1 + 0x14)) * D_00384BA4;
    f0 = Rand_FloatRange(*(f32 *)(arg1 + 0x3C), *(f32 *)(arg1 + 0x3C) + *(f32 *)(arg1 + 0x40));
    *(s32 *)(arg0 + 0) = 0;
    f20 = *(f32 *)(arg1 + 0x44) + f0;
    f20 = f20 * farg0;
    *(f32 *)(arg0 + 4) = (f32)(sinf(EftMath_WrapAngle(f21)) * f20);
    c = cosf(EftMath_WrapAngle(f21)) * f20;
    *(f32 *)(arg0 + 0xC) = 1.0f;
    *(f32 *)(arg0 + 8) = c;
    *(s64 *)(arg0 + 0x18) = loc[3];
    *(s64 *)(arg0 + 0x10) = loc[2];
    func_00129B28((s32)arg0, (s32)arg0, (s32)loc);
    *(f32 *)(arg0 + 0xA0) = EftMath_WrapAngle(Rand_FloatRange(*(f32 *)(arg1 + 0), *(f32 *)(arg1 + 0) + *(f32 *)(arg1 + 4)) * D_00384BA4);
    s = farg1 * D_00384BA4;
    *(f32 *)(arg0 + 0xAC) = EftMath_WrapAngle(s);
}
