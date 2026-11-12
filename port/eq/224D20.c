#include "common.h"

s32 BtlPad_Test48(s32 arg0, s32 arg1);
void BtlAnim_SetBlend(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
s32 func_0023C710(s32 arg0);
extern f32 D_00386190;
extern f32 D_00386194;

s32 func_00224D20(s32 arg0) {
    if (BtlPad_Test48(arg0, 6) == 0) {
        BtlAnim_SetBlend(arg0, 0, 1, D_00386190);
        return func_0023C710(arg0);
    }
    if (func_00211310(arg0, 0, 1, D_00386190) != 0) {
        BtlAnim_SetBlend(arg0, 0, 0, D_00386194);
        return func_0023C710(arg0);
    }
    return -1;
}
