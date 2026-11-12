#include "m2c_macros.h"

extern void *D_00387A40;

s32 func_002A9938(void) {
    s32 var_a1;
    s32 var_a2;
    void *var_a0;

    var_a1 = 3;
    var_a2 = 0;
    var_a0 = M2C_FIELD(D_00387A40, s32 *, 8) + 0x3F60;
    do {
        if (M2C_FIELD(var_a0, s32 *, 0xC) != 0) {
            var_a2 = (M2C_FIELD(var_a0, s32 *, 0xAF0) & 2) ? (var_a1 - 2) : var_a2;
        }
        var_a1 += 1;
        var_a0 += 0x1520;
    } while (var_a1 < 0xC);
    return var_a2;
}
