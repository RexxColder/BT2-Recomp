#include "common.h"

f32 func_00123140(void *a0, void *a1);

void func_00124448(void *arg0) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s4;
    s32 s3;

    s4 = (u8 *)arg0 + 0xBE0;
    if (*(s32 *)((u8 *)arg0 + 0xBE4) > 0) {
        s3 = 1;
        if (*(s32 *)(s4 + 4) > 1) {
            s0 = (u8 *)arg0 + 0xFA1;
            s2 = (u8 *)arg0 + 0xEC4;
            s1 = (u8 *)arg0 + 0xBF0;
            do {
                if (*s0 & 8) {
                    *(f32 *)s2 = func_00123140(s1 + 0x20, s1 + 0x10);
                    *s0 &= ~8;
                }
                s3 += 1;
                s2 += 4;
                s1 += 0x10;
                s0 += 1;
            } while (s3 < *(s32 *)(s4 + 4));
        }
    }
}
