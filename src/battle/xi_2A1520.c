#include "m2c_macros.h"

extern u8 gFontStyle __attribute__((section(".data")));

// Outputs two words of the font style block gFontStyle: +0x10 to *arg0, +0x14 to *arg1.
void func_002A1520(s32 *arg0, s32 *arg1) {
    u8 *base;

    base = &gFontStyle;
    *arg0 = *(s32 *)(base + 0x10);
    *arg1 = *(s32 *)(base + 0x14);
}
