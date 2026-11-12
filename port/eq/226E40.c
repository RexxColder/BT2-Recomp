#include "common.h"

#define FW(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern f32 D_003862C0;
extern f32 D_003862C4;
extern f32 D_003862C8;
extern f32 D_003862CC;
extern f32 D_003862D0;
extern f32 D_003862D4;
extern f32 D_003862D8;
extern f32 D_003862DC;
extern f32 D_003862E0;
extern f32 D_003862E4;
extern f32 D_003862E8;
extern f32 D_003862EC;
extern f32 D_003862F0;
extern f32 D_003862F4;

f32 sinf(f32 x);
f32 cosf(f32 x);
s32 BtlObjXf_Update(void *arg0);
void *BtlChar_GetPos(void *arg0);
void BtlAnim_SetBlend(f32 farg0, void *arg0);
f32 BtlOpp_GetPitchAdjusted(void *arg0);
s32 func_001F9FB0(void *arg0, s32 arg1);
s32 func_001FA0A0(void *arg0, s32 arg1, s32 arg2);
f32 func_001FA318(void *arg0);
void func_00206958(void *arg0, s64 arg1);
void func_0020D7E8(f32 farg0, void *arg0, f32 farg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00215068(f32 farg0, f32 farg1, void *arg2, s32 arg3, s32 arg4);
void func_00215550(f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, void *arg7, s32 arg8);
void func_00215E88(f32 farg0, void *arg1, s32 arg2);
void func_00216208(f32 farg0, void *arg1, f32 farg1);
void func_00216678(void *arg0);
s32 func_00217BD0(void *arg0);
void func_002181F0(void *arg0, f32 farg0);
f32 func_00240D50(void *arg0, s32 arg1);
f32 func_00240ED8(void *arg0, s32 arg1);
f32 func_00240F18(void *arg0, s32 arg1);

void func_00226E40(void *arg0) {
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 t15;
    f32 var;
    s32 v;
    s32 a1;
    void *p;

    f23 = D_003862C0;
    if (func_00211310(arg0, 0, 0x100) != 0) {
        a1 = 5;
    } else {
        a1 = 4;
    }
    f21 = func_00240D50(arg0, a1);
    f22 = f21;
    v = BtlObjXf_Update(arg0);
    if (v == 0x83) {
        goto c83;
    }
    if (v < 0x84) {
        if (v == 0x84) {
            goto c84;
        }
        if (v == 0x19) {
            goto c19;
        }
        goto tail;
    }
    if (v == 0x85) {
        goto c85;
    }
    goto tail;

c83:
    if (func_001FA0A0(arg0, 0x19, 0) != 0) {
        BtlAnim_SetBlend(D_003862C4, arg0);
    }
    if (func_00211310(arg0, 0, 1) != 0 && (W(arg0, 0x8DC) & 1)) {
        p = BtlChar_GetPos(arg0);
        FW(arg0, 0xA00) = FW(p, 0x20);
        p = BtlChar_GetPos(arg0);
        FW(arg0, 0xA04) = FW(p, 0x24);
        p = BtlChar_GetPos(arg0);
        var = FW(p, 0x28);
    } else {
        p = BtlChar_GetPos(arg0);
        FW(arg0, 0xA00) = sinf(FW(p, 0xB4));
        W(arg0, 0xA04) = 0;
        p = BtlChar_GetPos(arg0);
        var = cosf(FW(p, 0xB4));
    }
    goto c_store;

c84:
    if (func_001FA0A0(arg0, 0x19, 0) != 0) {
        BtlAnim_SetBlend(D_003862C8, arg0);
    }
    f20 = D_003862CC;
    p = BtlChar_GetPos(arg0);
    FW(arg0, 0xA00) = sinf(FW(p, 0xB4) + f20);
    W(arg0, 0xA04) = 0;
    p = BtlChar_GetPos(arg0);
    var = cosf(FW(p, 0xB4) + f20);
    goto c_store;

c85:
    if (func_001FA0A0(arg0, 0x19, 0) != 0) {
        BtlAnim_SetBlend(D_003862D0, arg0);
    }
    f20 = D_003862D4;
    p = BtlChar_GetPos(arg0);
    FW(arg0, 0xA00) = sinf(FW(p, 0xB4) - f20);
    W(arg0, 0xA04) = 0;
    p = BtlChar_GetPos(arg0);
    var = cosf(FW(p, 0xB4) - f20);
    goto c_store;

c19:
    func_001F9FB0(arg0, 0);
    f21 = 0.0f;
    f23 = D_003862D8;
    if (func_00217BD0(arg0) != 0) {
        p = BtlChar_GetPos(arg0);
        FW(p, 0xC0) = 0.0f;
    }
    goto tail;

c_store:
    W(arg0, 0xA0C) = 0;
    FW(arg0, 0xA08) = var;
    func_00206958(arg0, 0x1000);
    goto tail;

tail:
    if (W(arg0, 0x8DC) & 1) {
        if (func_00211310(arg0, 0, 1) != 0) {
            f20 = func_00240ED8(arg0, 0);
            t15 = func_00240F18(arg0, 0);
            func_00215550(f22, f20, 0.0f, t15, 0.0f, D_003862DC, D_003862E0, arg0, 1);
        } else {
            func_00215068(D_003862E4, D_003862E8, arg0, 5, 0xC);
        }
    } else {
        func_00215068(D_003862EC, D_003862F0, arg0, 5, 0xC);
    }
    func_00215E88(D_003862F4, arg0, 3);
    func_00216208(f21, arg0, f23);
    func_00216678(arg0);
    func_0020D7E8(20.0f, arg0, 50.0f);
    func_002113C0(arg0, 0xD, 8, 1);
    if (func_00211310(arg0, 0, 0x100) != 0) {
        func_002113C0(arg0, 0, 2, 1);
    }
    if (W(arg0, 0x8DC) & 1) {
        func_002113C0(arg0, 9, 0x200, 1);
    }
    if (func_00211310(arg0, 0, 1) == 0) {
        return;
    }
    if (!(W(arg0, 0x8DC) & 1)) {
        return;
    }

    f21 = 0.0f;
    v = BtlObjXf_Update(arg0);
    if (v == 0x19) {
        f21 = 1.0f - func_001FA318(arg0);
    } else if (v == 0x83) {
        f21 = 1.0f;
    }
    f20 = BtlOpp_GetPitchAdjusted(arg0);
    if (0.0f < f20) {
        f20 = f20 * 0.5f;
    }
    p = BtlChar_GetPos(arg0);
    FW(p, 0xD4) = f20 * f21;
    func_002181F0(arg0, 10.0f);
}
