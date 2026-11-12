#include "common.h"

void BtlMove_BrakeVertical(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00216770(s32 arg0);

/* if func_00211310(arg0, 0, 2) is nonzero: BtlMove_BrakeVertical(arg0), else func_00216770(arg0) */
void func_00216678(s32 arg0) {
    if (func_00211310(arg0, 0, 2) != 0) {
        BtlMove_BrakeVertical(arg0);
        return;
    }
    func_00216770(arg0);
}
