#include "common.h"

void func_001FBE80(s32 arg0, f32 farg0, f32 farg1);
s32 func_00211288(s32 arg0);
extern s32 D_00387930;

void func_0020CFD8(u32 arg0, f32 farg0, f32 farg1) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        func_001FBE80(func_00211288((s32)arg0), farg0, farg1);
    }
}
