#include "m2c_macros.h"

M2C_UNK func_002AF578(s32, M2C_UNK);                /* extern */
s32 func_002AF5E8();                                /* extern */

s32 func_002AF648(s32 arg0, M2C_UNK arg1) {
    s32 temp_v0;

    temp_v0 = func_002AF5E8(arg0);
    if (temp_v0 != 0) {
        func_002AF578(arg0, arg1);
    }
    return temp_v0 & 0xFF;
}
