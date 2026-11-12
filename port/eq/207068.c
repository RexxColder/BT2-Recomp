#include "common.h"

extern u8 *D_00387A40;

s32 func_00207068(u8 *arg0) {
    s32 temp_a0;
    s32 var_a2;
    s32 var_v0;
    u8 *temp_v0;
    f32 temp_f0;
    f32 temp_f1;
    f32 temp_f2;

    temp_a0 = *(s32 *)(arg0 + 0x142C);
    var_a2 = 0;
    var_v0 = 0;
    if (temp_a0 >= 0) {
        var_v0 = 1;
        if (temp_a0 < *(s32 *)(D_00387A40 + 0xC)) {
            temp_v0 = *(u8 **)(D_00387A40 + 0x8) + (temp_a0 * 0x1520) + 0xBD0;
            temp_f1 = *(f32 *)(temp_v0 + 0x10);
            temp_f2 = *(f32 *)(temp_v0 + 0x8);
            temp_f0 = temp_f1 + *(f32 *)(temp_v0 + 0x18);
            *(f32 *)(temp_v0 + 0x14) = temp_f1;
            *(f32 *)(temp_v0 + 0x10) = temp_f0;
            if (temp_f2 <= temp_f0) {
                *(f32 *)(temp_v0 + 0x10) = temp_f2;
                var_a2 = 1;
            }
            var_v0 = var_a2;
        }
    }
    return var_v0;
}
