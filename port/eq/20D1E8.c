#include "common.h"

void *func_00211288(s32 arg0);
void BtlChar_SetSmallVibration(f32 arg0, void *arg1, s32 arg2);
extern s32 D_00387930;

void func_0020D1E8(u32 arg0, s32 arg1, f32 farg0) {
    void *temp_v0;

    if (D_00387930 != 0 && arg0 < 2U) {
        temp_v0 = func_00211288(arg0);
        BtlChar_SetSmallVibration(farg0, temp_v0, arg1);
    }
}
