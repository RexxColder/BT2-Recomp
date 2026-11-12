#include "common.h"

void BtlChar_SetVibration(f32 farg0, f32 farg1, s32 arg2);
void func_001F9FB0(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(f32 farg0, s32 arg1, s32 arg2, s32 arg3, f32 farg1);
void func_00215E88(f32 farg0, s32 arg1, s32 arg2);
void func_00216208(f32 farg0, s32 arg1, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00217488(s32 arg0);
extern f32 D_00385D78;
extern f32 D_00385D7C;
extern f32 D_00385D80;
extern f32 D_00385D84;
extern f32 D_00385D88;

void func_0021CB08(s32 arg0) {
    func_001F9FB0(arg0, 0);
    func_00215068(D_00385D78, arg0, 5, 0xC, 0.5f);
    func_00215E88(D_00385D7C, arg0, 2);
    func_00216208(0.0f, arg0, D_00385D80);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    BtlChar_SetVibration(D_00385D84, D_00385D88, arg0);
    func_002113C0(arg0, 0xD, 8, 1);
    if (func_00217488(arg0) == 0x68) {
        func_002113C0(arg0, 3, 0x8000, 1);
    }
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
}
