#include "common.h"

s32 BtlMenu_IsSkillList(u8 *arg0);
s32 BtlMenu_IsControls(u8 *arg0);
s32 Font_GetGlyphHeight(void);
s32 Timer_Reset(s32 arg0);
s32 func_00106958(u8 *arg0);
s32 func_00106998(s32 arg0);
extern void *gObjOutline;

s32 func_00106B58(u8 *arg0) {
    s32 s2;
    s32 s3;
    s32 s0;
    s32 r;
    s32 tr;
    f32 f;
    s32 frac_r;

    s3 = *(s32 *)((u8 *)gObjOutline + 8);
    if (arg0 == NULL) {
        return 0;
    }
    s2 = 0;
    if (BtlMenu_IsSkillList(arg0) != 0) {
        s2 = Font_GetGlyphHeight() * 20;
    } else if (BtlMenu_IsControls(arg0) != 0) {
        s2 = Font_GetGlyphHeight() * 16;
    } else if (func_00106958(arg0) == 0) {
        if (*(s32 *)(arg0 + 4) > 0) {
            s3 = s3 << 1;
            s0 = 0;
            do {
                r = func_00106998((s16)*(s16 *)(*(u8 **)arg0 + (s0 << 5) + s3));
                s0 += 1;
                tr = Timer_Reset(r);
                if (s2 < tr) {
                    s2 = tr;
                }
            } while (s0 < *(s32 *)(arg0 + 4));
        }
        if (s2 < 0x80) {
            s2 = 0x80;
        }
    } else {
        s2 = Font_GetGlyphHeight() * 22;
    }
    f = (f32)s2 * *(f32 *)(arg0 + 8);
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    frac_r = (s32)f;
    return frac_r + *(s16 *)(arg0 + 0xC) * 2;
}
