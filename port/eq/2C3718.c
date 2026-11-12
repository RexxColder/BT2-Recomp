#include "common.h"

s32 func_002C0178(void *a0, s32 a1, void *a2, s32 a3);

s32 func_002C3718(void *arg0, void *arg1, void *arg2, s32 arg3, void *arg4) {
    s32 buf[4];
    s32 r;
    s32 a2v;
    s32 (*fp)(void *, s32, s32, s32);

    r = func_002C0178(arg0, *(s32 *)((u8 *)arg0 + 0x1F84), buf, arg3);
    if (r != 0) {
        return r;
    }
    *(s32 *)arg2 = buf[1];
    *(s32 *)arg4 = buf[1] + buf[3];
    *(s32 *)arg1 = buf[0];
    a2v = *(s32 *)arg2;
    if (a2v < 0x800) {
        return 0;
    }
    if (*(s32 *)((u8 *)arg0 + 0x37AC) == buf[0]) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x37A8) & 0x7FF) != 0) {
        return 0;
    }
    fp = *(void **)((u8 *)arg0 + 0x37A0);
    if (fp != NULL) {
        fp(*(void **)((u8 *)arg0 + 0x37A4), buf[0], buf[1], arg3);
    }
    *(s32 *)((u8 *)arg0 + 0x37AC) = *(s32 *)arg1;
    return 0;
}
