#include "common.h"

/* Expands an 8-bit indexed image into 32-bit pixels through a 256-entry palette, in 16x16 blocks.
 * *src_pp = 8-bit source (read with stride 4 inside a block row: only every 4th byte is used, 64 bytes per row),
 * img+4 = destination u32 pixels, img+8 = destination row stride in pixels, img+0x10/0x14 = width/height. */
void func_002D8DE8(u8 **src_pp, u8 *img, u8 *pal)
{
    s32 w = *(s32 *)(img + 0x10);
    s32 h = *(s32 *)(img + 0x14);
    s32 bw = (w < 0 ? w + 15 : w) >> 4;
    s32 bh = (h < 0 ? h + 15 : h) >> 4;
    u8 *src = *src_pp;
    u32 *dst = *(u32 **)(img + 4);
    s32 bx;
    s32 by;
    s32 r;
    s32 k;

    if (bw <= 0) {
        return;
    }
    for (bx = bw; bx != 0; bx--) {
        u32 *row = dst;
        src += 1024 * bh;
        if (bh > 0) {
            by = bh;
            do {
                by--;
                for (r = 0; r < 16; r++) {
                    for (k = 0; k < 16; k++) {
                        row[k] = *(u32 *)(pal + 4 * src[4 * k]);
                    }
                    src += 64;
                    row += *(s32 *)(img + 8);
                }
            } while (by != 0);
        }
        dst += 16;
    }
}
