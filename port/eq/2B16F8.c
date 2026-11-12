#include "common.h"

void func_002B16F8(s32 arg0) {
    f32 temp_f2;
    f32 var_f0;
    f32 var_f0_2;

    if (*(s32 *)(arg0 + 0x10) == 0) {
        var_f0 = *(f32 *)(arg0 + 0xD0);
        temp_f2 = -70.0f;
        if (var_f0 > 70.0f) {
            *(f32 *)(arg0 + 0xD0) = 70.0f;
            var_f0 = 70.0f;
            *(f32 *)(arg0 + 0x120) = 70.0f;
        }
        if (var_f0 < temp_f2) {
            *(f32 *)(arg0 + 0xD0) = temp_f2;
            *(f32 *)(arg0 + 0x120) = temp_f2;
        }
        var_f0_2 = *(f32 *)(arg0 + 0xD8);
        if (var_f0_2 > 70.0f) {
            *(f32 *)(arg0 + 0xD8) = 70.0f;
            var_f0_2 = 70.0f;
            *(f32 *)(arg0 + 0x128) = 70.0f;
        }
        if (var_f0_2 < temp_f2) {
            *(f32 *)(arg0 + 0x128) = temp_f2;
            *(f32 *)(arg0 + 0xD8) = temp_f2;
        }
    }
}
