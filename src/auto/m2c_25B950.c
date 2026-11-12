#include "m2c_macros.h"

f32 func_0025AAD0();                                /* extern */
f32 func_0025AAF0();                                /* extern */

s32 func_0025B950(void) {
    f32 temp_f20;
    s32 var_v0;

    temp_f20 = func_0025AAD0();
    var_v0 = 1;
    if (temp_f20 != func_0025AAF0()) {
        var_v0 = 0;
    }
    return var_v0;
}
