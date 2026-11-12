#include "common.h"

s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00386C20;
extern f32 D_00386C24;
extern f32 D_00386C28;

void func_0023BC60(s32 arg0) {
    f32 temp_f20;

    temp_f20 = D_00386C20;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xD, D_00386C24, temp_f20);
    func_00215E88(arg0, 7, temp_f20);
    func_00216208(arg0, 0.0f, D_00386C28);
    func_00216678(arg0);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
}
