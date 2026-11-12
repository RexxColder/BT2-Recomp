#include "common.h"

s32 BtlObjXf_Update(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001FA110(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(f32 farg0, s32 arg1, s32 arg2, s32 arg3, f32 farg1);
void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
void func_00216208(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
extern f32 D_00386198;
extern f32 D_0038619C;
extern f32 D_003861A0;

void func_00224DE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1) {
    f32 temp_f20;
    s32 temp_v0;

    temp_v0 = BtlObjXf_Update(arg0, arg1, arg2, arg3, farg0, farg1);
    switch (temp_v0) {
    case 0x199:
        func_001FA0A0(arg0, 0x19A, 0, 0x19A);
        break;
    case 0x19A:
        func_001FA110(arg0, 0, 0, 0x19A);
        break;
    }
    temp_f20 = D_00386198;
    func_00215068(D_0038619C, arg0, 5, 0xC, temp_f20);
    func_00215E88(temp_f20, arg0, 7);
    func_00216208(arg0, 0, 0.0f, D_003861A0);
    func_00216678(arg0);
}
