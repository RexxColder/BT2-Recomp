#include "m2c_macros.h"

s32 func_002F3010(s32, M2C_UNK);                    /* extern */
M2C_UNK func_002F33C0();                            /* extern */
M2C_UNK func_002F33D8();                            /* extern */

s32 func_002F2FC8(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    func_002F33C0();
    temp_s0 = func_002F3010(arg0, arg1);
    func_002F33D8();
    return temp_s0;
}
