#include "m2c_macros.h"

u32 func_002D8278();                                /* extern */
s32 func_002D8698(s32, s32, M2C_UNK);               /* extern */

s32 func_002D8498(s32 arg0, s32 arg1) {
    if ((arg0 == 0) || (arg1 < 0)) {
        return 0;
    }
    if (func_002D8278(arg0, arg1) >= 2U) {
        return func_002D8698(arg0, arg1, 0x17);
    }
    return 0;
}
