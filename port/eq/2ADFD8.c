#include "common.h"

s32 func_002ADFD8(u8 **arg0) {
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = *(s32 *)(*arg0 + 4);
    var_v0 = 0;
    if ((temp_a0 == 0x58) || (temp_a0 == 0x71)) {
        var_v0 = 1;
    }
    return var_v0;
}
