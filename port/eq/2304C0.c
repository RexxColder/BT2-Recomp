#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
extern f32 D_00386824;
extern f32 D_00386828;
extern f32 D_0038682C;

void func_002304C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 temp_f20;

    temp_f20 = D_00386824;
    func_001F9FB0(arg0, 0, arg2, arg3);
    func_00215068(D_00386828, temp_f20, arg0, 5, 0xC);
    func_00215E88(temp_f20, arg0, 6);
    func_00216208(0.0f, D_0038682C, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x1000, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 9, 0x200000, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 3, 0xF, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_00206958(arg0, 0x8000);
    func_002113C0(arg0, 0xF, 0x100000, 1);
}
