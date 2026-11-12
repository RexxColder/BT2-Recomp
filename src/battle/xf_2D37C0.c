#include "m2c_macros.h"

s32 func_002D37C0(void *arg0) {
    s32 *var_a0;
    s32 temp_a1;
    s32 temp_v0;
    s32 var_a2;
    s32 var_v1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x10);
    var_a2 = 0;
    if (temp_a1 > 0) {
        var_a0 = arg0 + 0x18;
        var_v1 = temp_a1;
        do {
            temp_v0 = *var_a0;
            var_a0 += 1;
            var_v1 -= 1;
            var_a2 += temp_v0;
        } while (var_v1 != 0);
    }
    return var_a2 / temp_a1;
}
