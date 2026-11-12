#include "m2c_macros.h"

s32 func_002FE000(s8);                              /* extern */

s32 func_002FE038(s8 arg0, s8 arg1) {
    s32 temp_s0;

    temp_s0 = func_002FE000(arg0);
    return ((temp_s0 ^ func_002FE000(arg1)) != 0) ? -1 : 0;
}
