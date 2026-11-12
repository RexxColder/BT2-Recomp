#include "common.h"

s32 func_002CB250(s32 arg0, s32 arg1);

void func_002CB140(void *arg0, void **arg1, void **arg2) {
    u8 *base;
    u8 *s0;
    s32 s3;
    s32 s4;
    s32 t;

    s4 = 0;
    base = (u8 *)(*(s32 *)((u8 *)arg0 + 0x1FC0));
    *arg1 = (void *)0;
    s3 = *(s32 *)(base + 0x178);
    s0 = base + 0x180;
    *arg2 = (void *)0;
    if (s3 > 0) {
        do {
            t = *(s32 *)s0;
            if ((t == 2 || t == 4) && *(s32 *)(s0 + 0x58) == -1) {
                s4 += 1;
                if (func_002CB250((s32)*arg1, (s32)s0) != 0) {
                    *arg2 = *arg1;
                    *arg1 = s0;
                } else if (func_002CB250((s32)*arg2, (s32)s0) != 0) {
                    *arg2 = s0;
                }
            }
            s3 -= 1;
            s0 += 0xF0;
        } while (s3 != 0);
    }
    if (s4 <= 0) {
        *arg1 = (void *)0;
        *arg2 = (void *)0;
    } else if (s4 == 1) {
        *arg2 = (void *)0;
    }
}
