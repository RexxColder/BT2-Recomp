#include "common.h"

s32 Font_GetGlyphHeight(void);
s32 func_00108780(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

/* 0x00108910: draws one glyph (arg3 & 0xFFFF) at arg0/arg1/arg2 with the glyph height (20 * height on the
 * third argument). Digits 0..8 choose a fifth value (0..7, 8 counts as 7, others 0); the characters '7' and
 * '8' draw a second piece below. Returns the result of the last draw. */
s32 func_00108910(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 ch;
    s32 h;
    s32 s1;
    s32 idx;
    s32 t1;
    s32 s0;

    ch = arg3 & 0xFFFF;
    h = Font_GetGlyphHeight();
    s1 = (((h << 2) + h) << 2);

    idx = ch - 0x30;
    t1 = 0;
    if ((u32)idx < 9) {
        t1 = (idx < 7) ? idx : 7;
    }

    s0 = func_00108780(arg0, arg1, arg2, s1, 0x20, t1 + 0x14);
    if (ch == 0x37) {
        s0 = func_00108780(s0, arg1 + s1 - 0x80, arg2 - 0x10, 0x80, 0x40, 0x1C);
    } else if (ch == 0x38) {
        s0 = func_00108780(s0, arg1 + s1 - 0x80, arg2 - 0x10, 0x80, 0x40, 0x1D);
    }
    return s0;
}
