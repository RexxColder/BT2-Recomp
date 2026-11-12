#include "common.h"

f32 func_001964F0(s32 arg0);
s32 func_0020B3D0(s32 arg0);
extern f32 D_00384CA4;
extern f32 D_00384CA8;
extern f32 D_00384CAC;
extern f32 D_00384CB0;

void func_00196B68(void *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f1;
    f32 var_f1;
    s32 temp_a0;
    u8 *temp_s0;

    temp_s0 = (u8 *)arg0 + 0xA10;
    temp_a0 = func_0020B3D0(*(s32 *)(*(u8 **)((u8 *)arg0 + 0xAF0)));
    if (*(s32 *)(temp_s0 + 0xB0) != 0) {
        if (arg1 & 0x80) {
            temp_f0 = 2.0f * func_001964F0(temp_a0);
            *(f32 *)(temp_s0 + 0x80) = 1.0f;
            temp_f0_2 = temp_f0 * D_00384CA4;
            *(s32 *)(temp_s0 + 0xB0) = *(s32 *)(temp_s0 + 0xB0) | 0x1080;
            *(f32 *)(temp_s0 + 0x8C) = 2.0f;
            var_f1 = (temp_f0_2 - 1.0f) / D_00384CA8;
            *(f32 *)(temp_s0 + 0x88) = temp_f0_2;
            *(f32 *)(temp_s0 + 0x84) = var_f1;
        } else if (arg1 & 0x100) {
            temp_f0_3 = func_001964F0(temp_a0) * D_00384CAC;
            temp_f1 = temp_f0_3 - *(f32 *)(temp_s0 + 0x80);
            *(s32 *)(temp_s0 + 0xB0) = (*(s32 *)(temp_s0 + 0xB0) & ~0x1000) | 0x100;
            *(f32 *)(temp_s0 + 0x88) = temp_f0_3;
            var_f1 = temp_f1 / D_00384CB0;
            *(f32 *)(temp_s0 + 0x84) = var_f1;
        }
    }
}
