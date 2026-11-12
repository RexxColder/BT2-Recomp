#include "common.h"

void *memset(void *, s32, u32);
void func_003061A8(void *arg0, s32 arg1, void *arg2, void *arg3);

s32 func_002F6BE8(u8 *arg0, s32 arg1, s32 arg2) {
    s32 buf[8];
    s32 *sp = buf;
    s32 *sp10 = &buf[4];
    s32 s0;
    s32 s1;
    s32 s3;
    s32 s5;
    s32 s5b;
    void **s4;
    u8 *vt;
    s32 result = 0;

    s0 = arg1 * 0x12;
    s4 = *(void ***)(arg0 + 0x14);
    if (s4 != NULL) {
        s3 = ((s32)((arg2 < 0) ? (arg2 + 0x1F) : arg2) >> 5) * s0;
        vt = *(u8 **)s4;
        (*(void (**)(void *, s32, s32, void *))(vt + 0x18))(s4, 0, s3, sp);
        s5 = (buf[1] / s0) * s0;
        memset((void *)buf[0], 0, s5);
        s1 = s5;
        func_003061A8(sp, s1, sp, sp10);
        vt = *(u8 **)s4;
        (*(void (**)(void *, s32, void *))(vt + 0x20))(s4, 1, sp);
        (*(void (**)(void *, s32, void *))(vt + 0x1C))(s4, 0, sp10);
        vt = *(u8 **)s4;
        (*(void (**)(void *, s32, s32, void *))(vt + 0x18))(s4, 0, s3 - s1, sp);
        s5b = (buf[1] / s0) * s0;
        memset((void *)buf[0], 0, s5b);
        s1 = s1 + s5b;
        func_003061A8(sp, s5b, sp, sp10);
        vt = *(u8 **)s4;
        (*(void (**)(void *, s32, void *))(vt + 0x20))(s4, 1, sp);
        (*(void (**)(void *, s32, void *))(vt + 0x1C))(s4, 0, sp10);
        result = ((s1 / s0)) << 5;
    }
    return result;
}
