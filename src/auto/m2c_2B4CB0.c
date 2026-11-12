#include "m2c_macros.h"

M2C_UNK func_002B4C20(s32, s32);                    /* extern */

void func_002B4CB0(s32 arg0) {
    s32 *var_s0;
    s32 temp_a1;
    s32 var_s2;

    var_s0 = arg0 + 0x280;
    var_s2 = 0x1F;
    do {
        temp_a1 = *var_s0;
        if (temp_a1 != 0) {
            func_002B4C20(arg0, temp_a1);
            *var_s0 = 0;
        }
        var_s2 -= 1;
        var_s0 -= 1;
    } while (var_s2 >= 0);
}
