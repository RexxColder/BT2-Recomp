#include "common.h"

u8 *func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5B08(s32 arg0);

s32 func_002D5358(s32 arg0, s32 arg1, s32 *arg2) {
    s32 temp_s0;
    u8 *temp_s1;
    s32 var_v0;

    temp_s0 = arg1 & 0xFF;
    *arg2 = 0;
    temp_s1 = func_002D5210(arg0, temp_s0);
    var_v0 = 0;
    if (temp_s1 != NULL) {
        if (func_002D5B08(temp_s0) == 0xC0) {
            var_v0 = 1;
            *arg2 = temp_s1[0x1B];
        }
    }
    return var_v0;
}
