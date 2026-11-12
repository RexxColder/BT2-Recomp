#include "common.h"

f32 EftMath_WrapAngle(f32 arg0);
f32 sinf(f32 arg0);

void func_001B0728(u8 *arg0, f32 farg0) {
    f32 temp_f0;

    temp_f0 = sinf(*(f32 *)(arg0 + 0x68));
    *(f32 *)(arg0 + 0x6C) = *(f32 *)(arg0 + 0x6C) + temp_f0 * farg0;
    *(f32 *)(arg0 + 0x68) = EftMath_WrapAngle(*(f32 *)(arg0 + 0x68) + 0.25f);
    *(f32 *)(arg0 + 0x4) = *(f32 *)(arg0 + 0x4) + *(f32 *)(arg0 + 0x6C);
}
