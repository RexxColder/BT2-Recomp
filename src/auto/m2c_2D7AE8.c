#include "m2c_macros.h"

s32 func_002D7AE8(f32 arg0, f32 arg1) {
    s32 var_v0;

    var_v0 = 1;
    if (arg1 <= arg0) {
        var_v0 = 0;
    }
    if ((arg1 - arg0) < -14.0f) {
        var_v0 = 0;
    }
    return var_v0;
}
