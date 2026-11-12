#include "m2c_macros.h"

extern u8 gFontStyle __attribute__((section(".data")));

// Stores the shadow offset halfwords in the font style block: arg1 at +0x2A, arg0 at +0x28.
void Font_SetShadowOffset(s16 arg0, s16 arg1) {
    u8 *base;

    base = &gFontStyle;
    *(s16 *)(base + 0x28) = arg0;
    *(s16 *)(base + 0x2A) = arg1;
}
