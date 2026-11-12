#include "m2c_macros.h"

s32 func_002D07B0(void *, M2C_UNK);                         /* extern */
s32 func_002D26A8(s32);                             /* extern */

s32 func_002D4188(s32 arg0) {
    if (func_002D07B0(arg0, 0xF) == 0) {
        return 1;
    }
    return func_002D26A8(arg0) != 0;
}
