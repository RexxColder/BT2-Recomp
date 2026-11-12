#include "m2c_macros.h"

M2C_UNK func_002E93F0();                            /* extern */
M2C_UNK func_002E93F8();                            /* extern */
s32 func_002F6820(s32, M2C_UNK);                    /* extern */

s32 func_002F67D8(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    func_002E93F0();
    temp_s0 = func_002F6820(arg0, arg1);
    func_002E93F8();
    return temp_s0;
}
