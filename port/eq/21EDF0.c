#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
extern f32 D_00385E98;
extern f32 D_00385E9C;
extern f32 D_00385EA0;

void func_0021EDF0(s32 arg0) {
    func_001F9FB0(arg0, 0);
    func_00215068(D_00385E98, 0.5f, arg0, 5, 0xC);
    func_00215E88(D_00385E9C, arg0, 2);
    func_00216208(0.0f, D_00385EA0, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 5, 1, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
