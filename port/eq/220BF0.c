#include "common.h"

s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
u8 *BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
void func_001F9D78(s32 arg0, s32 arg1);
void func_001FA110(s32 arg0, s32 arg1, s32 arg2);
void func_00206958(s32 arg0, s64 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
extern f32 D_00385F64;
extern f32 D_00385F68;
extern f32 D_00385F6C;
extern f32 D_00385F70;
extern f32 D_00385F74;

void func_00220BF0(s32 arg0) {
    f32 f20;
    s32 v;

    func_00216678(arg0);
    v = BtlObjXf_Update(arg0);
    switch (v) {
    case 0xEB:
        func_001FA110(arg0, 0, 0xEC);
        if (*(f32 *)(BtlChar_GetPos(arg0) + 0xC4) > 0.0f) {
            func_001F9D78(arg0, 0xEC);
            BtlAnim_SetBlend(arg0, D_00385F64);
        }
        break;
    case 0xEC:
        func_001FA110(arg0, 0, 0xEC);
        break;
    }

    f20 = D_00385F68;
    func_00215068(arg0, 5, 0xC, D_00385F6C, f20);
    if (func_00218838(arg0, 1) != 0) {
        func_00215E88(f20, arg0, 2);
    } else {
        func_00215E88(f20, arg0, 4);
    }
    func_00216208(arg0, D_00385F70, D_00385F74);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
}
