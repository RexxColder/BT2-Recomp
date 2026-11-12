#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_0038679C;
extern f32 D_003867A0;
extern f32 D_003867A4;

void func_0022F4F8(s32 arg0) {
    f32 temp_f20;

    temp_f20 = D_0038679C;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xD, D_003867A0, temp_f20);
    func_00215E88(arg0, 7, temp_f20);
    func_00216208(arg0, 0.0f, D_003867A4);
    func_00216678(arg0);
    func_002113C0(arg0, 3, 0x4000, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 1, 0x800000, 1);
}
