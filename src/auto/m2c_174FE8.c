#include "m2c_macros.h"

void *func_00174FE8(s32 arg0) {
    s32 var_v1;
    void *var_a0;
    void *var_a1;

    var_a0 = arg0 + 0xAB4;
    var_a1 = NULL;
    var_v1 = 0x1D;
    do {
        var_v1 -= 1;
        var_a1 = (M2C_FIELD(var_a0, s32 *, 4) == 0) ? var_a0 : var_a1;
        var_a0 += 8;
    } while (var_v1 >= 0);
    return var_a1;
}
