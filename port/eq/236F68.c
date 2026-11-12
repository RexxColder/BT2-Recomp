#include "common.h"

void func_001F9FB0(s32 arg0, s32 arg1);
void func_00215068(f32 farg0, f32 farg1, s32 arg0, s32 arg1, s32 arg2);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(f32 farg0, f32 farg1, s32 arg0);
void func_00216890(f32 farg0, f32 farg1, s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206958(s32 arg0, s64 arg1);
extern f32 D_00386A1C;
extern f32 D_00386A20;
extern f32 D_00386A24;
extern f32 D_00386A28;
extern f32 D_00386A2C;

void func_00236F68(s32 arg0) {
    f32 f20;

    f20 = D_00386A1C;
    func_001F9FB0(arg0, 0);
    func_00215068(D_00386A20, f20, arg0, 5, 0xC);
    func_00215E88(f20, arg0, 6);
    func_00216208(0.0f, D_00386A24, arg0);
    func_00216890(D_00386A28, D_00386A2C, arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
}
