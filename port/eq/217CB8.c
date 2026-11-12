#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void BtlOpp_GetDelta(s32 arg0, s32 arg1);
void func_002109C8(s32 arg0, s32 arg1);
f32 BtlOpp_GetHalfHeightDiff(s32 arg0);
f32 BtlMove_CalcVerticalSpeed(s32 arg0, f32 farg0, f32 farg1);
s32 BtlChar_GetPos(s32 arg0);
extern f32 D_00385B28;

void func_00217CB8(s32 arg0) {
    f32 sp[8];
    f32 f20;
    f32 hh;

    if (func_00211310(arg0, 5, 8) == 0) {
        if (func_00211310(arg0, 0, 1) != 0) {
            func_00215068(arg0, 1, 0xC, D_00385B28, 0.0f);
            func_002113C0(arg0, 0, 2, 1);
            BtlOpp_GetDelta(arg0, (s32)sp);
            func_002109C8(arg0, (s32)&sp[4]);
            hh = BtlOpp_GetHalfHeightDiff(arg0);
            f20 = BtlMove_CalcVerticalSpeed(arg0, sp[1] + hh, sp[5] * 0.5f);
            *(f32 *)(BtlChar_GetPos(arg0) + 0xC4) = f20;
            func_002113C0(arg0, 5, 4, 1);
        }
    }
    func_002113C0(arg0, 5, 2, 1);
    func_002113C0(arg0, 5, 8, 1);
}
