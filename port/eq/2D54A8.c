#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1);
s32 func_002D5B08(s32 arg0);

s32 func_002D54A8(s32 arg0, s32 arg1, s32 *arg2) {
    s32 s0 = arg1 & 0xFF;
    u8 *s1;
    u16 v1;

    *arg2 = 0;
    s1 = (u8 *)func_002D5210(arg0, s0);
    if (s1 == NULL) {
        return 0;
    }
    if (func_002D5B08(s0) != 0xE0) {
        return 0;
    }
    v1 = *(u16 *)(s1 + 0x1A);
    if (v1 == 0xFFFF) {
        *arg2 = 0;
    } else {
        *arg2 = v1;
    }
    return 1;
}
