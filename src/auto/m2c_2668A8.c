#include "m2c_macros.h"

s32 func_002668A8(void *arg0, f32 *arg1) {
    f32 temp_f1;
    s32 var_v0;

    temp_f1 = M2C_FIELD(arg0, f32 *, 0xFC0);
    var_v0 = 0;
    if (temp_f1 != 0.0f) {
        *arg1 = temp_f1;
        var_v0 = 1;
    }
    return var_v0;
}
