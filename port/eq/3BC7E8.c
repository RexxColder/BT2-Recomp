#include "common.h"

/* 0x003BC7E8: packs nine groups of 8-byte source records (from +0x20) into 27 bytes at dst.
   Group g: dst[3g]   = (src[b] << 2)   | ((u16 @b+2 >> 4) & 3)
            dst[3g+1] = (src[b+2] << 4) | ((u16 @b+4 >> 2) & 0xF)
            dst[3g+2] = (src[b+4] << 6) | (src[b+6] & 0x3F)     with b = 0x20 + 8g.
   Returns src[0x66] & 0x3F (the last byte-mask left in v0). */
s32 func_003BC7E8(u8 *dst, u8 *src) {
    s32 g;
    s32 b;
    s32 d;

    for (g = 0; g < 9; g++) {
        b = 0x20 + 8 * g;
        d = 3 * g;
        dst[d] = (u8)((src[b] << 2) | ((*(u16 *)(src + b + 2) >> 4) & 3));
        dst[d + 1] = (u8)((src[b + 2] << 4) | ((*(u16 *)(src + b + 4) >> 2) & 0xF));
        dst[d + 2] = (u8)((src[b + 4] << 6) | (src[b + 6] & 0x3F));
    }
    return src[0x66] & 0x3F;
}
