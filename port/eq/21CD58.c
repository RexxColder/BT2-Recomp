#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(f32 farg0, s32 arg1, s32 arg2, s32 arg3, f32 farg1);
void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
void func_00216208(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
extern f32 D_00385D94;
extern f32 D_00385D98;
extern f32 D_00385D9C;

void func_0021CD58(s32 arg0) {
    func_001F9FB0(arg0, 0);
    func_00215068(D_00385D94, arg0, 1, 0xC, 0.5f);
    func_00215E88(D_00385D98, arg0, 2);
    func_00216208(arg0, 0, 0.0f, D_00385D9C);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    if (func_00211310(arg0, 0, 0x100, 0, 0.0f, 0.0f) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
