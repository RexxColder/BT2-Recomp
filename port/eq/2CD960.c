#include "common.h"

s32 func_002C0EA8(s32 arg0, s32 arg1);
s32 func_002D07B0(s32 arg0, s32 arg1);
s32 func_002D3060(s32 arg0, s32 arg1);

s32 func_002CD960(s32 arg0) {
    s32 s0;
    s32 a1;

    if (func_002D07B0(arg0, 5) != 0) {
        if (func_002D3060(arg0, 6) != 0) {
            return 1;
        }
    }
    if (func_002D07B0(arg0, 6) != 0) {
        if (func_002D3060(arg0, 7) != 0) {
            return 1;
        }
    }
    s0 = 0;
    a1 = 0;
    do {
        s0 += 1;
        if (func_002C0EA8(arg0, a1) != 0) {
            return 1;
        }
        a1 = s0;
    } while (s0 < 8);
    return 0;
}
