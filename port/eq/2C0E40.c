#include "common.h"

s32 func_002C0E40(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 0;
    if (arg1 != 8) {
        var_v0 = *(s32 *)((u8 *)arg0 + arg1 * 0x74 + 0x1318);
    }
    return var_v0;
}
