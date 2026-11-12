#include "m2c_macros.h"

void func_002BFE68(void *arg0) {
    s32 var_v0;
    void *var_a0;

    var_a0 = arg0;
    var_v0 = 2;
    do {
        var_v0 -= 1;
        M2C_FIELD(var_a0, s32 *, 0) = 0;
        M2C_FIELD(var_a0, s32 *, 4) = 0;
        M2C_FIELD(var_a0, s32 *, 8) = 0;
        M2C_FIELD(var_a0, s32 *, 0xC) = 0;
        var_a0 += 0x10;
    } while (var_v0 >= 0);
}
