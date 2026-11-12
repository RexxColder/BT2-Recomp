#include "common.h"

f32 floorf(f32 farg0);
void func_001E1BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0);

/* 0x001E0B38: steps the emitter block arg0 for arg1 frames. For each of the entries at arg0+0x10
 * (stride 0x1B0, count at +0x1B0) it scales a value at +0x70 by arg1 / the time at +0x21D4, adds
 * 0.5, floors it (the result is passed to func_001E1BC8 with a float from +0x88 and a scratch
 * block of eight words), and clears the entry's flag at +0x19C. The frame value (as a float)
 * is stored at +0x21D4 and the counter at +0x21D0 is cleared. */
void func_001E0B38(u8 *arg0, s32 arg1) {
    u8 *s1 = arg0;
    u8 *s0;
    s32 count = *(s32 *)(s1 + 0x1B0);
    s32 s2 = 0;
    f32 f21 = (f32)arg1;
    f32 sb[8];

    if (count > 0) {
        s0 = s1 + 0x10;
        do {
            f32 f12 = *(f32 *)(s0 + 0x70) / *(f32 *)(s1 + 0x21D4);
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

            func_001E1BC8((s32)s0, (s32)*(f32 *)(s1 + 0x21D0), (s32)fl, (s32)(&sb[4]), (s32)sb, f20);
            *(u8 *)(s0 + 0x19C) = 0;

            s2++;
            count = *(s32 *)(s1 + 0x1B0);
            s0 += 0x1B0;
        } while (s2 < count);
        *(f32 *)(s1 + 0x21D4) = f21;
    } else {
        *(f32 *)(s1 + 0x21D4) = f21;
    }
    *(s32 *)(s1 + 0x21D0) = 0;
}
