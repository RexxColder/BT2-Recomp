#include "common.h"

s32 func_00211288(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 D_00387930;

/* when D_00387930 is set and arg0 < 2: func_002113C0(func_00211288(arg0), 7, 1, 1) (tail call) */
void BtlCharApi_SetHeldFlagA7(u32 arg0) {
    if ((D_00387930 != 0) && (arg0 < 2U)) {
        func_002113C0(func_00211288(arg0), 7, 1, 1);
    }
}
