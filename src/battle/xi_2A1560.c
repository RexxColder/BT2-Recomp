#include "m2c_macros.h"

extern u8 gFontStyle __attribute__((section(".data")));

// Outputs the four clip halfwords of the font style block gFontStyle (+0x2C..+0x32) to arg0..arg3.
void Font_GetClip(s32 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    u8 *base;

    base = &gFontStyle;
    *arg0 = *(u16 *)(base + 0x2C);
    *arg1 = *(u16 *)(base + 0x2E);
    *arg2 = *(u16 *)(base + 0x30);
    *arg3 = *(u16 *)(base + 0x32);
}
