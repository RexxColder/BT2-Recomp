#include "common.h"

s32 func_00218128(s32 a0, s32 a1);
void func_001FA360(f32 farg0, s32 a0);
s32 BtlObjXf_Update(s32 a0);
void func_001F9FB0(s32 a0, s32 a1);
f32 func_001FA318(s32 a0);
void func_002113C0(s32 a0, s32 a1, s32 a2, s32 a3);
f32 func_00240D50(s32 a0, s32 a1);
void func_00215068(f32 farg0, f32 farg1, s32 a0, s32 a1, s32 a2);
void func_00215E88(f32 farg0, s32 a0, s32 a1);
void func_00216208(f32 farg0, f32 farg1, s32 a0);
void func_00216678(s32 a0);
s32 func_00211310(s32 a0, s32 a1, s32 a2);
void *BtlMember_GetActiveGauge(s32 a0);
extern f32 D_003866A8;
extern f32 D_003866AC;
extern f32 D_003866B0;
extern f32 D_003866B4;
extern f32 D_003866B8;
extern f32 D_003866BC;

void func_0022D980(s32 arg0) {
    f32 f20;
    f32 f21;
    f32 f22;

    f21 = 0.0f;
    f22 = 0.0f;
    if (func_00218128(arg0, 2) != 0) {
        func_001FA360(D_003866A8, arg0);
    }
    if (BtlObjXf_Update(arg0) == 0x27) {
        func_001F9FB0(arg0, 0);
        if (func_001FA318(arg0) < 0.5f) {
            func_002113C0(arg0, 3, 1, 1);
        }
        if (!(func_001FA318(arg0) < D_003866AC)) {
            f21 = f22;
            f22 = D_003866B4;
        } else {
            f21 = func_00240D50(arg0, 0xA);
            f22 = D_003866B0;
        }
    }
    f20 = D_003866B8;
    func_00215068(D_003866BC, f20, arg0, 1, 0xC);
    func_00215E88(f20, arg0, 2);
    func_00216208(f21, f22, arg0);
    func_00216678(arg0);
    func_002113C0(arg0, 5, 1, 1);
    func_002113C0(arg0, 9, 0x200, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (*(u8 *)((u8 *)BtlMember_GetActiveGauge(arg0) + 0x29) != 0) {
        func_002113C0(arg0, 6, 8, 1);
    }
}
