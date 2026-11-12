#include "m2c_macros.h"

s32 func_002F2C30(s32, M2C_UNK, M2C_UNK);           /* extern */
M2C_UNK func_002F33C0();                            /* extern */
M2C_UNK func_002F33D8();                            /* extern */

s32 func_002F2BD8(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;

    func_002F33C0();
    temp_s0 = func_002F2C30(arg0, arg1, arg2);
    func_002F33D8();
    return temp_s0;
}
