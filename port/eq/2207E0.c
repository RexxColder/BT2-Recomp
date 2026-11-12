#include "common.h"

s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
s32 func_00217488(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
void BtlMove_BrakeVertical(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
extern f32 D_00385F2C;
extern f32 D_00385F30;
extern f32 D_00385F34;
extern f32 D_00385F38;

void func_002207E0(s32 arg0) {
    f32 temp_f20;
    f32 var_f21;
    s32 temp_v0;

    func_001F9FB0(arg0, 0);
    var_f21 = 0.0f;
    temp_v0 = func_00217488(arg0);
    if (temp_v0 != 0x98) {
        if (temp_v0 < 0x99) {
            if (temp_v0 == 0x97) {
                var_f21 = D_00385F2C;
            }
        }
    } else {
        var_f21 = D_00385F2C;
    }
    temp_f20 = D_00385F30;
    func_00215068(arg0, 5, 0xD, D_00385F34, temp_f20);
    if (func_00218838(arg0, 0) != 0) {
        func_00215E88(temp_f20, arg0, 3);
    } else {
        func_00215E88(temp_f20, arg0, 5);
    }
    func_00216208(arg0, var_f21, D_00385F38);
    BtlMove_BrakeVertical(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_002113C0(arg0, 0x10, 0x100000, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (func_00211310(arg0, 0, 4) != 0) {
        func_002113C0(arg0, 0, 2, 0);
    }
}
