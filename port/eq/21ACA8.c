#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001FA2E0(s32 arg0);
s32 func_0023F2D8(s32 arg0);
void func_00212DD8(s32 arg0, s32 arg1);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00385C44;
extern f32 D_00385C48;
extern f32 D_00385C4C;

void func_0021ACA8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = BtlObjXf_Update(arg0);
    if (temp_v0 == 0x5F) {
        func_001FA0A0(arg0, 0x61, 0, 0x61);
    } else if (temp_v0 == 0x61) {
        func_001F9FB0(arg0, 0, 0, 0x61);
        if (func_001FA2E0(arg0) != 0) {
            func_00212DD8(arg0, func_0023F2D8(arg0));
        }
    }

    func_00215068(D_00385C44, 0.5f, arg0, 5, 0xC);
    func_00215E88(D_00385C48, arg0, 2);
    func_00216208(0.0f, D_00385C4C, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 1, 0x800000, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
