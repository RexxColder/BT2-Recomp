#include "common.h"

s32 func_002C0EA8(s32 arg0, s32 arg1) {
    s32 var_v0;

    var_v0 = 1;
    if (arg1 != 8) {
        var_v0 = *(s32 *)((u8 *)arg0 + arg1 * 0x74 + 0x131C);
    }
    return var_v0;
}
