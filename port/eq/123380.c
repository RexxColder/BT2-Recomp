#include "common.h"

s32 func_00123300(s32 arg0, f32 farg0);

void func_00123380(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0) {
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a0;
    s32 s2;
    s32 s3;
    s32 s4;
    u8 *temp_a0;
    u8 *temp_s1;
    u8 *temp_v1;
    u8 *var_a1;

    s2 = arg1 & 0xFF;
    s3 = arg2 & 0xFF;
    s4 = (s8)arg3;
    temp_s1 = (u8 *)arg0 + 0x160;
    temp_v1 = (u8 *)arg0 + s2 + 0xA9C;
    *temp_v1 = (u8)(*temp_v1 | 1);
    temp_v0 = func_00123300(arg0, farg0);
    var_a0 = *(s32 *)(temp_s1 + 0x28) + *(s32 *)(temp_s1 + 0x2C);
    temp_a2 = arg0 + 0x16C;
    if (temp_v0 < var_a0) {
        var_a1 = (u8 *)(var_a0 + temp_a2 + 0x830);
        do {
            var_a0 -= 1;
            *var_a1 = *(var_a1 - 1);
            var_a1 -= 1;
        } while (temp_v0 < var_a0);
    }
    *(u8 *)(temp_v0 + temp_a2 + 0x830) = (u8)s2;
    temp_a0 = temp_s1 + ((s2 * 8) + 0x30);
    *(u8 *)(temp_a0 + 0xC) = (u8)s3;
    *(f32 *)(temp_a0 + 0x10) = farg0;
    *(s8 *)(temp_a0 + 0xD) = (s8)s4;
    *(s32 *)(temp_s1 + 0x2C) = *(s32 *)(temp_s1 + 0x2C) + 1;
}
