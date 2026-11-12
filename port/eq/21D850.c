#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001F9FB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217BD0(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00385DE8;
extern f32 D_00385DEC;
extern f32 D_00385DF0;
extern f32 D_00385DF4;
extern f32 D_00385DF8;

void func_0021D850(s32 arg0) {
    f32 f20;
    f32 f21;
    s32 r;

    r = BtlObjXf_Update(arg0);
    f20 = D_00385DE8;
    f21 = D_00385DEC;
    if (r == 0x53) {
        func_001FA0A0(arg0, 0x55, 0, 0x55);
    } else if (r == 0x55) {
        func_001F9FB0(arg0, 0, 0, 0x55);
        f20 = 0.0f;
        f21 = D_00385DF0;
        if (func_00211310(arg0, 4, 0xC) != 0 && func_00217BD0(arg0) != 0) {
            *(f32 *)((u8 *)BtlChar_GetPos(arg0) + 0xC0) = f20;
        }
    }
    func_00215068(D_00385DF4, 0.5f, arg0, 1, 9);
    func_00215E88(D_00385DF8, arg0, 3);
    func_00216208(arg0, f20, f21);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
}
