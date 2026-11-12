#include "m2c_macros.h"

s32 BtlText_IsNewline(s32 arg0) {
    s32 temp_a0;
    s32 var_v1;

    temp_a0 = arg0 & 0xFFFF;
    var_v1 = 0;
    if ((temp_a0 == 0xA) || (temp_a0 == 0xD)) {
        var_v1 = 1;
    }
    return var_v1;
}
