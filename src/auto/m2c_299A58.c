#include "m2c_macros.h"

M2C_UNK Mathf_Acos(f32);                            /* extern */

void func_00299A58(f32 arg0) {
    f32 var_f12;

    var_f12 = arg0;
    if (var_f12 > 1.0f) {
        var_f12 = 1.0f;
    }
    if (var_f12 < -1.0f) {
        var_f12 = -1.0f;
    }
    Mathf_Acos(var_f12);
}
