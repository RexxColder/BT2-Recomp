#include "m2c_macros.h"

M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_001B7FC0(void *arg0) {
    s32 var_s2;
    void *var_s0;

    var_s2 = 9;
    var_s0 = M2C_FIELD(arg0, void **, 0x68);
    do {
        if (M2C_FIELD(var_s0, s32 *, 0x58) == M2C_FIELD(arg0, s32 *, 0x64)) {
            memset(var_s0, 0, 0x60);
        }
        var_s2 -= 1;
        var_s0 += 0x60;
    } while (var_s2 >= 0);
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
}
