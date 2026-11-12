#include "common.h"

f32 EftMath_WrapAngle(f32 arg0);
void Mtx_RotateX(f32 farg0, void *arg0, void *arg1);
void Mtx_RotateY(f32 farg0, void *arg0, void *arg1);
s32 func_00129C50(s32 arg0, void *arg1, s32 arg2);

void func_00189530(s32 arg0, u8 *arg1, f32 farg0, f32 farg1) {
    s64 sp[8];

    sp[0] = *(s64 *)(arg1 + 0x00);
    sp[1] = *(s64 *)(arg1 + 0x08);
    sp[2] = *(s64 *)(arg1 + 0x10);
    sp[3] = *(s64 *)(arg1 + 0x18);
    sp[4] = *(s64 *)(arg1 + 0x20);
    sp[5] = *(s64 *)(arg1 + 0x28);
    sp[6] = *(s64 *)(arg1 + 0x30);
    sp[7] = *(s64 *)(arg1 + 0x38);
    Mtx_RotateX(EftMath_WrapAngle(farg0), sp, sp);
    Mtx_RotateY(EftMath_WrapAngle(farg1), sp, sp);
    func_00129C50(arg0, sp, arg0);
}
