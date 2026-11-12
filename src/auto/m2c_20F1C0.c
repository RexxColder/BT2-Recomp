#include "m2c_macros.h"

extern f32 D_003859E4;
extern f32 D_003859E8;
extern f32 D_003859EC;

f32 func_0020F1C0(s32 arg0) {
    f32 temp_f1;
    f32 var_f0;

    temp_f1 = (f32) arg0 * D_003859E4;
    var_f0 = temp_f1 / (fabsf(temp_f1) + 1.0f);
    if (D_003859E8 < var_f0) {
        var_f0 = D_003859E8;
    }
    if (var_f0 < D_003859EC) {
        var_f0 = D_003859EC;
    }
    return var_f0;
}
