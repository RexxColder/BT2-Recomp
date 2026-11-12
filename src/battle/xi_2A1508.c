#include "m2c_macros.h"

extern u8 gFontStyle __attribute__((section(".data")));

// Stores arg0 at +0x10 and arg1 at +0x14 of the font style block gFontStyle.
void func_002A1508(s32 arg0, s32 arg1) {
    u8 *base;

    base = &gFontStyle;
    *(s32 *)(base + 0x10) = arg0;
    *(s32 *)(base + 0x14) = arg1;
}
