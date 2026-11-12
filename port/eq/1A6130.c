#include "common.h"

extern s32 D_0036EA30[4] __attribute__((section(".data")));

void func_001A6130(u8 *dst, u8 *src) {
    s32 state;
    s32 sel;
    s32 pair;
    s32 triple;
    s32 k;
    s32 vofs;
    f32 *out;

    __builtin_memset(dst, 0, 0x354);
    out = (f32 *)(dst + 0x130);
    pair = 0;
    triple = 0;
    sel = 0;

    *(f32 *)(dst + 0x1CC) = *(f32 *)(src + 0x22C);
    *(f32 *)(dst + 0x1C8) = *(f32 *)(src + 0x228);
    dst[0x350] = src[0x400];
    *(f32 *)(dst + 0x2B4) = *(f32 *)(src + 0x344);

    state = 0;
    do {
        /* the four table entries are states that only advance */
        if (state == D_0036EA30[0] || state == D_0036EA30[1] ||
            state == D_0036EA30[2] || state == D_0036EA30[3]) {
            state++;
            continue;
        }

        vofs = 4 * (pair + sel);
        for (k = 0; k < 3; k++) {
            dst[triple + k] = src[triple + k];
            *(f32 *)(dst + vofs + 0x1D0 + 4 * k) = *(f32 *)(src + vofs + 0x230 + 4 * k);
            *(f32 *)(dst + vofs + 0x4C + 4 * k) = *(f32 *)(src + vofs + 0x5C + 4 * k);
            dst[4 + pair + sel + 0x300 + k] = src[4 + pair + sel + 0x3A0 + k];
        }

        dst[sel + 0x39] = src[sel + 0x45];
        *out = *(f32 *)(src + 0x170 + 4 * sel);
        out++;
        *(f32 *)(dst + 0x17C + 4 * sel) = *(f32 *)(src + 0x1CC + 4 * sel);
        *(f32 *)(dst + 0x2B8 + 4 * sel) = *(f32 *)(src + 0x348 + 4 * sel);
        dst[0x33D + sel] = src[0x3E9 + sel];

        triple += 3;
        pair += 2;
        sel += 1;
        state++;
    } while (state < 23);
}
