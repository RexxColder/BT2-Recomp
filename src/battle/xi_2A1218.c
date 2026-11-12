#include "m2c_macros.h"

extern u8 gFontCursor __attribute__((section(".data")));

// Outputs two words of the font cursor block gFontCursor: +8 to *arg0, +0xC to *arg1.
void func_002A1218(s32 *arg0, s32 *arg1) {
    u8 *base;

    base = &gFontCursor;
    *arg0 = *(s32 *)(base + 8);
    *arg1 = *(s32 *)(base + 0xC);
}
