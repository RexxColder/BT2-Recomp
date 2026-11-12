#include "common.h"

s32 func_001E7178(s32 arg0);

s32 func_001A5B18(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if ((*(s32 *)((u8 *)arg0 + 0x1C) != 0) && (*(s32 *)((u8 *)arg0 + 0x20) != 0)) {
        var_v0 = func_001E7178((s32)((u8 *)arg0 + 0x18));
    }
    return var_v0;
}
