#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00212DD8(s32 arg0, s32 arg1);
void func_002100C0(s32 arg0, s32 arg1);
extern f32 D_0038604C;
extern f32 D_00386050;
extern f32 D_00386054;

void func_00222A78(s32 arg0) {
    s32 v0;
    s32 v1;
    f32 f20;

    v1 = BtlObjXf_Update(arg0);
    if (v1 == 0xD8) {
        func_001F9FB0(arg0, 0);
    } else if (v1 < 0xD9) {
        if (v1 == 0xD7) {
            goto common_0xDB;
        }
        goto common_end;
    } else if (v1 == 0xD9) {
        goto common_0xDB;
    } else if (v1 == 0xDA) {
        func_001F9FB0(arg0, 0);
    }
    goto common_end;

common_0xDB:
    v0 = func_00211310(arg0, 0, 4);
    if (v0 == 0) {
        func_001F9FB0(arg0, 0);
    } else {
        v0 = BtlObjXf_Update(arg0);
        v0 = func_001FA0A0(arg0, v0 + 1, 0);
        if (v0 != 0) {
            func_00212DD8(arg0, 0);
            func_002100C0(arg0, 2);
        }
    }

common_end:
    f20 = D_0038604C;
    func_00215068(arg0, 5, 0xD, D_00386050, f20);
    func_00215E88(f20, arg0, 7);
    func_00216208(arg0, 0.0f, D_00386054);
    func_00216678(arg0);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    v0 = func_00211310(arg0, 0, 0x100);
    if (v0 != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
