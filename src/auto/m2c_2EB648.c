#include "m2c_macros.h"

s32 func_002EB690(s32, M2C_UNK);                    /* extern */
M2C_UNK func_002ED118();                            /* extern */
M2C_UNK func_002ED130();                            /* extern */

s32 func_002EB648(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    func_002ED118();
    temp_s0 = func_002EB690(arg0, arg1);
    func_002ED130();
    return temp_s0;
}
