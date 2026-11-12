#include "common.h"

void BtlAnim_SetBlend(s32 arg0, s32 arg1, f32 farg0);
f32 func_001FA318(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_0023BDA8(s32 arg0, s32 arg1, f32 farg0);
s32 func_0023C710(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
extern f32 D_003867A8;
extern f32 D_003867AC;
extern f32 D_003867B0;
extern f32 D_003867B4;

s32 func_0022F5A8(s32 arg0) {
    s32 t2;
    s32 v;

    if (D_003867A8 < func_001FA318(arg0)) {
        t2 = func_0023C798(arg0, 3);
        if (t2 != -1) {
            BtlAnim_SetBlend(arg0, 0x420000, D_003867AC);
            return t2;
        }
        v = func_0023BDA8(arg0, 0x420000, D_003867AC);
        if (v != t2) {
            BtlAnim_SetBlend(arg0, 0, D_003867B0);
            return v;
        }
    }
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, 0, D_003867B4);
        return func_0023C710(arg0);
    }
    return -1;
}
