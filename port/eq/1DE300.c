#include "common.h"

s32 rand(void);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_0038563C;
extern s32 D_003878DC;

void func_001DE300(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f21;
    u8 *temp_s1;
    u8 *var_s0;
    u8 *var_v0;
    u8 *temp_v1;

    var_s0 = arg1;
    temp_s1 = *(u8 **)(arg0 + 0x38);
    memset(temp_s1, 0, 0x12C0);
    var_v0 = temp_s1 + 0x10;
    temp_v1 = var_s0 + 0x12A0;
    do {
        *(s64 *)(var_v0 + 0) = *(s64 *)(var_s0 + 0);
        *(s64 *)(var_v0 + 8) = *(s64 *)(var_s0 + 8);
        *(s64 *)(var_v0 + 0x10) = *(s64 *)(var_s0 + 0x10);
        *(s64 *)(var_v0 + 0x18) = *(s64 *)(var_s0 + 0x18);
        var_s0 += 0x20;
        var_v0 += 0x20;
    } while (var_s0 != temp_v1);
    temp_f21 = D_0038563C;
    *(s32 *)(temp_s1 + 0) = D_003878DC + 8;
    temp_f0 = (f32)rand();
    *(f32 *)(temp_s1 + 0x12B4) = -10.0f;
    *(f32 *)(temp_s1 + 0x12B0) = (temp_f0 / temp_f21) * 20.0f;
    temp_f0_2 = (f32)rand();
    *(f32 *)(temp_s1 + 0x12BC) = 1.0f;
    *(f32 *)(temp_s1 + 0x12B8) = (temp_f0_2 / temp_f21) * 20.0f;
}
