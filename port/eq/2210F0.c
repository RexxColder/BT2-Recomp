#include "common.h"

s32 BtlMember_IsHealthEmpty_2127F8(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
void func_001F9FB0(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
void func_001FA360(s32 arg0, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00212878(void);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00218838(s32 arg0, s32 arg1);
extern f32 D_00385F94;
extern f32 D_00385F98;
extern f32 D_00385F9C;
extern f32 D_00385FA0;
extern f32 D_00385FA4;

void func_002210F0(u8 *arg0) {
    f32 f20;
    s32 v0;

    if (BtlMember_IsHealthEmpty_2127F8((s32)arg0) == 0) {
        if (BtlPad_Test4C((s32)arg0, 0x18) != 0) {
            func_001FA360((s32)arg0, 4.0f);
        } else if (D_00385F94 < func_001FA318((s32)arg0)) {
            f32 h = *(f32 *)(arg0 + 0xB58);
            f32 x = (1.0f - h) * 0.5f + 0.5f;
            func_001FA360((s32)arg0, x + x);
        }
    }
    v0 = BtlObjXf_Update((s32)arg0);
    if (v0 == 0xED) {
        func_001FA0A0((s32)arg0, 0xEE, 0);
    } else if (v0 == 0xEE) {
        func_001F9FB0((s32)arg0, 0);
    }
    f20 = D_00385F98;
    func_00215068((s32)arg0, 5, 0xC, D_00385F9C, f20);
    if (func_00218838((s32)arg0, 1) != 0) {
        func_00215E88(f20, (s32)arg0, 2);
    } else {
        func_00215E88(f20, (s32)arg0, 4);
    }
    func_00216208((s32)arg0, D_00385FA0, D_00385FA4);
    func_00216678((s32)arg0);
    func_002113C0((s32)arg0, 6, 4, 1);
    func_002113C0((s32)arg0, 6, 8, 1);
    func_002113C0((s32)arg0, 0xF, 1, 1);
    if (func_00211310((s32)arg0, 0, 0x100) != 0) {
        func_002113C0((s32)arg0, 0, 2, 1);
    }
    if (func_00212878() != 0) {
        if (func_00211310((s32)arg0, 0, 0x40) != 0) {
            func_002113C0((s32)arg0, 0, 2, 1);
        }
    }
}
