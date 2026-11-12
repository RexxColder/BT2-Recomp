#include "m2c_macros.h"

extern s32 func_001F9FB0(s32 arg0, s32 arg1);
extern s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
extern void func_00216208(s32 arg0, f32 farg0, f32 farg1);
extern void func_00216678(s32 arg0);
extern f32 D_00386038;
extern f32 D_0038603C;
extern f32 D_00386040;

void func_00222778(s32 arg0) {
    f32 f20;

    f20 = D_00386038;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xC, D_0038603C, f20);
    func_00215E88(f20, arg0, 6);
    func_00216208(arg0, 0.0f, D_00386040);
    func_00216678(arg0);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
