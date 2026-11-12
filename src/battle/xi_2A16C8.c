#include "m2c_macros.h"

extern u8 gFontStyle __attribute__((section(".data")));

// Replaces the user flags word of the font style block (+0x34): (old & arg0) | arg1.
void Font_ChangeUserFlags(s32 arg0, s32 arg1) {
    u8 *base;

    base = &gFontStyle;
    *(s32 *)(base + 0x34) = (*(s32 *)(base + 0x34) & arg0) | arg1;
}
