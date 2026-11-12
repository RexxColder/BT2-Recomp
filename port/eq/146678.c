#include "common.h"

s32 rand(void);
extern f32 D_00384554;
extern u8 *gEftWeather;

void func_00146678(u8 *arg0, s32 arg1) {
    f32 temp_f20;
    s32 temp_v0;
    s32 var_a1;
    s32 var_s1;
    u8 *var_a0;
    u8 *var_s0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_s1 = 0x1D;
    temp_f20 = D_00384554;
    var_s0 = *(u8 **)(var_a0 + 0x38);
    do {
        var_s1 -= 1;
        *(f32 *)(var_s0 + 0) = (f32)((f32)((rand() & 0x3FF) - 0x1FF) * temp_f20);
        *(f32 *)(var_s0 + 4) = (f32)((f32)((rand() & 0x3FF) - 0x1FF) * temp_f20);
        temp_v0 = rand();
        *(f32 *)(var_s0 + 0xC) = 1.0f;
        *(s32 *)(var_s0 + 0x10) = 0;
        *(s32 *)(var_s0 + 0x14) = 0;
        *(s32 *)(var_s0 + 0x18) = 0;
        *(s32 *)(var_s0 + 0x1C) = 0;
        *(s64 *)(var_s0 + 0x20) = 0;
        *(s32 *)(var_s0 + 0x28) = 0;
        *(f32 *)(var_s0 + 8) = (f32)((f32)((temp_v0 & 0x3FF) - 0x1FF) * temp_f20);
        var_a0 = gEftWeather;
        var_a1 = rand() % *(s32 *)(var_a0 + 0x208);
        *(s32 *)(var_s0 + 0x2C) = var_a1;
        var_s0 += 0x30;
    } while (var_s1 >= 0);
    *(s8 *)(gEftWeather + 0x2B0) = 1;
}
