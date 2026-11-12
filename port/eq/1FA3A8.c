#include "common.h"

extern u8 *D_00387930;

s32 func_001FA3A8(s32 arg0) {
    s32 var_v0;
    u8 *base;

    var_v0 = 0;
    if (arg0 < 0x1B1) {
        base = *(u8 **)(D_00387930 + 0x14);
        var_v0 = *(s32 *)(base + arg0 * 4);
    }
    return var_v0;
}
