#include "m2c_macros.h"

s32 func_0026FFA0(void *arg0) {
    s32 var_a3;
    u16 *var_a0;
    u16 temp_v1;
    u32 temp_a1;
    u32 var_a2;

    temp_a1 = M2C_FIELD(arg0, u32 *, 4);
    var_a2 = 0;
    var_a3 = 0;
    if (temp_a1 != 0) {
        var_a0 = M2C_FIELD(arg0, s32 *, 0) + 0xBA;
        do {
            temp_v1 = *var_a0;
            var_a0 += 96;
            var_a2 += 1;
            var_a3 += temp_v1;
        } while (var_a2 < temp_a1);
    }
    return var_a3;
}
