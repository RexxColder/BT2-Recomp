#include "common.h"

s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_001FA1D0(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
extern f32 D_00385D20;
extern f32 D_00385D24;
extern f32 D_00385D28;

s32 func_0021C3C0(s32 arg0) {
    if (func_00211310(arg0, 4, 2) != 0) {
        if (BtlPad_Test4C(arg0, 0) != 0) {
            func_002174D8(arg0, 0x49);
        }
        if ((func_001FA1D0(D_00385D20, arg0) != 0) && (func_002174B8(arg0) != -1)) {
            BtlAnim_SetBlend(arg0, D_00385D24);
            return func_002174B8(arg0);
        }
    }
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, D_00385D28);
        return func_0023C710(arg0);
    }
    return -1;
}
