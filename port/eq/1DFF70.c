#include "common.h"

void func_001E18F0(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);

void func_001DFF70(u8 *arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1, f32 fparg2) {
    u8 *s1 = arg0;
    u8 *s0;
    s32 s2;
    s32 s3;
    s32 s4 = arg2 & 0xFF;
    s32 s5 = arg1;
    f32 f12;
    f32 f13;

    if (*(u8 *)(s1 + 0x21DA) != 0) {
        s3 = 0;
        if (*(u8 *)(s1 + 0x21CC) != 0) {
            s0 = s1 + 0x34;
            s2 = 0;
            f12 = *(f32 *)(s0 - 4);
            do {
                f13 = *(f32 *)s0;
                *(f32 *)(s0 + 0x20) = fparg2;
                s0 += 0x1B0;
                s3 += 1;
                s2 += 0x1B0;
                func_001E18F0((s32)(s1 + s2 - 0x1B0), s5, s4, f12 * fparg0, f13 * fparg1, *(f32 *)(s1 + 0x21D0));
                if (s3 >= *(u8 *)(s1 + 0x21CC)) {
                    break;
                }
                f12 = *(f32 *)(s0 - 4);
            } while (1);
        }
    }
}
