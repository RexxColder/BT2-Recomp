#include "common.h"

s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023C710(s32 arg0);
extern f32 D_00386A68;

s32 func_002379B8(s32 arg0) {
    if (func_00211310(arg0, 2, 1) != 0) {
        func_002113C0(arg0, 5, 0x100, 1);
        BtlAnim_SetBlend(arg0, D_00386A68);
        return func_0023C710(arg0);
    }
    return -1;
}
