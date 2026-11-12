#include "common.h"

void func_001F9FB0(void *arg0, s32 arg1);
void func_001FA110(void *arg0, s32 arg1);
void func_00206958(void *arg0, s64 arg1);
s32 func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(void *arg0, s32 arg1, f32 farg0);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);
extern f32 D_00386944;
extern f32 D_00386948;
extern f32 D_0038694C;

void func_002340F0(void *arg0) {
    f32 temp_f20;

    if (*(s32 *)((u8 *)arg0 + 0x8DC) & 1) {
        func_001FA110(arg0, 0);
    } else {
        func_001F9FB0(arg0, 0);
    }
    temp_f20 = D_00386944;
    func_00215068(arg0, 5, 0xC, D_00386948, temp_f20);
    func_00215E88(arg0, 6, temp_f20);
    func_00216208(arg0, 0.0f, D_0038694C);
    func_00216678(arg0);
    func_002113C0(arg0, 1, 0x40, 1);
    func_002113C0(arg0, 3, 0x800, 1);
    if (*(s32 *)((u8 *)arg0 + 0x8DC) & 1) {
        func_002113C0(arg0, 3, 0xA, 1);
    } else {
        func_002113C0(arg0, 3, 0xE, 1);
    }
    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    func_002113C0(arg0, 0xD, 1, 1);
    func_002113C0(arg0, 9, 0x200000, 1);
    func_00206958(arg0, (s64)0x8000 << 29);
    func_002113C0(arg0, 1, 0x800000, 1);
    func_002113C0(arg0, 6, 4, 1);
    if (*(u8 *)((u8 *)arg0 + 0xAB9) != 0) {
        func_002113C0(arg0, 6, 2, 1);
        func_002113C0(arg0, 1, 0x1000, 1);
    }
}
