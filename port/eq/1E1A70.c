#include "common.h"

f32 floorf(f32 farg0);
void func_001E1BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);

/* 0x001E1A70: sibling of 0x001E0B38 (same per-entry step, entries from the block base, count at
 * +0x1A0, frame time at +0x21C4, second float at +0x21C8). Each entry's value at +0x70 is scaled by
 * arg1 / the time, offset by 0.5, floored and passed to func_001E1BC8 with a float from +0x88.
 * Then the frame value is stored at +0x21C4, the byte at +0x21D9 is cleared and the word at +0x21C8
 * is zeroed. */
void func_001E1A70(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    u8 *s0;
    s32 count = *(s32 *)(s1 + 0x1A0);
    s32 s2 = 0;
    f32 f21 = (f32)arg1;
    f32 sb[8];

    if (count > 0) {
        s0 = s1;
        do {
            f32 f12 = *(f32 *)(s0 + 0x70) / *(f32 *)(s1 + 0x21C4);
            f32 fl;
            f32 f20;

            sb[0] = *(f32 *)(s0 + 0x140);
            sb[1] = *(f32 *)(s0 + 0x144);
            sb[2] = *(f32 *)(s0 + 0x148);
            sb[3] = *(f32 *)(s0 + 0x14C);
            sb[4] = *(f32 *)(s0 + 0xE0);
            sb[5] = *(f32 *)(s0 + 0xE4);
            sb[6] = *(f32 *)(s0 + 0xE8);
            sb[7] = 0.0f;

            f12 = f21 * f12;
            f12 = f12 + 0.5f;
            f20 = *(f32 *)(s0 + 0x88);
            fl = floorf(f12);

            func_001E1BC8((s32)s0, (s32)*(f32 *)(s1 + 0x21C8), (s32)fl, (s32)(&sb[4]), (s32)sb, f20);
            *(u8 *)(s0 + 0x19C) = 0;

            s2++;
            count = *(s32 *)(s1 + 0x1A0);
            s0 += 0x1B0;
        } while (s2 < count);
        *(f32 *)(s1 + 0x21C4) = f21;
    } else {
        *(f32 *)(s1 + 0x21C4) = f21;
    }
    *(u8 *)(s1 + 0x21D9) = 0;
    *(s32 *)(s1 + 0x21C8) = 0;
}
