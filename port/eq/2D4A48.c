#include "common.h"

s32 func_002D49B0(s32 arg0, s32 arg1);
s32 func_002D4D30(s32 arg0, s32 arg1, s32 arg2);

s32 func_002D4A48(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 buf[14];
    u8 *s0;
    s32 s3;
    s32 result;
    s32 a;
    s32 b;

    *arg1 = 0;
    *arg2 = 0;
    s0 = (u8 *)(*(s32 *)(arg0 + 4) + 0x20);
    result = func_002D49B0(arg0, (s32)buf);
    if (result != 0) {
        s3 = *(u8 *)(s0 + 0x19);
        s0 = (u8 *)(s32)*(u8 *)(s0 + 0x18);
        result = func_002D4D30((s32)buf, (s32)&buf[12], (s32)&buf[13]);
        if (result != 0) {
            if ((s32)s0 * 100 + s3 < buf[12] * 100 + buf[13]) {
                *arg1 = buf[12];
                *arg2 = buf[13];
            } else {
                *arg1 = (s32)s0;
                *arg2 = s3;
            }
            result = 1;
        }
    }
    return result;
}
