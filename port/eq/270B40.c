#include "common.h"

s32 strcmp(void *arg0, void *arg1);

void func_00270B40(s32 arg0, s32 arg1, s32 arg2) {
    u8 *s6;
    u8 *s4;
    u8 *s0;
    u8 *s2;
    s32 s1;
    u32 s3;

    s6 = (u8 *)arg0;
    s4 = (u8 *)arg1;
    s0 = (u8 *)(*(s32 *)s6 + *(s32 *)s4 * 0xC0);
    *(s32 *)(s0 + 0x48) = *(s32 *)(s0 + 0x48) | arg2;
    s1 = *(s32 *)(s4 + 4);
    s3 = 1;
    if (s1 != 0) {
        s2 = s0 + 0xC0;
        for (;;) {
            u32 cnt = (u32)(*(s32 *)(s6 + 4) - *(s32 *)s4);
            u32 cond = s3 < cnt;
            s3 += 1;
            if (!cond) {
                break;
            }
            if (strcmp((void *)s2, (void *)s0) != 0) {
                s2 += 0xC0;
                continue;
            }
            s2 += 0xC0;
            *(s32 *)(s0 + 0x48) = *(s32 *)(s0 + 0x48) | arg2;
            s1 -= 1;
            if (s1 == 0) {
                break;
            }
        }
    }
}
