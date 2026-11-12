#include "common.h"

extern s32 D_00387930;
s32 func_00211288(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* 0x0020CC68: if D_00387930 is set and arg0 < 2 (unsigned), tail call func_002113C0(func_00211288(arg0), 7, 2, 1). */
void func_0020CC68(s32 arg0) {
    if (D_00387930 == 0) {
        return;
    }
    if ((u32)arg0 >= 2) {
        return;
    }
    func_002113C0(func_00211288(arg0), 7, 2, 1);
}
