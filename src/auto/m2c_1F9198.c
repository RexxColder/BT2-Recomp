#include "m2c_macros.h"

void func_001F9198(s32 arg0) {
    s32 var_v0;
    void *var_a0;

    var_a0 = arg0 + 0xB01;
    var_v0 = 3;
    do {
        var_v0 -= 1;
        M2C_FIELD(var_a0, s8 *, -1) = 0;
        M2C_FIELD(var_a0, s8 *, 0) = 0;
        var_a0 += 0x14;
    } while (var_v0 >= 0);
}
