#include "common.h"

s32 strcmp(void *a, void *b);

void func_00270438(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *s3;
    u8 *s0;
    s32 s2;
    u32 s4;
    u32 count;

    s3 = *(u8 **)arg0 + *(s32 *)arg1 * 0xC0;
    *(s32 *)(s3 + 0x64) = *(s32 *)(arg2 + 0x0);
    *(s32 *)(s3 + 0x68) = *(s32 *)(arg2 + 0x4);
    *(s32 *)(s3 + 0x6C) = *(s32 *)(arg2 + 0x8);
    *(s32 *)(s3 + 0x48) = *(s32 *)(s3 + 0x48) | 4;
    *(s32 *)(s3 + 0x70) = *(s32 *)(arg2 + 0xC);

    s2 = *(s32 *)(arg1 + 0x4);
    s4 = 1;
    if (s2 == 0) {
        return;
    }
    count = (u32)(*(s32 *)(arg0 + 0x4) - *(s32 *)arg1);
    if (!(1U < count)) {
        return;
    }

    s0 = s3 + 0xC0;
    for (;;) {
        if (strcmp(s0, s3) == 0) {
            s2 -= 1;
            *(s32 *)(s0 + 0x64) = *(s32 *)(arg2 + 0x0);
            *(s32 *)(s0 + 0x68) = *(s32 *)(arg2 + 0x4);
            *(s32 *)(s0 + 0x6C) = *(s32 *)(arg2 + 0x8);
            *(s32 *)(s0 + 0x48) = *(s32 *)(s0 + 0x48) | 4;
            *(s32 *)(s0 + 0x70) = *(s32 *)(arg2 + 0xC);
            if (s2 == 0) {
                return;
            }
        }
        s4 += 1;
        if (!(s4 < count)) {
            return;
        }
        s0 += 0xC0;
    }
}
