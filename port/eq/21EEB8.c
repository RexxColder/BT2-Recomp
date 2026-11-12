#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg0);
f32 func_001FA318(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
extern f32 D_00385EA4;
extern f32 D_00385EA8;
extern f32 D_00385EAC;

s32 func_0021EEB8(s32 arg0) {
    func_002174D8(arg0, func_0023C798(arg0, 3));
    if ((D_00385EA4 < func_001FA318(arg0)) && (func_002174B8(arg0) != -1)) {
        BtlAnim_SetBlend(D_00385EA8, arg0);
        return func_002174B8(arg0);
    }
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(D_00385EAC, arg0);
        return func_0023C710(arg0);
    }
    return -1;
}
