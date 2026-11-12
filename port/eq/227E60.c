#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 BattleSide_GetStartChara(s32 arg0);
void BtlAnim_SetBlend(s32 arg0, f32 farg0);
void func_001F9D78(s32 arg0, s32 arg1);
void func_001FA110(s32 arg0, s32 arg1);
void func_00215068(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1);
void func_00215E88(s32 arg0, s32 arg1, f32 farg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00211328(s32 arg0, s32 arg1, s32 arg2);
s32 func_00216208(s32 arg0, f32 farg0, f32 farg1);
void func_002166C0(s32 arg0);
void func_00216678(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00217BD0(s32 arg0);
s32 BtlChar_GetPos(s32 arg0);
s32 BtlMember_GetActiveGauge(s32 arg0);
extern u8 D_0038636C[] __attribute__((section(".data")));
extern u8 D_00386370[] __attribute__((section(".data")));
extern u8 D_00386374[] __attribute__((section(".data")));
extern u8 D_00386378[] __attribute__((section(".data")));
extern u8 D_0038637C[] __attribute__((section(".data")));
extern u8 D_00386380[] __attribute__((section(".data")));
extern u8 D_00386384[] __attribute__((section(".data")));
extern u8 D_00386388[] __attribute__((section(".data")));

/* 0x00227E60: battle character setup (blend, anim flags, 2113C0 calls). */
s32 func_00227E60(s32 a0) {
    s32 s1 = a0;
    s32 prev;
    s32 r;
    s32 v;
    f32 f20;
    f32 f13;

    prev = BtlObjXf_Update(s1);
    r = BattleSide_GetStartChara(s1);
    if (prev != r) {
        BtlAnim_SetBlend(s1, *(f32 *)D_0038636C);
        r = BattleSide_GetStartChara(s1);
        func_001F9D78(s1, r);
    }

    f20 = *(f32 *)D_00386370;
    func_001FA110(s1, 0);
    func_00215068(s1, 5, 0xC, *(f32 *)D_00386374, f20);
    func_00215E88(s1, 7, f20);
    if (func_00211310(s1, 0, 2) != 0) {
        f13 = *(f32 *)D_00386380;
    } else {
        if (func_00211310(s1, 1, 4) != 0) {
            f13 = *(f32 *)D_00386378;
        } else {
            f13 = *(f32 *)D_0038637C;
        }
    }
    func_00216208(s1, 0.0f, f13);
    v = BtlObjXf_Update(s1);
    if (v == 0x1A4) {
        func_002166C0(s1);
    } else {
        func_00216678(s1, 9);
    }
    func_002113C0(s1, 9, 0x80000, 1);
    func_002113C0(s1, 1, 0x10000, 1);
    if (func_00217BD0(s1) != 0) {
        v = BtlChar_GetPos(s1);
        *(s32 *)(v + 0xC0) = 0;
    }

    if (func_00211310(s1, 0, 0x100) != 0
        && func_00211328(s1, 0, 0x100) == 0
        && func_00211310(s1, 0, 4) == 0
        && func_00211310(s1, 0, 2) == 0) {
        func_002113C0(s1, 0, 2, 1);
        BtlAnim_SetBlend(s1, *(f32 *)D_00386384);
        r = BattleSide_GetStartChara(s1);
        func_001F9D78(s1, r);
    }

    if (func_00211310(s1, 0, 2) != 0 && func_00211310(s1, 0, 4) != 0) {
        func_002113C0(s1, 0, 2, 0);
        BtlAnim_SetBlend(s1, *(f32 *)D_00386388);
        r = BattleSide_GetStartChara(s1);
        func_001F9D78(s1, r);
    }

    func_002113C0(s1, 9, 0x40, 1);
    func_002113C0(s1, 1, 0x400, 1);
    func_002113C0(s1, 1, 0x400000, 1);
    v = BtlMember_GetActiveGauge(s1);
    if (*(u8 *)(v + 0x29) != 0) {
        return func_002113C0(s1, 6, 8, 1);
    }
    return v;
}
