#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
s32 func_001F9FB0(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217BD0(s32 arg0);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00385D14;
extern f32 D_00385D18;
extern f32 D_00385D1C;

void func_0021C2E8(s32 arg0) {
    if (BtlObjXf_Update(arg0) == 0x79) {
        func_001F9FB0(arg0, 0);
        if (func_00217BD0(arg0) != 0) {
            *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = 0;
        }
        if (func_00211310(arg0, 4, 0x80) != 0) {
            *(s32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = 0;
        }
    }
    func_00215068(arg0, 5, 0xD, D_00385D18, D_00385D14);
    func_00215E88(D_00385D14, arg0, 3);
    func_00216208(arg0, 0.0f, D_00385D1C);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
}
