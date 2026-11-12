#include "common.h"

s32 func_00126040(s32 arg0);
s32 func_00210DD8(s32 arg0);
s32 func_00211288(s32 arg0);

void func_00125048(s32 arg0) {
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_a3;
    s32 temp_a1;
    f32 temp_f2;

    temp_s0 = arg0 + 0x10A0;
    temp_v0 = func_00211288(func_00210DD8(func_00126040(arg0)));
    temp_a3 = *(s32 *)(temp_v0 + 0x147C);
    temp_a1 = temp_a3 + *(s32 *)(temp_v0 + 0x1480) + *(s32 *)(temp_v0 + 0x1484) +
              *(s32 *)(temp_v0 + 0x1488) + *(s32 *)(temp_v0 + 0x148C) + *(s32 *)(temp_v0 + 0x1490) +
              *(s32 *)(temp_v0 + 0x1494) + *(s32 *)(temp_v0 + 0x1498);
    if (temp_a1 == 0) {
        *(s32 *)(temp_s0 + 0xB0) = 0;
        *(s32 *)(temp_s0 + 0x94) = 0;
        *(s32 *)(temp_s0 + 0x98) = 0;
        *(s32 *)(temp_s0 + 0x9C) = 0;
        *(s32 *)(temp_s0 + 0xA0) = 0;
        *(s32 *)(temp_s0 + 0xA4) = 0;
        *(s32 *)(temp_s0 + 0xA8) = 0;
        *(s32 *)(temp_s0 + 0xAC) = 0;
        return;
    }
    temp_f2 = (f32)temp_a1;
    *(f32 *)(temp_s0 + 0x94) = (f32)temp_a3 / temp_f2;
    *(f32 *)(temp_s0 + 0x98) = (f32)*(s32 *)(temp_v0 + 0x1480) / temp_f2;
    *(f32 *)(temp_s0 + 0x9C) = (f32)*(s32 *)(temp_v0 + 0x1484) / temp_f2;
    *(f32 *)(temp_s0 + 0xA0) = (f32)*(s32 *)(temp_v0 + 0x1488) / temp_f2;
    *(f32 *)(temp_s0 + 0xA4) = (f32)*(s32 *)(temp_v0 + 0x148C) / temp_f2;
    *(f32 *)(temp_s0 + 0xA8) = (f32)*(s32 *)(temp_v0 + 0x1490) / temp_f2;
    *(f32 *)(temp_s0 + 0xAC) = (f32)*(s32 *)(temp_v0 + 0x1494) / temp_f2;
    *(f32 *)(temp_s0 + 0xB0) = (f32)*(s32 *)(temp_v0 + 0x1498) / temp_f2;
}
