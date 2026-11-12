#include "common.h"

extern f32 D_003861E8;
extern f32 D_003861EC;
extern f32 D_003861F0;
extern f32 D_003861F4;
extern f32 D_003861F8;
extern f32 D_003861FC;
extern f32 D_00386200;
extern f32 D_00386204;

u8 *BtlChar_GetPos(s32 arg0);
s32 BtlObjXf_Update(s32 arg0);
f32 BtlOpp_GetPitchAdjusted(s32 arg0);
void func_001F9FB0(s32 arg0, s32 arg1);
void func_001FA0A0(s32 arg0, s32 arg1, s32 arg2);
f32 func_001FA318(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215550(s32 arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6);
void func_00215E88(f32 farg0, s32 arg0, s32 arg1);
void func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_00216678(s32 arg0);
s32 func_00217BD0(s32 arg0);
void func_002181F0(s32 arg0, f32 farg0);
f32 func_00240D50(s32 arg0, s32 arg1);
f32 func_00240ED8(s32 arg0, s32 arg1);
f32 func_00240F18(s32 arg0, s32 arg1);

void func_002257A0(u8 *arg0) {
    s32 s1;
    s32 a1;
    s32 v;
    u8 *p;
    f32 f0;
    f32 f20;
    f32 f21;
    f32 f22;

    s1 = 0;
    if (func_00211310((s32)arg0, 0, 0x100) != 0) {
        a1 = 5;
    } else {
        a1 = 4;
    }
    f21 = func_00240D50((s32)arg0, a1);
    f22 = f21;
    v = BtlObjXf_Update((s32)arg0);
    if (v == 0x19) {
        func_001F9FB0((s32)arg0, 0);
        if (func_00217BD0((s32)arg0) != 0) {
            p = BtlChar_GetPos((s32)arg0);
            *(s32 *)(p + 0xC0) = 0;
        }
        f21 = 0.0f;
    } else if (v == 0x111) {
        s1 = 1;
        func_001FA0A0((s32)arg0, 0x19, 0);
        func_002113C0((s32)arg0, 3, 0x40, 1);
        func_002113C0((s32)arg0, 3, 0x80, 1);
    }

    if (s1 != 0) {
        if (func_00211310((s32)arg0, 0, 1) != 0) {
            f20 = func_00240ED8((s32)arg0, 0);
            f0 = func_00240F18((s32)arg0, 0);
            func_00215550((s32)arg0, 1, f22, f20, 0.0f, f0, 0.0f, D_003861E8, D_003861EC);
        } else {
            func_00215068((s32)arg0, 5, 0xC, D_003861F0, D_003861F4);
        }
    } else {
        func_00215068((s32)arg0, 5, 0xD, D_003861F8, D_003861FC);
    }
    func_00215E88(D_00386200, (s32)arg0, 3);
    func_00216208((s32)arg0, f21, D_00386204);
    func_00216678((s32)arg0);
    func_002113C0((s32)arg0, 9, 0x200, 1);

    if (func_00211310((s32)arg0, 0, 1) == 0) {
        return;
    }
    if (func_00211310((s32)arg0, 0, 2) == 0) {
        return;
    }

    f21 = 0.0f;
    v = BtlObjXf_Update((s32)arg0);
    if (v == 0x19) {
        f21 = 1.0f - func_001FA318((s32)arg0);
    } else if (v == 0x111) {
        f21 = 1.0f;
    }
    f20 = BtlOpp_GetPitchAdjusted((s32)arg0);
    if (0.0f < f20) {
        f20 = f20 * 0.5f;
    }
    p = BtlChar_GetPos((s32)arg0);
    f0 = f20 * f21;
    *(f32 *)(p + 0xD4) = f0;
    func_002181F0((s32)arg0, 10.0f);
}
