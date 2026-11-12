#include "common.h"

void *memset(void *s, int c, unsigned int n);

void func_001EB1B8(u8 *arg0, u8 *arg1) {
    u8 *temp_s0;
    u8 *var_v0;
    u8 *var_v1;

    temp_s0 = *(u8 **)(arg0 + 0x38);
    memset(temp_s0, 0, 0x70);
    var_v1 = temp_s0;
    var_v0 = arg1;
    do {
        *(s64 *)(var_v1 + 0x00) = *(s64 *)(var_v0 + 0x00);
        *(s64 *)(var_v1 + 0x08) = *(s64 *)(var_v0 + 0x08);
        *(s64 *)(var_v1 + 0x10) = *(s64 *)(var_v0 + 0x10);
        *(s64 *)(var_v1 + 0x18) = *(s64 *)(var_v0 + 0x18);
        var_v0 += 0x20;
        var_v1 += 0x20;
    } while (var_v0 != arg1 + 0x40);
    *(s64 *)(var_v1 + 0x00) = *(s64 *)(var_v0 + 0x00);
    *(s64 *)(var_v1 + 0x08) = *(s64 *)(var_v0 + 0x08);
    *(s32 *)(temp_s0 + 0x64) = 0;
    *(s32 *)(temp_s0 + 0x68) = 0;
    *(u16 *)(temp_s0 + 0x60) = (u16)(*(u16 *)(temp_s0 + 0x60) | 9);
    *(f32 *)(temp_s0 + 0x5C) = *(f32 *)(arg1 + 0x30) * 30.0f;
}
