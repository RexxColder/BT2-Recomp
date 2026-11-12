#include "m2c_macros.h"

extern s32 func_001F9FB0(s32 arg0, s32 arg1);
extern void func_0020D7E8(s32 arg0, f32 farg0, f32 farg1);
extern s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
extern void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
extern void func_00216208(s32 arg0, f32 farg0, f32 farg1);
extern void func_00216678(s32 arg0);
extern f32 D_00386778;
extern f32 D_0038677C;
extern f32 D_00386780;

void func_0022F280(s32 arg0) {
    f32 f20;

    f20 = D_00386778;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xC, D_0038677C, f20);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386780);
    func_00216678(arg0);
    func_002113C0(arg0, 3, 0x4000, 1);
    func_0020D7E8(arg0, 20.0f, 50.0f);
}
