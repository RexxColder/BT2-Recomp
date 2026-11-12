#include "m2c_macros.h"

void func_001F9138(void *arg0) {
    s32 var_v1;
    void *var_v0;

    var_v1 = 3;
    var_v0 = arg0 + 0xAFD;
    do {
        var_v1 -= 1;
        M2C_FIELD(var_v0, s8 *, -1) = 0;
        M2C_FIELD(var_v0, s8 *, 0) = 0;
        var_v0 += 0x14;
    } while (var_v1 >= 0);
    M2C_FIELD(arg0, s8 *, 0xAF4) = 0;
}
