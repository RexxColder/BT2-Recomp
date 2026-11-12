#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define LDF(p, off) (*(f32 *)((u8 *)(p) + (off)))

s32 func_002D7B70(void);

/* 0x002D7938: converts 256 words from arg1 to arg2. When func_002D7B70 returns 1 each word is masked
 * (0x7FFFFF80) and doubled. Otherwise a zero word becomes 1 (written back to arg1), then the word is read as
 * a float scaled by the float at arg0+0x40 (a negative word is halved with its low bit kept, then doubled),
 * divided into 2147483520, inverted into 16777215 and converted to an unsigned integer. */
void func_002D7938(s32 arg0, s32 arg1, s32 arg2) {
    u8 *p;
    u8 *in;
    u8 *out;
    f32 scale;
    f32 g;
    f32 f;
    s32 i;
    s32 x;
    s32 v;

    p = (u8 *)(s32)arg0;
    in = (u8 *)(s32)arg1;
    out = (u8 *)(s32)arg2;
    scale = LDF(p, 0x40);

    if (func_002D7B70() == 1) {
        for (i = 0; i < 256; i++) {
            LD32(out, i * 4) = (s32)(((u32)LD32(in, i * 4) & 0x7FFFFF80u) << 1);
        }
        return;
    }

    for (i = 0; i < 256; i++) {
        x = LD32(in, i * 4);
        if (x == 0) {
            LD32(in, i * 4) = 1;
            x = 1;
        }
        if (x < 0) {
            g = (f32)(s32)(((u32)x >> 1) | (u32)(x & 1));
            g = g + g;
            g = scale * g;
        } else {
            g = scale * (f32)x;
        }
        f = g / 2147483520.0f;
        f = 16777215.0f / f;
        if (f >= 2147483648.0f) {
            v = (s32)((u32)(s32)(f - 2147483648.0f) | 0x80000000u);
        } else {
            v = (s32)f;
        }
        LD32(out, i * 4) = v;
    }
}
