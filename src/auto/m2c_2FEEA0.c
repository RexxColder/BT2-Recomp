#include "m2c_macros.h"

s32 func_002FEE88(s8);                              /* extern */

s32 func_002FEEA0(s8 arg0, s8 arg1) {
    s32 temp_s0;

    temp_s0 = func_002FEE88(arg0);
    return ((temp_s0 ^ func_002FEE88(arg1)) != 0) ? -1 : 0;
}
