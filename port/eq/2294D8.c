#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
f32 func_0023FC58(s32 arg0);
s32 func_001FA1D0(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
f32 func_00240E80(s32 arg0, s32 arg1);
f32 BtlMove_CalcJumpSpeed(f32 farg0);
s32 BtlChar_GetPos(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);
f32 func_00240D50(s32 arg0, s32 arg1);
f32 func_00207E90(s32 arg0);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
void func_0020D7E8(f32 farg0, f32 farg1, s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
extern f32 D_00386410;
extern f32 D_00386414;
extern f32 D_00386418;

void func_002294D8(s32 arg0) {
    s32 var_a1;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f21;
    f32 var_f0;

    func_001F9FB0(arg0, 0);
    if (func_001FA1D0(func_0023FC58(arg0), arg0) != 0) {
        if (func_00211310(arg0, 1, 2) != 0) {
            var_f0 = BtlMove_CalcJumpSpeed(func_00240E80(arg0, 1));
        } else {
            var_f0 = BtlMove_CalcJumpSpeed(func_00240E80(arg0, 0));
        }
        *(f32 *)(BtlChar_GetPos(arg0) + 0xC4) = var_f0;
    }
    var_a1 = 0xE;
    if (func_00211310(arg0, 1, 2) == 0) {
        var_a1 = 0xD;
    }
    temp_f20 = func_00240D50(arg0, var_a1);
    temp_f21 = temp_f20 * func_00207E90(arg0);
    temp_f20_2 = D_00386410;
    func_00215068(D_00386414, temp_f20_2, arg0, 5, 0xC);
    func_00215E88(temp_f20_2, arg0, 2);
    func_00216208(temp_f21, D_00386418, arg0);
    func_00216678(arg0);
    func_0020D7E8(20.0f, 50.0f, arg0);
    func_002113C0(arg0, 9, 0x1000, 1);
    func_002113C0(arg0, 1, 0x40, 1);
    func_00206958(arg0, (s64)0x8000 << 28);
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
}
