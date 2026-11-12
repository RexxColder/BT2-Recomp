#include "common.h"

f32 Rand_FloatRange(f32 farg0, f32 farg1);
f32 EftMath_WrapAngle(f32 farg0);
f32 sinf(f32 farg0);
f32 cosf(f32 farg0);
void func_00129B28(void *arg0, void *arg1, void *arg2);
extern f32 D_00384BDC;

void func_00188F78(void *arg0, void *arg1, void *arg2, void *arg3, f32 farg0, f32 farg1) {
    s64 sp[4];
    f32 t22;
    f32 t21;
    f32 t20;
    f32 t20b;
    f32 r;

    t22 = D_00384BDC;
    sp[0] = ((s64 *)arg2)[0];
    sp[1] = ((s64 *)arg2)[1];
    sp[2] = ((s64 *)arg3)[0];
    sp[3] = ((s64 *)arg3)[1];

    r = Rand_FloatRange(*(f32 *)((u8 *)arg1 + 0x10), *(f32 *)((u8 *)arg1 + 0x14));
    t21 = EftMath_WrapAngle(r * t22);
    r = Rand_FloatRange(*(f32 *)((u8 *)arg1 + 0x3C),
                        *(f32 *)((u8 *)arg1 + 0x3C) + *(f32 *)((u8 *)arg1 + 0x40));
    *(s32 *)arg0 = 0;
    t20 = *(f32 *)((u8 *)arg1 + 0x44) + r;
    t20b = t20 * farg0;
    *(f32 *)((u8 *)arg0 + 4) = sinf(EftMath_WrapAngle(t21)) * t20b;
    r = cosf(EftMath_WrapAngle(t21)) * t20b;
    *(f32 *)((u8 *)arg0 + 0xC) = 1.0f;
    *(f32 *)((u8 *)arg0 + 8) = r;
    *(s64 *)((u8 *)arg0 + 0x18) = sp[3];
    *(s64 *)((u8 *)arg0 + 0x10) = sp[2];
    func_00129B28(arg0, arg0, sp);
    r = Rand_FloatRange(*(f32 *)((u8 *)arg1 + 0), *(f32 *)((u8 *)arg1 + 0) + *(f32 *)((u8 *)arg1 + 4));
    *(f32 *)((u8 *)arg0 + 0xA0) = EftMath_WrapAngle(r * t22);
    *(f32 *)((u8 *)arg0 + 0xAC) = EftMath_WrapAngle(farg1 * t22);
}
