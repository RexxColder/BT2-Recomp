#include "common.h"

s32 Font_CharSize(s32 arg0);
s32 Font_ReadChar(s32 arg0, s32 arg1);
s32 Font_IsNewline(s32 arg0);
void *Font_FindGlyph(s32 arg0, s32 arg1);
extern s32 gFontGlyphGap;
extern u8 gFontStyle[] __attribute__((section(".data")));

s32 BtlCtrl_SetChargeFx(s32 arg0, s32 arg1) {
    s32 pos;
    s32 best;
    s32 cur;
    s32 base;
    s32 ch;
    s32 a1;
    void *glyph;
    s32 idx;
    s32 r;
    f32 f;

    pos = arg0;
    best = 0;
    cur = 0;
    base = gFontGlyphGap + *(s32 *)(gFontStyle + 0x10);
loop_4:
    a1 = pos;
loop_5:
    ch = Font_ReadChar(arg1, a1);
    pos += Font_CharSize(arg1);
    if (ch != 0) {
        if (Font_IsNewline(ch) != 0) {
            cur = 0;
            if (!(*(s32 *)(gFontStyle + 0x1C) & 1)) {
                goto loop_4;
            }
        } else {
            a1 = pos;
            glyph = Font_FindGlyph(ch, 0);
            if (glyph != NULL) {
                idx = (*(u16 *)((u8 *)glyph + 2) >> 10) & 0x1F;
                f = (f32)idx * *(f32 *)(gFontStyle + 0);
                f = f * *(f32 *)(gFontStyle + 8);
                /* cvt.w.s: truncates toward zero */
                r = (s32)f;
                cur += r + base;
                if (best < cur) {
                    best = cur;
                }
                goto loop_4;
            }
            goto loop_5;
        }
    }
    return best - base;
}
