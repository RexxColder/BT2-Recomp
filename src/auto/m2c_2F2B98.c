#include "m2c_macros.h"

s32 func_002F2BD0(s32);                             /* extern */
M2C_UNK func_002F33C0();                            /* extern */
M2C_UNK func_002F33D8();                            /* extern */

s32 func_002F2B98(s32 arg0) {
    s32 temp_s0;

    func_002F33C0();
    temp_s0 = func_002F2BD0(arg0);
    func_002F33D8();
    return temp_s0;
}
