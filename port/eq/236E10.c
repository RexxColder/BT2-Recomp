#include "common.h"

s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023C710(s32 arg0);
extern f32 D_00386A18;

s32 func_00236E10(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, D_00386A18);
        return func_0023C710(arg0);
    }
    return -1;
}
