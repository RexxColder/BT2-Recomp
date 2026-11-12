#include "common.h"

s32 func_002D45E8(s32 arg0);

s32 func_002D4F58(s32 arg0, s32 *arg1) {
    u8 *temp_s1;
    s32 var_v0;

    *arg1 = 0;
    temp_s1 = (u8 *)(*(s32 *)((u8 *)arg0 + 4)) + 0xB0;
    var_v0 = func_002D45E8(arg0);
    if (var_v0 != 0) {
        var_v0 = 0;
        if (*(s32 *)((u8 *)arg0 + 0xC) >= 0x6E) {
            var_v0 = 1;
            *arg1 = *(s32 *)(temp_s1 + 4);
        }
    }
    return var_v0;
}
