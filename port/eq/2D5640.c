#include "common.h"

u8 *func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5AC8(s32 arg0, u8 *arg1);

s32 func_002D5640(s32 arg0, s32 arg1, s32 *arg2) {
    s32 s0 = arg1 & 0xFF;
    u8 *s1;

    *arg2 = -1;
    s1 = func_002D5210(arg0, s0);
    if (s1 != NULL && func_002D5AC8(s0, s1) != 0) {
        *arg2 = *(u8 *)(s1 + 0x21);
        return 1;
    }
    return 0;
}
