#include "common.h"

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003876A8;
extern s32 D_003B0F70 __attribute__((section(".data")));

s32 func_002A3D38(s32 arg0) {
    s32 ret = func_00100ED0(arg0, 0, D_003876A8 != 0);
    D_003B0F70 = ret;
    if (D_003876A8 != 0) {
        D_003876A8 = 0;
    }
    return ret;
}
