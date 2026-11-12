#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5AC8(s32 arg0, s32 arg1);

s32 func_002D5878(s32 arg0, s32 arg1, s32 *arg2) {
    s32 temp_s0;
    s32 temp_s1;
    u8 temp_v0;

    temp_s0 = arg1 & 0xFF;
    *arg2 = -1;
    temp_s1 = func_002D5210(arg0, temp_s0);
    if (temp_s1 == 0) {
        return 0;
    }
    if (func_002D5AC8(temp_s0, temp_s1) == 0) {
        return 0;
    }
    temp_v0 = *(u8 *) (temp_s1 + 0x25);
    *arg2 = (s32) temp_v0;
    if ((s32) temp_v0 >= 0x40) {
        *arg2 = -1;
    }
    return 1;
}
