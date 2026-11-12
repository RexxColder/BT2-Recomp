#include "common.h"

extern f32 D_00386A30;
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 BtlAnim_SetBlend(s32 arg0, s32 arg1, s32 arg2, f32 farg0);

s32 func_00237030(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, 2, 1, D_00386A30);
        return 0x98;
    }
    return -1;
}
