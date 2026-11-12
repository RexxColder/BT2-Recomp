#include "common.h"

s32 func_002FE8A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002FEA28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_002F3568(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_s0;

    var_s0 = 0;
    if (arg0 != 0) {
        var_s0 = func_002FEA28(arg1, arg2, *(s32 *)((u8 *)arg0 + 8), *(s32 *)((u8 *)arg0 + 0xC), *(s32 *)((u8 *)arg0 + 4));
    } else {
        func_002FE8A8(arg0, 0, 0, 0);
    }
    return var_s0;
}
