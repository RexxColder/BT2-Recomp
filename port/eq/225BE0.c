#include "common.h"

void BtlAnim_SetBlend(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_0023C710(s32 arg0);
extern f32 D_00386218;
extern f32 D_0038621C;

s32 func_00225BE0(s32 arg0, f32 farg0) {
    if (func_00211310(arg0, 0, 4, farg0) != 0) {
        BtlAnim_SetBlend(arg0, 2, 1, D_00386218);
        return func_0023C710(arg0);
    }
    if (func_00211310(arg0, 2, 1, D_00386218) != 0) {
        BtlAnim_SetBlend(arg0, 0, 0, D_0038621C);
        return 0xA;
    }
    return -1;
}
