#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
void func_001FA110(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_002179A8(s32 arg0, f32 farg0);
s32 func_00217A78(s32 arg0);
s32 func_00212DD8(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00211418(s32 arg0, s32 arg1);
void func_0020FC38(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);

extern f32 D_00386174;
extern f32 D_00386178;
extern f32 D_0038617C;
extern f32 D_00386180;
extern f32 D_00386184;
extern f32 D_00386188;
extern f32 D_0038618C;

void func_00224B30(s32 arg0) {
    s32 var_s1;
    s32 temp_v0;
    f32 temp_f20;

    var_s1 = 0;
    temp_v0 = BtlObjXf_Update(arg0);
    if (temp_v0 == 0x197) {
        func_001FA110(arg0, 0);
        var_s1 = 1;
    } else if (temp_v0 == 0x198) {
        if (func_001FA0A0(arg0, 0x197, 0) != 0) {
            BtlAnim_SetBlend(arg0, D_00386174);
        }
        if (D_00386178 < func_001FA318(arg0)) {
            var_s1 = 1;
        }
    }
    if ((var_s1 != 0) && (func_002179A8(arg0, D_0038617C) != 0)) {
        func_00212DD8(arg0, 0x26);
    }
    if (func_00217A78(arg0) != 0) {
        func_002113C0(arg0, 0, 1, 1);
        func_00215068(arg0, 1, 0xC, D_00386180, 0.0f);
        func_00212DD8(arg0, 0x27);
        func_0020FC38(arg0, 0x2C);
        func_00211418(arg0, 4);
        if (func_00211310(arg0, 0, 0x400) == 0) {
            func_00206958(arg0, 0x20000);
        }
    }
    temp_f20 = D_00386184;
    func_00215068(arg0, 5, 0xC, D_00386188, temp_f20);
    func_00215E88(arg0, 7, temp_f20);
    func_00216208(arg0, 0.0f, D_0038618C);
    func_00216678(arg0);
    func_002113C0(arg0, 1, 0x400, 1);
    func_002113C0(arg0, 1, 0x800, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
