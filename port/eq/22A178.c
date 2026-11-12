#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
f32 func_00240D50(s32 arg0, s32 arg1);
void func_001F9D78(s32 arg0, s32 arg1);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
void func_001FA110(s32 arg0, s32 arg1);
s32 func_00217BD0(s32 arg0);
void func_00206958(s32 arg0, s64 arg1);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216678(s32 arg0);
extern f32 D_00386494;
extern f32 D_00386498;
extern f32 D_0038649C;
extern f32 D_003864A0;

void func_0022A178(s32 arg0) {
    s32 var_s1;
    s32 var_s2;
    f32 var_f20;
    f32 var_f21;
    s32 temp_v0;

    var_s1 = 9;
    var_s2 = 1;
    var_f20 = func_00240D50(arg0, 0xF);
    var_f21 = D_00386494;
    temp_v0 = BtlObjXf_Update(arg0);
    if (temp_v0 == 48) {
        func_001FA110(arg0, 0);
        if (func_00217BD0(arg0) != 0) {
            func_001F9D78(arg0, 0x31);
        }
    } else if (temp_v0 == 49) {
        var_f20 = 0.0f;
        func_001F9FB0(arg0, 0);
        var_f21 = D_00386498;
        var_s2 = 5;
        var_s1 = 0xD;
    } else if (temp_v0 == 47) {
        func_001FA0A0(arg0, 0x30, 0);
    }
    func_00215068(D_0038649C, 1.0f, arg0, var_s2, var_s1);
    func_00215E88(D_003864A0, arg0, 3);
    func_00216208(var_f20, var_f21, arg0);
    func_00216678(arg0);
    func_00206958(arg0, 0x1000);
    func_00206958(arg0, (s64)0x8000 << 28);
}
