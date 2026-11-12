#include "common.h"

void func_002DC6E8(s32 arg0, void *arg1, s32 arg2);

void func_002C4DB8(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 sp[8];
    u8 *s3;
    s32 s4;
    s32 s0;
    s32 s1;
    s32 s2;

    s0 = 0;
    s1 = 0;
    s2 = 0;
    s3 = *(u8 **)(arg0 + 0x1F7C);
    s4 = *(s32 *)s3;
    do {
        func_002DC6E8(s4, sp, s0);
        s0 += 1;
        s2 = (sp[2] >= s2) ? sp[2] : s2;
        s1 = (sp[3] >= s1) ? sp[3] : s1;
    } while (s0 < 3);
    *(s32 *)(s3 + 4) = s1;
    *(s32 *)(s3 + 8) = s2;
    *arg1 = s2;
    *arg2 = *(s32 *)(s3 + 4);
}
