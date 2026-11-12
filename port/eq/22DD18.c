#include "common.h"

u8 *BtlMember_GetActiveGauge(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
void func_001FA360(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00218128(s32 arg0, s32 arg1);
extern f32 D_003866CC;
extern f32 D_003866D0;
extern f32 D_003866D4;
extern f32 D_003866D8;
extern f32 D_003866DC;

void func_0022DD18(s32 arg0) {
    f32 f20;

    if (func_00218128(arg0, 2) != 0) {
        func_001FA360(D_003866CC, arg0);
    }
    func_001F9FB0(arg0, 0);
    if (func_001FA318(arg0) < D_003866D0) {
        func_002113C0(arg0, 3, 1, 1);
    }
    f20 = D_003866D4;
    func_00215068(arg0, 1, 0xC, D_003866D8, f20);
    func_00215E88(arg0, 2, f20);
    func_00216208(arg0, 0.0f, D_003866DC);
    func_00216678(arg0);
    func_002113C0(arg0, 5, 1, 1);
    func_002113C0(arg0, 9, 0x200, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (*(u8 *)(BtlMember_GetActiveGauge(arg0) + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
}
