#include "common.h"

s32 func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_0038620C;
extern f32 D_00386210;
extern f32 D_00386214;

void func_00225B00(s32 arg0) {
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 1, 0xC, D_0038620C, 0.5f);
    func_00215E88(D_00386210, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386214);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 3, 0x40, 1);
    func_002113C0(arg0, 3, 0x80, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
