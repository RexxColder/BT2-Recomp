#include "m2c_macros.h"

M2C_UNK func_002D6C90(M2C_UNK, M2C_UNK, M2C_UNK *); /* extern */
extern M2C_UNK D_0037AD90 __attribute__((section(".data")));

s32 func_002D8008(u32 arg0) {
    s32 var_v1;

    var_v1 = 1;
    if (arg0 != 0x10) {
        if (arg0 >= 0x11U) {
            var_v1 = 2;
            if (arg0 != 0x18) {
                var_v1 = 3;
                if (arg0 != 0x20) {
                    goto block_5;
                }
            }
        } else {
block_5:
            func_002D6C90(0, 0, &D_0037AD90);
            var_v1 = 0;
        }
    }
    return var_v1;
}
