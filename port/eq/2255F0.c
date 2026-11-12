#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
extern f32 D_003861D4;
extern f32 D_003861D8;
extern f32 D_003861DC;

void func_002255F0(s32 arg0) {
    f32 f20;

    f20 = D_003861D4;
    func_001F9FB0(arg0, 0);
    func_00215068(D_003861D8, f20, arg0, 5, 0xC);
    func_00215E88(f20, arg0, 7);
    func_00216208(0.0f, D_003861DC, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 3, 0x100, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
