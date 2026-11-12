#include "common.h"

extern f32 D_00386BF4;
extern f32 D_00386BF8;
extern f32 D_00386BFC;

s32 func_00212320(void *arg0);
s32 func_001F9FB0(void *arg0, s32 arg1);
void func_00215068(void *arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(void *arg0, s32 arg1, f32 farg0);
void func_00216208(void *arg0, f32 farg0, f32 farg1);
void func_00216678(void *arg0);
s32 func_00241F80(void *arg0, s32 arg1);
s32 func_00241C50(void *arg0, s32 arg1);
s32 func_001FA1D0(void *arg0, f32 farg0);
f32 func_001FA318(void *arg0);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);

void func_0023B330(u8 *arg0) {
    f32 f20;
    f32 f0;
    f32 f1;
    s32 s1;
    s32 v1;

    s1 = func_00212320(arg0);
    f20 = D_00386BF4;
    func_001F9FB0(arg0, 0);
    func_00215068(arg0, 5, 0xD, D_00386BF8, f20);
    func_00215E88(arg0, 7, f20);
    func_00216208(arg0, 0.0f, D_00386BFC);
    func_00216678(arg0);

    if (func_00241F80(arg0, s1) & 0x01000000) {
        func_002113C0(arg0, 3, 1, 1);
    }
    if (func_00241F80(arg0, s1) & 0x02000000) {
        func_002113C0(arg0, 3, 2, 1);
    }
    if (func_00241F80(arg0, s1) & 0x04000000) {
        func_002113C0(arg0, 3, 4, 1);
    }
    if (func_00241F80(arg0, s1) & 0x08000000) {
        func_002113C0(arg0, 3, 8, 1);
    }
    if (func_00241F80(arg0, s1) & 0x10000000) {
        func_002113C0(arg0, 3, 0x20, 1);
    }

    v1 = func_00241C50(arg0, s1);
    if (v1 == 1) {
        if (func_001FA1D0(arg0, 0.5f) != 0) {
            func_002113C0(arg0, 3, 0x80000, 1);
        }
        func_002113C0(arg0, 9, 0x20000000, 1);
    } else if (v1 == 0xD2) {
        f0 = func_001FA318(arg0);
        f1 = *(f32 *)(arg0 + 0x8D0) + f0;
        *(f32 *)(arg0 + 0xAC4) = f1;
        if (3.0f <= f1) {
            *(f32 *)(arg0 + 0xAC4) = 3.0f;
        }
    }

    func_002113C0(arg0, 0xD, 8, 1);
    func_002113C0(arg0, 0xD, 0x10, 1);
    if (func_00211310(arg0, 0, 2) != 0) {
        return;
    }
    if (func_00211310(arg0, 0, 4) != 0) {
        return;
    }
    func_002113C0(arg0, 0, 2, 1);
}
