#include "common.h"

s32 func_00211288();
s32 BtlCtrl_IsInterruptible(u32 arg0);
s32 func_0020A908(u32 arg0);
s32 func_00209B08(u32 arg0);
u32 func_00210DD8(s32 arg0);
s32 func_0025AB48();
extern s32 D_00387930;
extern u8 *D_003876A0;

s32 BtlScene_IsCharInView(u32 arg0) {
    s32 s0;
    s32 s2;
    s32 v;

    if (D_00387930 == 0) {
        return 0;
    }
    if (!(arg0 < 2U)) {
        return 0;
    }
    s2 = func_00211288(arg0);
    if (BtlCtrl_IsInterruptible(arg0) != 0) {
        return 0;
    }
    if (func_0020A908(arg0) != 0) {
        return 0;
    }
    if (func_0025AB48() != 0) {
        return 1;
    }
    s0 = func_00209B08(arg0);
    v = func_00209B08(func_00210DD8(s2));
    if (v < s0) {
        return 1;
    }
    if (s0 < v) {
        return 0;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        return 1;
    }
    return arg0 == 0;
}
