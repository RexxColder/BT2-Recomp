#include "common.h"

s32 strcmp(void *a, void *b);

void func_00270A10(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    u8 *s2;
    u8 *s0;
    s32 s7;
    s32 s1;
    u32 s3;
    s32 v;

    s7 = arg3 & 0xFF;
    s2 = *(u8 **)arg0 + *(s32 *)arg1 * 0xC0;
    if (s7 != 0) {
        v = *(s32 *)(s2 + 0x44) | arg2;
    } else {
        v = *(s32 *)(s2 + 0x44) & ~arg2;
    }
    *(s32 *)(s2 + 0x44) = v;

    s1 = *(s32 *)(arg1 + 0x4);
    s3 = 1;
    if (s1 == 0) {
        return;
    }
    if (!(1U < (u32)(*(s32 *)(arg0 + 0x4) - *(s32 *)arg1))) {
        return;
    }

    s0 = s2 + 0xC0;
    for (;;) {
        if (strcmp(s0, s2) == 0) {
            if (s7 != 0) {
                v = *(s32 *)(s0 + 0x44) | arg2;
            } else {
                v = *(s32 *)(s0 + 0x44) & ~arg2;
            }
            s1 -= 1;
            *(s32 *)(s0 + 0x44) = v;
            if (s1 == 0) {
                return;
            }
        }
        s3 += 1;
        if (!(s3 < (u32)(*(s32 *)(arg0 + 0x4) - *(s32 *)arg1))) {
            return;
        }
        s0 += 0xC0;
    }
}
