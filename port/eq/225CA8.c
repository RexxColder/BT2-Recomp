#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FA110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_00386220;
extern f32 D_00386224;
extern f32 D_00386228;

void func_00225CA8(s32 arg0) {
    s32 v;
    f32 f20;

    v = BtlObjXf_Update(arg0);
    if (v == 0x10F) {
        func_001FA0A0(arg0, 0x110, 0, 0x110);
    } else if (v == 0x110) {
        func_001FA110(arg0, 0, 0, 0x110);
    }
    f20 = D_00386220;
    func_00215068(arg0, 5, 0xC, D_00386224, f20);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386228);
    func_00216678(arg0);
    func_002113C0(arg0, 3, 0x10, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
