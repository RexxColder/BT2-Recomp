#include "m2c_macros.h"

void func_002D2A80(void *arg0, s32 arg1) {
    s32 *var_v0;
    s32 var_v1;

    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    var_v1 = 2;
    M2C_FIELD(arg0, s32 *, 0xC) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = 8;
    var_v0 = arg0 + 0x1C;
    do {
        var_v1 -= 1;
        *var_v0 = 8;
        var_v0 -= 1;
    } while (var_v1 >= 0);
    M2C_FIELD(arg0, s32 *, 0x20) = -1;
}
