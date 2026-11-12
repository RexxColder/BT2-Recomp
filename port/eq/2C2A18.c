#include "common.h"

s32 func_002D4748(s32 arg0, s32 arg1, s32 *arg2);

s32 func_002C2A18(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 s0 = arg1;

    if (arg2 < s0) {
        return 0;
    }
    for (;;) {
        if (func_002D4748(arg0, s0 & 0xFF, sp) != 0 && sp[0] != 0) {
            return s0;
        }
        s0 += 1;
        if (arg2 < s0) {
            return 0;
        }
    }
}
