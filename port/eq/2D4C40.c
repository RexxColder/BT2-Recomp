#include "common.h"

s32 func_002D45E8(s32 arg0);

s32 func_002D4C40(s32 arg0, s32 *arg1) {
    s32 var_v0;
    s32 temp_s0;

    *arg1 = -1;
    temp_s0 = *(s32 *)(arg0 + 4) + 0x80;
    var_v0 = func_002D45E8(arg0);
    if (var_v0 != 0) {
        var_v0 = 1;
        *arg1 = *(u8 *)(temp_s0 + 4);
    }
    return var_v0;
}
