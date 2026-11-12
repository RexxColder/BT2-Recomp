#include "common.h"

extern f32 D_00383F28;
extern f32 D_00383F2C;

f32 func_00116698(u8 *arg0, f32 farg0) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f4_2;
    f32 var_f0;
    f32 var_f1;
    f32 var_f3;

    temp_f0 = *(f32 *)(arg0 + 4);
    temp_f2 = *(f32 *)(arg0 + 0xC);
    if (temp_f0 < farg0) {
        var_f1 = 1.0f;
    } else if (!(temp_f2 < farg0)) {
        var_f1 = 0.0f;
    } else {
        var_f1 = (farg0 - temp_f2) / (temp_f0 - temp_f2);
    }
    var_f3 = *(f32 *)(arg0 + 0x14);
    if (var_f1 < var_f3) {
        temp_f0_2 = var_f3 - D_00383F28;
        *(f32 *)(arg0 + 0x14) = temp_f0_2;
        if (temp_f0_2 < var_f1) {
            *(f32 *)(arg0 + 0x14) = var_f1;
            var_f3 = var_f1;
        } else {
            var_f3 = temp_f0_2;
        }
    }
    if (var_f3 < var_f1) {
        temp_f0_3 = var_f3 + D_00383F2C;
        *(f32 *)(arg0 + 0x14) = temp_f0_3;
        if (var_f1 < temp_f0_3) {
            *(f32 *)(arg0 + 0x14) = var_f1;
            var_f3 = var_f1;
        } else {
            var_f3 = temp_f0_3;
        }
    }
    temp_f4 = temp_f2 + *(f32 *)(arg0 + 8);
    var_f0 = 1.0f;
    temp_f4_2 = temp_f4 + ((*(f32 *)(arg0 + 0) - temp_f4) * var_f3);
    if (temp_f4_2 != 0.0f) {
        var_f0 = 1.0f / temp_f4_2;
    }
    return var_f0;
}
