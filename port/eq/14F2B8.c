#include "common.h"

s32 func_0014F2B8(s32 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 temp_v0;
    s32 var_a0;
    u8 *p;

    temp_v0 = *((u8 *)arg1 + arg3 + arg2 * 8);
    var_a0 = 0;
    if ((temp_v0 & 2) && !(temp_v0 & 4)) {
        var_a0 = 0x18;
        if (arg2 != 2) {
            p = (u8 *)(*arg0 + (arg3 << 5) + arg2 * 0x110);
            var_a0 = ((p[0x10] ^ 2) != 0) ? 0 : 0x18;
        }
    }
    return var_a0;
}
