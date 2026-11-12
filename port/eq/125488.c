#include "common.h"

s32 func_00126040(u8 *arg0);
s32 func_00210DD8(s32 arg0);
u8 *func_00211288(s32 arg0);

void func_00125488(u8 *arg0) {
    f32 temp_f2;
    s32 temp_a1;
    s32 temp_a3;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = arg0 + 0x10A0;
    temp_v0 = func_00211288(func_00210DD8(func_00126040(arg0)));
    temp_a3 = *(s32 *)(temp_v0 + 0x14FC);
    temp_a1 = temp_a3 + *(s32 *)(temp_v0 + 0x1500) + *(s32 *)(temp_v0 + 0x1504) + *(s32 *)(temp_v0 + 0x1508) + *(s32 *)(temp_v0 + 0x150C);
    if (temp_a1 == 0) {
        *(f32 *)(temp_s0 + 0xF4) = 0.0f;
        *(f32 *)(temp_s0 + 0xE4) = 0.0f;
        *(f32 *)(temp_s0 + 0xE8) = 0.0f;
        *(f32 *)(temp_s0 + 0xEC) = 0.0f;
        *(f32 *)(temp_s0 + 0xF0) = 0.0f;
        return;
    }
    temp_f2 = (f32)temp_a1;
    *(f32 *)(temp_s0 + 0xE4) = (f32)temp_a3 / temp_f2;
    *(f32 *)(temp_s0 + 0xE8) = (f32)*(s32 *)(temp_v0 + 0x1500) / temp_f2;
    *(f32 *)(temp_s0 + 0xEC) = (f32)*(s32 *)(temp_v0 + 0x1504) / temp_f2;
    *(f32 *)(temp_s0 + 0xF0) = (f32)*(s32 *)(temp_v0 + 0x1508) / temp_f2;
    *(f32 *)(temp_s0 + 0xF4) = (f32)*(s32 *)(temp_v0 + 0x150C) / temp_f2;
}
