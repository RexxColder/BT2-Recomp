#include "common.h"

s32 func_001B5CF0(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 var_f1;
    f32 var_f2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;

    var_v1 = *(s32 *)(arg0 + 0x48);
    var_v0 = var_v1 & 4;
    if (var_v1 & 2) {
        temp_f0 = *(f32 *)(arg0 + 0x40) - 1.0f;
        *(f32 *)(arg0 + 0x40) = temp_f0;
        if (temp_f0 <= 0.0f) {
            temp_v0 = var_v1 | 4;
            *(s32 *)(arg0 + 0x48) = temp_v0;
            var_v1 = temp_v0;
        }
        if (var_v1 & 0x20) {
            temp_f0_2 = *(f32 *)(arg0 + 0x28);
            var_f1 = temp_f0_2 * *(f32 *)(arg0 + 0x2C);
            var_f2 = *(f32 *)(arg0 + 0x24) + temp_f0_2;
            goto block_7;
        }
        var_v0_2 = var_v1 & 8;
        if (var_v1 & 0x40) {
            temp_f0_3 = *(f32 *)(arg0 + 0x28);
            var_f1 = temp_f0_3 * *(f32 *)(arg0 + 0x2C);
            var_f2 = *(f32 *)(arg0 + 0x24) - temp_f0_3;
block_7:
            *(f32 *)(arg0 + 0x24) = var_f2;
            *(f32 *)(arg0 + 0x28) = *(f32 *)(arg0 + 0x28) + var_f1;
            var_v0_2 = var_v1 & 8;
        }
        if (var_v0_2 == 0) {
            if (var_v1 & 0x10) {
                temp_f0_4 = *(f32 *)(arg0 + 0x34) - *(f32 *)(arg0 + 0x38);
                *(f32 *)(arg0 + 0x34) = temp_f0_4;
                if (temp_f0_4 <= *(f32 *)(arg0 + 0x3C)) {
                    var_v0_3 = -0x11;
                    goto block_16;
                }
            }
        } else {
            temp_f0_5 = *(f32 *)(arg0 + 0x34) + *(f32 *)(arg0 + 0x38);
            *(f32 *)(arg0 + 0x34) = temp_f0_5;
            if (*(f32 *)(arg0 + 0x3C) <= temp_f0_5) {
                var_v0_3 = -9;
block_16:
                *(f32 *)(arg0 + 0x34) = *(f32 *)(arg0 + 0x3C);
                temp_v0_2 = var_v1 & var_v0_3;
                *(s32 *)(arg0 + 0x48) = temp_v0_2;
                var_v1 = temp_v0_2;
            }
        }
        var_v0 = var_v1 & 4;
    }
    return var_v0 != 0;
}
