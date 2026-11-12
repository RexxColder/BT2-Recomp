#include "m2c_macros.h"

void func_001F91C8(s32 arg0) {
    s32 var_v0;
    s8 *var_a0;

    var_a0 = arg0 + 0xB3E;
    var_v0 = 3;
    do {
        var_v0 -= 1;
        *var_a0 = 0;
        var_a0 -= 0x14;
    } while (var_v0 >= 0);
}
