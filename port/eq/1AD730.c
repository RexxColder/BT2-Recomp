#include "common.h"

void func_001F0418(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7,
                   s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, s32 arg10);
extern f32 D_00384F20;

void func_001AD730(void *arg0) {
    u8 *s1;
    u8 *s0;
    s32 s2;
    f32 f0;
    f32 f1;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 g;
    f32 f22;
    s32 rr;
    s32 t3;

    s1 = *(u8 **)((u8 *)arg0 + 0x38);
    s0 = s1 + 0x120;
    if (*(s32 *)(s1 + 0xC0) & 0x800) {
        f22 = D_00384F20;
        s2 = 4;
        do {
            f1 = *(f32 *)(s0 + 0x1C);
            f12 = *(f32 *)(s0 + 0x00);
            f13 = *(f32 *)(s0 + 0x04);
            f14 = *(f32 *)(s0 + 0x08);
            f0 = *(f32 *)(s1 + 0xD0) * f22 * 4096.0f * f1;
            s0 += 0x20;
            if (f0 < 2147483648.0f) {
                /* cvt.w.s: truncates toward zero */
                rr = (s32)f0;
                t3 = rr;
            } else {
                g = f0 - 2147483648.0f;
                /* cvt.w.s: truncates toward zero */
                rr = (s32)g;
                t3 = rr | (s32)0x80000000;
            }
            s2 -= 1;
            func_001F0418(f12, f13, f14, 0.0f, 0.0f, 1.0f, 1.0f, *(f32 *)(s1 + 0xD8),
                          0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0, t3,
                          0, 0, *(s32 *)(s1 + 0x1C0));
        } while (s2 >= 0);
    }
}
