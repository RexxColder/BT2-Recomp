#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_00386164;
extern f32 D_00386168;
extern f32 D_0038616C;

void func_00224950(s32 arg0) {
    f32 f20;

    if (BtlObjXf_Update(arg0) == 0xFF) {
        func_001F9FB0(arg0, 0);
    }
    f20 = D_00386164;
    func_00215068(arg0, 2, 0xC, D_00386168, f20);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_0038616C);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
