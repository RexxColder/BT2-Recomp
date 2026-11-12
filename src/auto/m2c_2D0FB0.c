#include "m2c_macros.h"

s32 func_002D07B0(s32, M2C_UNK);                    /* extern */
M2C_UNK func_002D1000();                            /* extern */
M2C_UNK func_002D1B88(s32);                         /* extern */

void func_002D0FB0(s32 arg0) {
    func_002D1000(arg0);
    if (func_002D07B0(arg0, 0x47) == 1) {
        func_002D1B88(arg0);
    }
}
