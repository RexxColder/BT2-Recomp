#include "common.h"

void *Font_FindGlyph(s32 arg0, s32 arg1);
s32 Font_IsNewline(s32 arg0);
extern s32 gFontCursor __attribute__((section(".data")));
extern s32 gFontGlyphGap;
extern s32 D_00387ED8;

s32 Font_AdvanceChar(void *arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    u8 *s1;
    s32 ch;
    s32 ret;
    s32 rr;
    f32 f;
    void *glyph;
    s32 idx;
    s32 a1;

    s1 = (u8 *)arg0;
    ch = arg3 & 0xFFFF;
    ret = 0;
    if (ch == 0) {
        return 1;
    }
    if (Font_IsNewline(ch) != 0) {
        *arg1 = gFontCursor;
        f = (f32)(D_00387ED8 + *(u16 *)(s1 + 0x1A)) * *(f32 *)(s1 + 0x14);
        /* cvt.w.s: truncates toward zero */
        rr = (s32)f;
        *arg2 = *arg2 + rr;
        if (*(s32 *)(s1 + 0x3C) & 1) {
            return 1;
        }
        return ret;
    }

    glyph = Font_FindGlyph(ch, 0);
    if (glyph == NULL) {
        return ret;
    }
    idx = (*(u16 *)((u8 *)glyph + 2) >> 10) & 0x1F;
    a1 = *(u16 *)(s1 + 0x18) + gFontGlyphGap;
    f = (f32)idx * *(f32 *)(s1 + 0x10);
    /* cvt.w.s: truncates toward zero */
    rr = (s32)f;
    *arg1 = *arg1 + rr + a1;
    return ret;
}
