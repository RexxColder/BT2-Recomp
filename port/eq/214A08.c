#include "common.h"

extern void *memset(void *dst, int c, u32 n);
extern u8 *D_003876A0;
extern u8 D_003438E0[];
s32 func_00217488();
s32 func_0021FB00();
void func_002174F0();
void func_0021FE78();
void func_00213660();
void func_001FCD80();
s32 func_002113C0();
s32 func_00211310();
void func_0021FAA8();
void BattleSide_SetChara();
void func_0025F058(u8 *arg0, f32 farg0);
void func_0021FAF8();
void func_00217128();
void func_00213B10();
void func_00213D98();
void func_002142A8();
void func_00214128();
s32 func_0020AB00();
s32 func_00203310();
s32 func_0023F440();
f32 func_001FA370();
void func_001FA380(u8 *arg0, f32 arg1);
s32 BtlPad_Test48();
s32 BtlPad_Test4C();
void func_00213738();
void func_0025F5F8();
s32 func_00203118();
void func_00203280();
void func_002031E0();
void func_001F9C10();
void func_001F9C90();
u8 *BtlChar_GetPos();
void func_00312638();

typedef s32 (*Fn1)(u8 *);
typedef s32 (*Fn2)(u8 *, s32);

s32 func_00214A08(u8 *arg0) {
    s32 sp[2];
    s32 s3, s0, v0, v1, a1;
    u8 *s0p, *v;
    s32 r;
    int flow;

    sp[0] = -1;
    s3 = func_00217488(arg0);
    *(s32 *)(arg0 + 0x8E8) = *(s32 *)(arg0 + 0x8E0);
    v1 = func_0021FB00(arg0);
    sp[0] = v1;
    s0 = s3 << 4;
    flow = 1;
    if (v1 == -1) {
        Fn1 cb = *(Fn1 *)(D_003438E0 + 8 + s0);
        if (cb) {
            v1 = cb(arg0);
            sp[0] = v1;
        }
        if (v1 == -1) flow = 0;
    }
    if (flow) {
        Fn2 cb2;
        Fn1 cb3;
        sp[1] = -1;
        cb2 = *(Fn2 *)(D_003438E0 + 0xC + s0);
        if (cb2) {
            cb2(arg0, sp[0]);
            v1 = sp[0];
        }
        func_002174F0(v1, sp, sp + 1);
        func_0021FE78(arg0, sp[0]);
        func_00213660(arg0);
        func_001FCD80(arg0);
        *(s32 *)(arg0 + 0xC08) = -1;
        v1 = *(s32 *)(arg0 + 0x1010);
        *(s32 *)(arg0 + 0xC0C) = sp[1];
        *(s32 *)(arg0 + 0xC00) = sp[0];
        *(s32 *)(arg0 + 0xC10 + v1 * 4) = s3;
        v0 = *(s32 *)(arg0 + 0x1010) + 1;
        *(s32 *)(arg0 + 0x1010) = v0;
        if (v0 >= 0x100) *(s32 *)(arg0 + 0x1010) = 0;
        memset(arg0 + 0x8C0, 0, 0x20);
        *(s32 *)(arg0 + 0x9B0) = 0;
        *(s32 *)(arg0 + 0xA1C) = 0;
        *(s32 *)(arg0 + 0x9C0) = 0;
        *(s32 *)(arg0 + 0xA44) = 0;
        *(s32 *)(arg0 + 0xA48) = 0;
        *(s32 *)(arg0 + 0xA4C) = 0;
        func_002113C0(arg0, 0, 0x80, 1);
        func_002113C0(arg0, 5, 6, 0);
        func_002113C0(arg0, 2, 0x70, 0);
        func_0021FAA8(arg0);
        cb3 = *(Fn1 *)(D_003438E0 + func_00217488(arg0) * 16);
        if (cb3) {
            cb3 = *(Fn1 *)(D_003438E0 + func_00217488(arg0) * 16);
            cb3(arg0);
        }
    } else {
        if (func_00211310(arg0, 2, 0x10)) {
            func_00213660(arg0);
            a1 = *(s32 *)(arg0 + 0x8E4);
            if (a1 >= 0) BattleSide_SetChara(arg0, a1);
        } else if (func_00211310(arg0, 2, 0x20)) {
            a1 = *(s32 *)(arg0 + 0x8E4);
            if (a1 >= 0) func_001F9C10(arg0, a1);
        } else if (func_00211310(arg0, 2, 0x40)) {
            if (*(s32 *)(arg0 + 0x8EC) >= 0) func_001F9C90(arg0);
        }
        func_002113C0(arg0, 0, 0x80, 0);
    }
    if (func_00211310(arg0, 2, 8)) {
        func_0025F058(*(u8 **)(arg0 + 0x1530), *(f32 *)(arg0 + 0x8F0));
        func_002113C0(arg0, 2, 8, 0);
        *(s32 *)(arg0 + 0x8F0) = 0;
        v = *(u8 **)(arg0 + 0x1530);
        *(f32 *)(v + 0xBEC) = *(f32 *)(v + 0xBEC) - *(f32 *)(v + 0xBF0);
        v = *(u8 **)(arg0 + 0x1530);
        if (*(f32 *)(v + 0xBEC) < 0.0f) *(f32 *)(v + 0xBEC) = 0.0f;
    }
    *(u8 *)(arg0 + 0x1014) = 0;
    func_002113C0(arg0, 1, 0x1C000, 0);
    func_0021FAF8(arg0);
    {
        Fn1 cb4 = *(Fn1 *)(D_003438E0 + 4 + func_00217488(arg0) * 16);
        if (cb4) {
            cb4 = *(Fn1 *)(D_003438E0 + 4 + func_00217488(arg0) * 16);
            cb4(arg0);
        }
    }
    *(s32 *)(arg0 + 0x8CC) = *(s32 *)(arg0 + 0x8CC) + 1;
    func_00217128(arg0);
    func_00213B10(arg0);
    func_00213D98(arg0);
    if (func_00211310(arg0, 5, 0x20)) {
        s0p = BtlChar_GetPos(arg0);
        v = BtlChar_GetPos(arg0);
        func_00312638(s0p, v, arg0 + 0xBE0);
    }
    if (!func_00211310(arg0, 5, 2)) func_002113C0(arg0, 5, 8, 0);
    func_002142A8(arg0);
    func_00214128(arg0);
    if (func_0020AB00(*(u8 **)(arg0 + 0x1534))) {
        v = *(u8 **)(arg0 + 0x1530);
        if (*(u32 *)(v + 0xE54) & 0x80) {
            func_00203310(arg0, 0x12C, 0);
            v = *(u8 **)(arg0 + 0x1530);
        }
        if (*(u32 *)(v + 0xE54) & 0x100) {
            func_00203310(arg0, 0x3E8, 0);
            v = *(u8 **)(arg0 + 0x1530);
        }
        if (*(u32 *)(v + 0xE54) & 0x200) func_00203310(arg0, 0x640, 0);
    }
    if (func_00211310(arg0, 0xC, 0x40000)) {
        func_002113C0(arg0, 0xC, 0x8000, 0);
        func_002113C0(arg0, 0xC, 0x10000, 0);
        func_002113C0(arg0, 0xC, 0x20000, 0);
        func_002113C0(arg0, 0xC, 0x40000, 0);
        func_002113C0(arg0, 0xC, 0x80000, 1);
    } else {
        func_002113C0(arg0, 0xC, 0x80000, 0);
    }
    if (func_00211310(arg0, 0xA, 0x20)) {
        f32 fv;
        if (func_0023F440(arg0) == 4) {
            fv = func_001FA370(arg0);
            func_001FA380(arg0, fv + fv);
        } else {
            fv = func_001FA370(arg0);
            func_001FA380(arg0, fv * 3.0f);
        }
    }
    a1 = *(s32 *)(arg0 + 0x9C0);
    if (a1 >= 0) {
        if (!BtlPad_Test48(arg0, a1)) *(s32 *)(arg0 + 0x9C0) = -1;
    }
    func_00213738(arg0);
    func_0025F5F8(*(u8 **)(arg0 + 0x1530));
    r = *(s32 *)(D_003876A0 + 0xD8) & 1;
    if (r) return r;
    r = func_00211310(arg0, 9, 0x8000000);
    if (r) return r;
    r = func_00203118(arg0) < 3;
    if (r) return r;
    if (BtlPad_Test48(arg0, 7)) {
        if (BtlPad_Test4C(arg0, 0xE)) {
            func_00203280(arg0);
            func_002113C0(arg0, 0xF, 0x200000, 1);
        }
    }
    r = BtlPad_Test48(arg0, 7);
    if (r) {
        r = BtlPad_Test4C(arg0, 0xF);
        if (r) {
            func_002031E0(arg0);
            return func_002113C0(arg0, 0xF, 0x400000, 1);
        }
    }
    return r;
}
