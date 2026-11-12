#include "m2c_macros.h"

M2C_UNK func_002E05A8(s32, s32, s32);               /* extern */

void func_002C58E8(void *arg0, s32 *arg1, s32 arg2) {
    s32 *var_s0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_s2;
    s32 var_s1;

    temp_s2 = *M2C_FIELD(arg0, s32 **, 0x1FC0);
    if (temp_s2 != 0) {
        var_s1 = 0;
        if (arg2 > 0) {
            var_s0 = arg1;
            do {
                temp_a2 = *var_s0;
                var_s0 += 1;
                temp_a1 = var_s1;
                var_s1 += 1;
                func_002E05A8(temp_s2, temp_a1, temp_a2);
            } while (var_s1 < arg2);
        }
    }
}
