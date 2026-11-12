#include "common.h"

/* 0x001C4F00 EftRibbon_SetTexPair (BT3 exact name): slot record at arg0 + slot * 32 gets the 16-byte table entry
 * image (arg3) at +0xC8 and entry palette (arg4) at +0xD8; arg0->0x40 = palette. tex table = arg2, 16-byte entries. */
void EftRibbon_SetTexPair(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4) {
    u8 *dst = arg0 + arg1 * 32;
    u8 *img = arg2 + arg3 * 16;
    u8 *pal = arg2 + arg4 * 16;
    s32 k;

    for (k = 0; k < 16; k++) {
        dst[0xC8 + k] = img[k];
        dst[0xD8 + k] = pal[k];
    }
    *(s32 *)(arg0 + 0x40) = arg4;
}
