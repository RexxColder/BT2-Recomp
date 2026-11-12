#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_002174B8(s32 arg0);
s32 func_0023C710(s32 arg0);
extern f32 D_00386170;

/* 0x00224A28(obj): when func_00211310(obj, 2, 1) == 0 returns -1. Otherwise BtlAnim_SetBlend(obj, D_00386170); then
 * func_002174B8(obj) == -1 tail-calls func_0023C710(obj), else the result of a second func_002174B8(obj) is returned. */
s32 func_00224A28(s32 arg0) {
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386170);
    if (func_002174B8(arg0) == -1) {
        return func_0023C710(arg0);
    }
    return func_002174B8(arg0);
}
