#include "common.h"

s32 BtlCtrl_IsInterruptible(u32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_00387930;

s32 func_0020A890(u32 arg0) {
    s32 t;

    if (D_00387930 == 0 || arg0 >= 2U) {
        return 0;
    }
    t = func_00211288((s32)arg0);
    if (BtlCtrl_IsInterruptible(arg0) == 0) {
        return 0;
    }
    return func_00211310(t, 7, 0x40000) != 0;
}
