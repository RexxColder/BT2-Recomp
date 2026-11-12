#include "common.h"

s32 func_0023F420(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 func_001FA1D0(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
extern f32 D_00385C9C;
extern f32 D_00385CA0;

s32 func_0021B520(s32 arg0) {
    if ((func_0023F420(arg0) & 0x2000) && (func_00211310(arg0, 4, 2) != 0)) {
        if (BtlPad_Test4C(arg0, 1) != 0) {
            func_002174D8(arg0, 0x79);
        }
        if ((func_001FA1D0(D_00385C9C, arg0) != 0) && (func_002174B8(arg0) != -1)) {
            return func_002174B8(arg0);
        }
    }
    if (func_00211310(arg0, 2, 1) != 0) {
        BtlAnim_SetBlend(arg0, D_00385CA0);
        return func_0023C710(arg0);
    }
    return -1;
}
