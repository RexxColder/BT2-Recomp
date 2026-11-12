#include "m2c_macros.h"

s32 func_002B7CB8();                                /* extern */
M2C_UNK func_002D1A98();                         /* extern */

void func_002B6B58(s32 arg0) {
    if (arg0 != 0) {
        func_002D1A98(func_002B7CB8(arg0));
        return;
    }
    func_002D1A98();
}
