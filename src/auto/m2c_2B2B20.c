#include "m2c_macros.h"

M2C_UNK func_002B2B80();                /* extern */
M2C_UNK func_002B2BE8();                /* extern */
s32 func_002B2CD0();                    /* extern */

void func_002B2B20(s32 arg0, M2C_UNK arg1) {
    func_002B2BE8(arg0, arg1);
    if (func_002B2CD0(arg0, arg1) == 1) {
        func_002B2BE8(arg0, arg1);
    }
    func_002B2B80(arg0, arg1);
}
