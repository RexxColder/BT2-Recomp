#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);

void func_0019FA10(u8 *arg0, u8 *arg1) {
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;
    u8 *temp_s0;

    temp_s0 = (u8 *)*(s32 *)(arg0 + 0x38);
    memset(temp_s0, 0, 0x40);
    *(s64 *)(temp_s0 + 0x00) = *(s64 *)(arg1 + 0x00);
    *(s64 *)(temp_s0 + 0x08) = *(s64 *)(arg1 + 0x08);
    *(s64 *)(temp_s0 + 0x10) = *(s64 *)(arg1 + 0x10);
    *(s64 *)(temp_s0 + 0x18) = *(s64 *)(arg1 + 0x18);
    temp_f1 = *(f32 *)(temp_s0 + 0x10) * 30.0f;
    temp_f2 = *(f32 *)(temp_s0 + 0x14) * 30.0f;
    temp_f0 = *(f32 *)(temp_s0 + 0x18) * 30.0f;
    *(s32 *)(temp_s0 + 0x30) = 1;
    *(f32 *)(temp_s0 + 0x24) = temp_f1;
    *(f32 *)(temp_s0 + 0x10) = temp_f1;
    *(f32 *)(temp_s0 + 0x14) = temp_f2;
    *(f32 *)(temp_s0 + 0x28) = temp_f0;
    *(f32 *)(temp_s0 + 0x18) = temp_f0;
}
