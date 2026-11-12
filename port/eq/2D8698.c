#include "common.h"

s32 func_002D86F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s64 func_002D8698(u8 *arg0, s32 arg1, s32 arg2) {
    u8 buf[4];
    s32 out[4];
    u8 *p;
    s32 r;

    if (arg0 == NULL || arg1 < 0) {
        return 0;
    }
    p = arg0 + arg2;
    buf[0] = p[0];
    buf[1] = p[1];
    buf[2] = p[2];
    r = func_002D86F8((s32)buf, (s32)out, 0x10, (s8)p[1]);
    return (s64)r;
}
