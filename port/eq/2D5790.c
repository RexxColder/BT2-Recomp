#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5AC8(s32 arg0, s32 arg1);

s32 func_002D5790(s32 arg0, s32 arg1, s32 *arg2) {
    s32 s0 = arg1 & 0xFF;
    u8 *s1;
    s32 ret;

    *arg2 = 0;
    s1 = (u8 *)func_002D5210(arg0, s0);
    if (s1 == NULL) {
        return 0;
    }
    ret = func_002D5AC8(s0, (s32)s1);
    if (ret == 0) {
        return 0;
    }
    *arg2 = (s1[0x23] & 0x10) != 0;
    return 1;
}
