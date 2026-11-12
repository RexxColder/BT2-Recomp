#include "common.h"

s32 func_002B9858(s32 arg0, s32 arg1);
s32 func_002B98C8(s32 arg0);
s32 func_002B9938(s32 arg0);

void func_002B97E0(s32 arg0, s32 arg1) {
    s32 *dst = (s32 *)(arg1 + 0x60);
    s32 *src = (s32 *)(arg0 + 0x88);

    dst[0] = func_002B9858(arg0, arg1);
    dst[1] = func_002B98C8(arg0);
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = func_002B9938(src[5]);
    dst[6] = func_002B9938(src[6]);
}
