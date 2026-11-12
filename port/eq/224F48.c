#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FA110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_003861A4;
extern f32 D_003861A8;
extern f32 D_003861AC;

void func_00224F48(s32 arg0) {
    s32 v;
    f32 f20;

    v = BtlObjXf_Update(arg0);
    if (v == 0x19B) {
        func_001FA0A0(arg0, 0x19C, 0, 0x19C);
    } else if (v == 0x19C) {
        func_001FA110(arg0, 0, 0, 0x19C);
    }
    f20 = D_003861A4;
    func_00215068(arg0, 5, 0xC, D_003861A8, f20);
    func_00215E88(arg0, 7, f20);
    func_00216208(arg0, 0.0f, D_003861AC);
    func_00216678(arg0);
    func_002113C0(arg0, 3, 0xF, 1);
    func_002113C0(arg0, 9, 0x10000, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 9, 4, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
}
