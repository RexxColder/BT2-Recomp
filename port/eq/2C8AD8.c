#include "common.h"

s32 func_002C8AD8(s32 arg0, u32 arg1) {
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = arg0 + 0xA0C;
    if (arg1 == 2) {
        var_v0 = *(s32 *)(temp_a0 + 0xC);
    } else if (arg1 < 3U) {
        if (arg1 != 1) {
            return 1;
        }
        var_v0 = *(s32 *)(temp_a0 + 0x8);
    } else {
        if (arg1 != 3) {
            return 1;
        }
        var_v0 = *(s32 *)(temp_a0 + 0x10);
    }
    return var_v0 == 0;
}
