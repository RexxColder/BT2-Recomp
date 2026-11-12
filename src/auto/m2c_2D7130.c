#include "m2c_macros.h"

M2C_UNK func_002D6DD0(s32, M2C_UNK);                /* extern */
M2C_UNK func_002D6F48(s32, M2C_UNK, u32, u32);      /* extern */
M2C_UNK func_002D8D78(s32);                         /* extern */

void func_002D7130(s32 arg0, s32 arg1) {
    u32 temp_s0;

    temp_s0 = arg1 & 0xFF;
    func_002D8D78(arg1);
    func_002D6DD0(arg0, 0);
    func_002D6F48(arg0, 0, temp_s0 >> 1, temp_s0);
}
