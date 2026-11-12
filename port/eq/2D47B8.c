#include "common.h"

s32 func_002D5210(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D5A88(s32 arg0, s32 arg1);
s32 func_002D5AC8(s32 arg0, s32 arg1);
s32 func_002D5B08(s32 arg0);

s32 func_002D47B8(s32 arg0, s32 arg1, s32 *arg2) {
    s32 s0;
    s32 t;
    s32 v0;
    s32 res;

    v0 = 0;
    s0 = arg1 & 0xFF;
    if (*(s32 *)(arg0 + 0xC) < 0x6E) {
        return v0;
    }
    t = func_002D5B08(s0);
    if (t == 0xC0) {
        v0 = func_002D5210(arg0, s0, 0xE0);
        if (v0 == 0) {
            return v0;
        }
        res = func_002D5A88(s0, v0);
        *arg2 = res;
        return 1;
    }
    if (t == 0xE0) {
        v0 = func_002D5210(arg0, s0, 0xE0);
        if (v0 == 0) {
            return v0;
        }
        res = func_002D5AC8(s0, v0);
        *arg2 = res;
        return 1;
    }
    return 0;
}
