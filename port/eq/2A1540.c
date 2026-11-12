#include "common.h"

extern u8 gFontStyle[] __attribute__((section(".data")));

void Font_SetClip(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(s16 *)(gFontStyle + 0x32) = arg3;
    *(s16 *)(gFontStyle + 0x2C) = arg0;
    *(s16 *)(gFontStyle + 0x2E) = arg1;
    *(s16 *)(gFontStyle + 0x30) = arg2;
}
