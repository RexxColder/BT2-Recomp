#include "m2c_macros.h"

s32 func_0024B3D8(s32);                             /* extern */

s32 func_0024B468(s32 arg0) {
    s32 temp_a0;
    s32 var_s0;
    s32 var_s2;

    var_s0 = 0;
    var_s2 = 0;
    if (arg0 > 0) {
        do {
            temp_a0 = var_s0;
            var_s0 += 1;
            var_s2 += func_0024B3D8(temp_a0);
        } while (var_s0 < arg0);
    }
    return var_s2;
}
