#include "common.h"

s32 strcmp(s32 arg0, s32 arg1);

void func_00270D00(u8 *arg0, u8 *arg1) {
    s32 i;
    s32 s1;
    s32 s2;
    u8 *s3;
    u8 *s0;

    i = *(s32 *)arg1;
    s1 = *(s32 *)(arg1 + 4);
    s3 = *(u8 **)arg0 + i * 0xC0;
    *(u8 *)(s3 + 0xB9) = (*(u8 *)(s3 + 0xB9) & 0xFD) | 1;
    s2 = 1;
    if (s1 != 0) {
        if ((u32)(*(s32 *)(arg0 + 4) - i) > 1U) {
            s0 = s3 + 0xC0;
            for (;;) {
                if (strcmp((s32)s0, (s32)s3) == 0) {
                    s1 -= 1;
                    *(u8 *)(s0 + 0xB9) = (*(u8 *)(s0 + 0xB9) & 0xFD) | 1;
                    if (s1 == 0) {
                        break;
                    }
                }
                s2 += 1;
                s0 += 0xC0;
                if (!((u32)s2 < (u32)(*(s32 *)(arg0 + 4) - i))) {
                    break;
                }
            }
        }
    }
}
