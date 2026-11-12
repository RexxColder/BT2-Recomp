#include "common.h"

/* Builds a 256-byte table: 16 zero bytes, then 220 entries cvt.w.s(0.5890...f * (i - 16)) (the byte
 * of the cvt.w.s (truncated) integer; the 2^31 branch is kept), then 0x80 up to the end. */
void func_002D5F50(void *arg0) {
    union { u32 u; f32 f; } bits;
    u8 *a0 = (u8 *)arg0;
    s32 i;
    f32 f0;
    f32 f2;
    f32 f1;
    s32 r;

    for (i = 0; i < 16; i++) {
        a0[i] = 0;
    }
    bits.u = 0x3F14FDF3u;
    f2 = bits.f;
    bits.u = 0x4F000000u;
    f1 = bits.f;
    for (i = 16; i < 0xEC; i++) {
        f0 = (f32)(i - 16) * f2;
        if (f1 <= f0) {
            f0 = f0 - f1;
            r = (s32)f0;
            r = (s32)((u32)r | 0x80000000u);
        } else {
            r = (s32)f0;
        }
        a0[i] = (u8)r;
    }
    for (i = 0xEC; i < 0x100; i++) {
        a0[i] = 0x80;
    }
}
