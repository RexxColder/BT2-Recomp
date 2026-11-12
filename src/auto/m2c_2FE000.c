#include "m2c_macros.h"

s32  func_002FE000(s8 arg0) {
    s8 temp_v1;
    s8 var_a0;

    var_a0 = arg0;
    temp_v1 = var_a0;
    if ((u32) (var_a0 - 0x61) < 0x1AU) {
        var_a0 -= 0x20;
    }
    return (s8)(((temp_v1 ^ 0x5C) != 0) ? var_a0 : 0x2F);
}
