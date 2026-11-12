#include "common.h"

void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
extern f32 D_00385AB0;
extern f32 D_00385AB4;
extern f32 D_00385AB8;

void func_00216618(s32 arg0) {
    f32 f20;

    f20 = D_00385AB4;
    func_00215068(arg0, 5, 0xC, D_00385AB0, f20);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_00385AB8);
}
