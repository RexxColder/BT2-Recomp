#include "common.h"

s32 BtlMenu_IsControls(s32 arg0);
s32 BtlMenu_IsSkillList(s32 arg0);
s32 Font_GetGlyphHeight();
s32 func_00106958(s32 arg0);

s32 func_00106C98(s32 arg0) {
    s32 x;
    s32 h;
    f32 f;
    s32 r;

    if (arg0 == 0) {
        return 0;
    }
    if (BtlMenu_IsSkillList(arg0) != 0) {
        h = Font_GetGlyphHeight(arg0);
        x = h * 9 * 2;
    } else if (BtlMenu_IsControls(arg0) != 0) {
        h = Font_GetGlyphHeight(arg0);
        x = h * 3 * 4;
    } else if (func_00106958(arg0) != 0) {
        h = Font_GetGlyphHeight();
        x = h * 15;
    } else {
        x = *(s32 *)(arg0 + 4) * 28;
    }
    f = (f32)x * *(f32 *)(arg0 + 8);
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    r = (s32)f;
    return r + *(s16 *)(arg0 + 0xE) * 2;
}
