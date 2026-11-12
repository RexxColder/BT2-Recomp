#include "common.h"

s32 func_002D2948(s32 *arg0, s32 arg1) {
    s32 *var_s0;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s1;

    var_s0 = arg0;
    var_s1 = 0;
    var_a0 = 0;
    while (var_s1 < 0xF) {
        var_s1 += 1;
        temp_v0 = *var_s0;
        var_s0 += 1;
        if (temp_v0 == 0) {
            break;
        }
        var_a0 = ((s32 (*)(s32, s32, s32, s32)) (*(s32 *) (temp_v0 + arg1 * 4)))(0, 0, 0, 0);
        if (var_a0 != 0) {
            break;
        }
    }
    return var_a0;
}
