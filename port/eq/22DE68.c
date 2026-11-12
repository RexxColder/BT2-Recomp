#include "common.h"

s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
f32 func_001FA318(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
s32 func_0023C710(s32 arg0);
extern f32 D_003866E0;
extern f32 D_003866E4;
extern f32 D_003866E8;

s32 func_0022DE68(s32 arg0) {
    if ((D_003866E0 < func_001FA318(arg0)) && (func_002174B8(arg0) != -1)) {
        BtlAnim_SetBlend(arg0, D_003866E4);
        return func_002174B8(arg0);
    }
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, D_003866E8);
        return func_0023C710(arg0);
    }
    return -1;
}
