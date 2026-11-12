#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_00206958(s32 arg0, s64 arg1);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_003861B0;
extern f32 D_003861B4;
extern f32 D_003861B8;

s32 func_00225138(s32 arg0) {
    f32 f20;

    if (BtlObjXf_Update(arg0) == 0x19D) {
        func_001F9FB0(arg0, 0);
    }
    f20 = D_003861B0;
    func_00215068(arg0, 5, 0xC, D_003861B4, f20);
    func_00215E88(arg0, 7, f20);
    func_00216208(arg0, 0.0f, D_003861B8);
    func_00216678(arg0);
    func_002113C0(arg0, 3, 0xF, 1);
    func_002113C0(arg0, 9, 0x10000, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 9, 4, 1);
    return func_00206958(arg0, (s64)0x8000 << 29);
}
