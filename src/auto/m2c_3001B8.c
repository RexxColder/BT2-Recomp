#include "m2c_macros.h"

s32 func_003001F0(s32);                             /* extern */
M2C_UNK func_00300790();                            /* extern */
M2C_UNK func_00300798();                            /* extern */

s32 func_003001B8(s32 arg0) {
    s32 temp_s0;

    func_00300790();
    temp_s0 = func_003001F0(arg0);
    func_00300798();
    return temp_s0;
}
