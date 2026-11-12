#include "common.h"

/* 0x0017ABD0 EftAura_Start(obj, src, flag): obj->flags = (src->+4 != 0) ? (old | 0x21) : (old | 0x11). When
 * (flag & 0xFF) != 0 the block is reset: +0x60, +0x30, +0x50, +0x8, +0x58, +0xC = 0 words, +0x2C = 1, and the
 * floats at +0x5C, +0x48, +0x54 = 1.0f. */
void EftAura_Start(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 old = *(s32 *)arg0;

    if (*(s32 *)(arg1 + 4) != 0) {
        *(s32 *)arg0 = old | 0x21;
    } else {
        *(s32 *)arg0 = old | 0x11;
    }
    if ((arg2 & 0xFF) != 0) {
        *(s32 *)(arg0 + 0x60) = 0;
        *(s32 *)(arg0 + 0x30) = 0;
        *(s32 *)(arg0 + 0x50) = 0;
        *(s32 *)(arg0 + 0x8) = 0;
        *(s32 *)(arg0 + 0x58) = 0;
        *(s32 *)(arg0 + 0xC) = 0;
        *(s32 *)(arg0 + 0x2C) = 1;
        *(f32 *)(arg0 + 0x5C) = 1.0f;
        *(f32 *)(arg0 + 0x48) = 1.0f;
        *(f32 *)(arg0 + 0x54) = 1.0f;
    }
}
