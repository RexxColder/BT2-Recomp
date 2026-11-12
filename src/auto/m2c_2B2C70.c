#include "m2c_macros.h"

M2C_UNK func_002B2B98();                            /* extern */
M2C_UNK func_002B2BE8(s32, M2C_UNK);                /* extern */
s32 func_002B2CD0(s32, M2C_UNK);                    /* extern */

void func_002B2C70(s32 arg0, M2C_UNK arg1) {
    func_002B2B98(arg0, arg1);
    if (func_002B2CD0(arg0, arg1) == 0) {
        func_002B2BE8(arg0, arg1);
    }
}
