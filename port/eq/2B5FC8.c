#include "common.h"

s32 func_002D4748(s32 arg0, s32 arg1, s32 *arg2);
s32 func_002D5640(s32 arg0, s32 arg1, s32 *arg2);

s32 func_002B5FC8(s32 arg0) {
    s32 buf[2];
    s32 r;
    s32 r2;

    r = func_002D4748(arg0, 0xE0, buf);
    if (r != 1 || buf[0] != 1) {
        return 0;
    }
    r2 = func_002D5640(arg0, 0xE0, &buf[1]);
    if (r2 != 1) {
        return 0;
    }
    return buf[1] == 3;
}
