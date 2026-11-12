#include "m2c_macros.h"

s32 func_002FFC50(s32, M2C_UNK);                    /* extern */
M2C_UNK func_00300790();                            /* extern */
M2C_UNK func_00300798();                            /* extern */

s32 func_002FFC08(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    func_00300790();
    temp_s0 = func_002FFC50(arg0, arg1);
    func_00300798();
    return temp_s0;
}
