#include "m2c_macros.h"

M2C_UNK func_002614E0(s32, M2C_UNK, M2C_UNK);       /* extern */
M2C_UNK func_00261558(s32, M2C_UNK);                /* extern */

void func_001EDC68(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;

    temp_s0 = arg0 & 0xFFFF;
    func_00261558(temp_s0, 0);
    func_002614E0(temp_s0, arg1, arg2);
}
