#include "common.h"

void func_001FA110(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_003860E8;
extern f32 D_003860EC;
extern f32 D_003860F0;

void func_00223950(s32 arg0) {
    f32 temp_f20;

    temp_f20 = D_003860E8;
    func_001FA110(arg0, 0);
    func_00215068(arg0, 5, 0xD, D_003860EC, temp_f20);
    func_00215E88(temp_f20, arg0, 6);
    func_00216208(arg0, 0.0f, D_003860F0);
    func_00216678(arg0);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
