#include "common.h"

void BtlChar_SetVibration(s32 arg0, f32 farg0, f32 farg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

void func_0020D178(u32 arg0, f32 farg0, f32 farg1) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        BtlChar_SetVibration(func_00211288((s32)arg0), farg0, farg1);
    }
}
