#include "m2c_macros.h"

M2C_UNK func_001B1A20(s32, s32, void *);            /* extern */

void func_001B2930(void *arg0) {
    s32 temp_s1;
    s32 var_s2;
    void *var_s0;

    var_s2 = 0xF;
    temp_s1 = M2C_FIELD(arg0, s32 *, 0x38);
    var_s0 = temp_s1 + 0x40;
    do {
        if (M2C_FIELD(var_s0, s32 *, 8) & 1) {
            func_001B1A20(temp_s1, temp_s1, var_s0);
        }
        var_s2 -= 1;
        var_s0 += 0xA0;
    } while (var_s2 >= 0);
}
