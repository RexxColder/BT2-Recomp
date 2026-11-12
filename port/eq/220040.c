#include "common.h"

s32 BtlChar_GetPos(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
f32 func_0029DFD0(s32 arg0);
extern f32 D_00385EF8;
extern f32 D_00385EFC;
extern f32 D_00385F00;
extern f32 D_00385F04;

void func_00220040(s32 arg0) {
    f32 f20;

    f20 = D_00385EF8;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xC, D_00385EFC, f20);
    if (func_00218838(arg0, 0) != 0) {
        func_00215E88(f20, arg0, 2);
    } else {
        func_00215E88(f20, arg0, 4);
    }
    func_00216208(arg0, 0.0f, D_00385F00);
    func_00216678(arg0);
    func_002113C0(arg0, 9, 0x200, 1);
    func_002113C0(arg0, 6, 4, 1);
    func_002113C0(arg0, 6, 8, 1);
    func_002113C0(arg0, 3, 0x2000, 1);
    func_002113C0(arg0, 3, 0x4000, 1);
    func_002113C0(arg0, 1, 0x400000, 1);
    if (func_00211310(arg0, 0, 4) != 0) {
        if (D_00385F04 < func_0029DFD0(BtlChar_GetPos(arg0) + 0x50)) {
            func_00206958(arg0, 0x80000000LL);
        }
    }
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (func_00211310(arg0, 0, 4) != 0) {
        func_002113C0(arg0, 0, 2, 0);
    }
}
