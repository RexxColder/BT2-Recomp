#include "m2c_macros.h"

s32 *func_00202E60(void *, s32);                    /* extern */

s32 func_00203118(void *arg0) {
    s32 temp_a1;
    s32 var_s0;
    s32 var_s2;

    var_s0 = 0;
    var_s2 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x1184) > 0) {
        do {
            temp_a1 = var_s0;
            var_s0 += 1;
            var_s2 += *func_00202E60(arg0, temp_a1) > 0;
        } while (var_s0 < M2C_FIELD(arg0, s32 *, 0x1184));
    }
    return var_s2;
}
