#include "m2c_macros.h"

extern s32 Battle_GetSetup(s32 arg0);
extern s32 BtlObjAnim_QueryEvent(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_001F9898(s32 arg0);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00218128(s32 arg0, s32 arg1);
extern u32 func_0023E520(s32 arg0);

s32 func_0023EAE0(s32 arg0) {
    f32 f20;
    s32 ret;

    f20 = (f32)*(s32 *)((u8 *)Battle_GetSetup(arg0) + 4);
    f20 = (f20 * (f32)func_001F9898(arg0)) / 100.0f;
    if (func_00211310(arg0, 0, 0x800) != 0 && func_00218128(arg0, 4) != 0 && func_0023E520(arg0) < 10) {
        f20 = f20 - (f20 * 3.0f) / 10.0f;
    }
    ret = BtlObjAnim_QueryEvent(*(s32 *)(arg0 + 0x1530), 1, 0, 2);
    if (ret > 0) {
        f20 = f20 / (f32)ret;
    }
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    return (s32)f20;
}
