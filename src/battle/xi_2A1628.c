#include "m2c_macros.h"

extern u8 gFontStyle __attribute__((section(".data")));

// Outputs the shadow offset pair from the font style block gFontStyle: halfword +0x28 to *arg0, +0x2A to *arg1.
void Font_GetShadowOffset(s32 *arg0, s32 *arg1) {
    u8 *base;

    base = &gFontStyle;
    *arg0 = *(u16 *)(base + 0x28);
    *arg1 = *(u16 *)(base + 0x2A);
}
