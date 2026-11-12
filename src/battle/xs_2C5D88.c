#include "m2c_macros.h"

s32 func_002C2D98(s32);                             /* extern */
M2C_UNK func_002C57A8(s32, M2C_UNK, M2C_UNK);       /* extern */
s32 func_002D07B0(s32, s32);                       /* extern */

void func_002C5D88(s32 arg0) {
    M2C_UNK var_a2;
    s32 temp_v0;

    if (func_002D07B0(arg0, 0x1C) != 0) {
        temp_v0 = func_002C2D98(arg0);
        var_a2 = 1;
        if ((temp_v0 == 0) || (var_a2 = 0, (temp_v0 > 0)) || (temp_v0 != -1)) {
            func_002C57A8(arg0, 5, var_a2);
        }
    }
}
