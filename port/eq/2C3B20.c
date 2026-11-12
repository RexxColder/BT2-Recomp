#include "common.h"

s32 func_002D07B0(s32 arg0, s32 arg1, s64 arg2);

void func_002C3B20(s32 arg0, s32 arg1, s64 arg2) {
    s64 buf[3];
    s32 fnp;
    s32 x;

    fnp = func_002D07B0(arg0, 0x5B, arg2);
    if (fnp != 0) {
        ((u8 *)buf)[0] = (u8)(arg1 & 0xFF);
        buf[1] = arg2;
        buf[2] = *(s64 *)(arg0 + 0x990);
        x = func_002D07B0(arg0, 0x5C, arg2);
        ((void (*)(s32, void *))fnp)(x, (void *)buf);
    }
}
