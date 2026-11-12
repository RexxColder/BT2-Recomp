#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5B08(s32 arg0);

s32 func_002D52D8(s32 arg0, s32 arg1, s32 *arg2) {
    s32 temp_s0;
    u8 *temp_s1;

    temp_s0 = arg1 & 0xFF;
    *arg2 = 0;
    temp_s1 = (u8 *) func_002D5210(arg0, temp_s0);
    if (temp_s1 == NULL) {
        return 0;
    }
    if (func_002D5B08(temp_s0) != 0xC0) {
        return 0;
    }
    if (temp_s1[0x19] != 1) {
        return 0;
    }
    *arg2 = temp_s1[0x1A];
    return 1;
}
