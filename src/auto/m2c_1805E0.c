#include "m2c_macros.h"

extern s32 *D_00387798;

s32 func_001805E0(s32 arg0) {
    s32 *temp_a1;
    s32 var_a2;
    s32 var_t0;

    var_t0 = -1;
    var_a2 = 0;
    if (*D_00387798 == 0) {
        *D_00387798 = arg0;
        var_t0 = 0;
    } else {
loop_2:
        var_a2 += 1;
        temp_a1 = &D_00387798[var_a2];
        if (var_a2 < 3) {
            if (*temp_a1 == 0) {
                *temp_a1 = arg0;
                var_t0 = var_a2;
            } else {
                goto loop_2;
            }
        }
    }
    return var_t0;
}
