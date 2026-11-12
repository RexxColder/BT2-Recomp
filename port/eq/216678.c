#include "common.h"

/* 0x00216678: if (func_00211310(a0, 0, 2)) tail BtlMove_BrakeVertical(a0); else tail func_00216770(a0). */
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00216770(s32 arg0);
void BtlMove_BrakeVertical(s32 arg0);

void func_00216678(s32 a0) {
    if (func_00211310(a0, 0, 2) != 0) {
        BtlMove_BrakeVertical(a0);
        return;
    }
    func_00216770(a0);
}
