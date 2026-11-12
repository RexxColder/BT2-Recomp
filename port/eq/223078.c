#include "common.h"

void func_001FA110(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216770(s32 arg0, f32 farg0, f32 farg1);
void func_00216890(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00386088;
extern f32 D_0038608C;
extern f32 D_00386090;
extern f32 D_00386094;

void func_00223078(s32 arg0) {
    f32 temp_f20;
    f32 temp_f21;

    temp_f20 = D_00386088;
    func_001FA110(arg0, 0);
    temp_f21 = D_00386090;
    func_00215068(arg0, 5, 0xD, D_0038608C, temp_f20);
    func_00215E88(arg0, 6, temp_f20);
    func_00216208(arg0, 0.0f, temp_f21);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_00216890(arg0, D_00386094, temp_f21);
    } else {
        func_00216770(arg0, D_00386094, temp_f21);
    }
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_002113C0(arg0, 1, 0x02000000, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
