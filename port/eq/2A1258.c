#include "common.h"

extern s32 D_00387ED8;
extern u8 gFontCursor[] __attribute__((section(".data")));
extern u8 gFontStyle[] __attribute__((section(".data")));

f32 Font_NewLine(void) {
    f32 temp_f1;
    f32 result;

    temp_f1 = *(f32 *)(gFontStyle + 4) * *(f32 *)(gFontStyle + 8);
    *(s32 *)(gFontCursor + 8) = *(s32 *)(gFontCursor + 0);
    result = (f32)(D_00387ED8 + *(s32 *)(gFontStyle + 0x14)) * temp_f1;
    *(s32 *)(gFontCursor + 0xC) = *(s32 *)(gFontCursor + 0xC) + (s32)result;
    return result;
}
