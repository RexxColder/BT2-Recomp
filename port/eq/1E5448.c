#include "common.h"

s32 func_001E5448(f32 *arg0, s32 arg1, s32 arg2, f32 farg0) {
    f32 *var_a3;
    f32 *var_a3_2;
    f32 *var_t2;
    f32 *var_v1;
    f32 temp_f0;
    s32 var_t0;
    s32 var_t1;
    s32 var_v0;
    s32 var_v0_2;

    var_t0 = arg1;
    var_t1 = arg2;
    if (var_t1 >= var_t0) {
        var_t2 = arg0 + var_t1;
        var_v1 = arg0 + var_t0;
loop_2:
        var_v0 = var_t1 < arg1;
        if ((arg2 >= var_t0) && (*var_v1 < farg0)) {
            var_a3 = arg0 + var_t0;
loop_5:
            var_t0 += 1;
            var_a3 += 1;
            var_v1 += 1;
            if (arg2 >= var_t0) {
                if (*var_a3 < farg0) {
                    goto loop_5;
                }
            }
            var_v0 = var_t1 < arg1;
        }
        var_v0_2 = var_t1 < var_t0;
        if ((var_v0 == 0) && (farg0 <= *var_t2)) {
            var_a3_2 = arg0 + var_t1;
            var_t1 -= 1;
loop_11:
            var_a3_2 -= 1;
            var_t2 -= 1;
            if (var_t1 >= arg1) {
                if (farg0 <= *var_a3_2) {
                    var_t1 -= 1;
                    goto loop_11;
                }
            }
            var_v0_2 = var_t1 < var_t0;
        }
        if (var_v0_2 == 0) {
            temp_f0 = *var_v1;
            var_t0 += 1;
            var_t1 -= 1;
            *var_v1 = *var_t2;
            var_v1 += 1;
            *var_t2 = temp_f0;
            var_t2 -= 1;
            if (var_t1 >= var_t0) {
                goto loop_2;
            }
        }
    }
    return var_t0;
}
