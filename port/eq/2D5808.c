#include "common.h"

u8 *func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5AC8(s32 arg0, s32 arg1);

s32 func_002D5808(s32 arg0, s32 arg1, s32 *arg2) {
    s32 temp_s0;
    u8 *temp_s1;

    temp_s0 = arg1 & 0xFF;
    *arg2 = 0;
    temp_s1 = func_002D5210(arg0, temp_s0);
    if (temp_s1 == NULL) {
        return 0;
    }
    if (func_002D5AC8(temp_s0, (s32)temp_s1) == 0) {
        return 0;
    }
    *arg2 = temp_s1[0x24];
    return 1;
}
