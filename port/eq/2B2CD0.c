#include "m2c_macros.h"

s32 func_002B2CD0(s32 unused, u8 *arg1) {
    s32 var_a0 = 0;

    if (arg1[0] == 0 && arg1[1] == 0 && arg1[2] == 1) {
        var_a0 = ((arg1[3] + 0x47) & 0xFF) < 2;
    }
    return var_a0;
}
