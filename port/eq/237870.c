#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_00386A5C;
extern f32 D_00386A60;
extern f32 D_00386A64;

s32 func_00237870(s32 arg0) {
    s32 v;

    v = BtlObjXf_Update(arg0);
    if (v == 0xA5) {
        func_001FA0A0(arg0, 0xA7, 1);
        func_002113C0(arg0, 5, 0x20, 1);
    } else if (v == 0x1A1) {
        func_001FA0A0(arg0, 0x1A3, 1);
        func_002113C0(arg0, 5, 0x20, 1);
    } else if ((v == 0xA7) || (v == 0x1A3)) {
        func_001F9FB0(arg0, 0);
    }
    func_00215068(arg0, 5, 0xC, D_00386A5C, 0.5f);
    func_00215E88(arg0, 2, D_00386A60);
    func_00216208(arg0, 0.0f, D_00386A64);
    func_00216678(arg0);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 1, 0x40, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 3, 0xE, 1);
    return func_002113C0(arg0, 1, 0x800000, 1);
}
