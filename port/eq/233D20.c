#include "common.h"

void func_001F9FB0(void *arg0, s32 arg1);
void func_00206958(void *arg0, s64 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212320(void *arg0);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(void *arg0, s32 arg1, f32 farg0);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);
s32 func_002411E0(void *arg0, s32 arg1);
extern f32 D_00386930;
extern f32 D_00386934;
extern f32 D_00386938;

void func_00233D20(void *arg0) {
    f32 temp_f20;
    s32 temp_s0;

    temp_f20 = D_00386930;
    temp_s0 = func_00212320(arg0);
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xC, D_00386934, temp_f20);
    func_00215E88(arg0, 6, temp_f20);
    func_00216208(arg0, 0.0f, D_00386938);
    func_00216678(arg0);
    func_002113C0(arg0, 1, 0x40, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    func_002113C0(arg0, 3, 0xE, 1);
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 9, 0x200000, 1);
    func_002113C0(arg0, 1, 0x800000, 1);
    if (!(func_002411E0(arg0, temp_s0) & 0x10)) {
        func_00206958(arg0, 0x8000);
    }
    if ((func_00211310(arg0, 0, 2) == 0) && (func_00211310(arg0, 0, 4) == 0)) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (*(u8 *)((u8 *)arg0 + 0xAB9) != 0) {
        func_002113C0(arg0, 5, 0x20, 1);
        func_002113C0(arg0, 1, 0x2000, 1);
    }
}
