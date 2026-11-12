#include "common.h"

void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);

void func_001AD690(u8 *arg0) {
    s32 temp_a0;
    s32 temp_v0;
    s32 var_s2;
    u8 *temp_s1;
    u8 *var_s0;

    temp_s1 = (u8 *)*(s32 *)(arg0 + 0x38);
    temp_a0 = *(s32 *)(temp_s1 + 0xC0);
    var_s0 = temp_s1 + 0x120;
    if (temp_a0 & 0x800) {
        temp_v0 = *(u16 *)(temp_s1 + 0x1C4) - 1;
        *(u16 *)(temp_s1 + 0x1C4) = (u16)temp_v0;
        if ((s32)((u32)temp_v0 << 16) <= 0) {
            *(u16 *)(temp_s1 + 0x1C4) = 0;
            *(s32 *)(temp_s1 + 0xC0) = temp_a0 & ~0x800;
            return;
        }
        var_s2 = 4;
        do {
            var_s2 -= 1;
            Vec3_Add((s32)var_s0, (s32)var_s0, (s32)(var_s0 + 0x10));
            *(f32 *)(var_s0 + 0x14) = *(f32 *)(var_s0 + 0x14) + *(f32 *)(temp_s1 + 0xE0);
            var_s0 += 0x20;
        } while (var_s2 >= 0);
    }
}
