#include "common.h"

s32 Font_CountLinesEx(s32 arg0, s32 arg1);
s32 Font_GetGlyphHeight(void);
extern u8 gFontStyle[] __attribute__((section(".data")));

s32 Font_GetHeight(s32 arg0) {
    s32 lines;
    s32 spacing;
    s32 h;

    lines = Font_CountLinesEx(arg0, 0);
    h = (s32)((f32)Font_GetGlyphHeight() * *(f32 *)(gFontStyle + 0x04) * *(f32 *)(gFontStyle + 0x08));
    spacing = *(s32 *)(gFontStyle + 0x14);
    return lines * (h + spacing) - spacing;
}
