#include "m2c_macros.h"

s32 func_002EB030(s32);                             /* extern */
M2C_UNK func_002ED118();                            /* extern */
M2C_UNK func_002ED130();                            /* extern */

s32 func_002EAFF8(s32 arg0) {
    s32 temp_s0;

    func_002ED118();
    temp_s0 = func_002EB030(arg0);
    func_002ED130();
    return temp_s0;
}
