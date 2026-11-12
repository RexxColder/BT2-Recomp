#include "common.h"

extern u8 *D_00387930;
extern u8 *D_00387A40;
extern u8 *D_003876A0;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
extern f32 D_00385780;

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_001F5958(u8 *arg0);
u8 *func_00202E60(u8 *arg0, s32 arg1);
u8 *func_00202DA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00206EA0(u8 *arg0);
void func_00207340(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00211270(void);
u8 *func_00211288(s32 arg0);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00211D80(u8 *arg0, s32 arg1);
void func_002128D8(f32 farg0);
f32 BtlUtil_WrapAngle(f32 farg0);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
s32 func_0023F960(u8 *arg0);
s32 func_0023F9B0(u8 *arg0);

void func_001F5A98(void) {
    s32 s5;
    s32 s6;
    s32 s7;
    s32 n;
    s32 c1;
    s32 t;
    s32 prod;
    u8 *p;
    u8 *a;
    u8 *c;

    *(s32 *)(D_00387930 + 0x8) = 0;
    *(s32 *)(D_00387930 + 0xC) = 0;
    *(s32 *)(D_00387930 + 0x10) = 0;
    *(s32 *)(D_00387930 + 0x20) = 0;
    *(s32 *)(D_00387930 + 0x24) = 0;
    memset(D_00387930 + 0x30, 0, 0x40);

    s5 = 0;
    n = func_00211270();
    while (s5 < n) {
        p = func_00211288(s5);
        s5 += 1;
        if (p[0x1434] != 0) {
            func_00206EA0(p);
        }
        n = func_00211270();
    }

    s5 = 0;
    s6 = 0;
    s7 = 0;
    memset(*(u8 **)D_00387930, 0, *(s32 *)(D_00387930 + 4) * 0x1550);
    func_002128D8(0.5f);

    while (s5 < func_00211270()) {
        p = func_00211288(s5);
        t = s5 * 0x18580;
        *(s32 *)(p + 0x152C) = *(s32 *)D_00387A40 + t;
        *(s32 *)(p + 0x1534) = s5;
        *(s32 *)(p + 0x1538) = s5;
        *(s32 *)(p + 0x1530) = *(s32 *)D_00387A40 + t;
        *(s32 *)(p + 0x153C) = s5;
        func_00207340(p, s5, t);
        func_00211D80(p, 0);
        *(f32 *)(p + 0x150) = BtlUtil_WrapAngle(*(f32 *)(p + 0x150) + D_00385780);

        if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
            *(s32 *)(p + 0x204) = *(s32 *)(D_003876A4 + s7 + 0x468);
            p[0x208] = (*(s32 *)(D_003876A4 + s7 + 0x46C) == 0);
        } else {
            *(s32 *)(p + 0x204) = *(s32 *)(D_00387F2C + 0x1094);
            p[0x208] = (*(s32 *)(D_00387F2C + 0x1098) == 0);
        }

        func_002113C0(p, 0, 4, 1);
        *(s32 *)(p + 0xC00) = 0;
        *(s32 *)(p + 0xB48) = 1;
        *(f32 *)(p + 0x101C) = 0.5f;
        *(f32 *)(p + 0x1020) = 500.0f;
        *(f32 *)(p + 0x1F0) = 1.0f;
        *(s32 *)(p + 0xC08) = -1;
        *(s32 *)(p + 0xC0C) = -1;
        *(s32 *)(p + 0xBF4) = -1;
        func_001F5958(p);

        c1 = *(s32 *)(D_003876A0 + s6 + 0xE0);
        *(s32 *)(p + 0x1184) = c1;
        if (c1 > 0) {
            s32 k3 = 0;
            s32 t0 = 0;
            u8 *a1 = p + 0x1190;
            do {
                s32 base = s6 + t0;
                k3 += 1;
                *(u32 *)a1 = *(u32 *)(D_003876A0 + base + 0xE8) / 9U;
                *(u32 *)(a1 + 4) = *(u32 *)(D_003876A0 + base + 0xE8) % 9U;
                t0 += 0x58;
                a1 += 0x80;
            } while (k3 < c1);
        }

        {
            s32 k4 = 4;
            u8 *v0p = p + 0x1420;
            do {
                k4 -= 1;
                *(s32 *)v0p = -1;
                v0p -= 4;
            } while (k4 >= 0);
        }

        if (c1 > 0) {
            s32 a3 = 0;
            s32 k5 = 0;
            u8 *dst = p + 0x11C0;
            s32 *ip = (s32 *)(p + 0x1410);
            do {
                dst[-0x28] = 1;
                *ip = k5;
                ip += 1;
                dst[-0x27] = 1;
                k5 += 1;
                *(s32 *)dst = *(s32 *)(D_003876A0 + s6 + a3 + 0xF0);
                *(s32 *)(dst + 4) = *(s32 *)(D_003876A0 + s6 + a3 + 0xF4);
                if (*(D_003876A0 + s6 + 0x2A4) != 0 &&
                    *(s32 *)(D_003876A0 + s6 + 0xE0 + a3 + 0x18) == 0) {
                    dst[-0x27] = 0;
                }
                a3 += 0x58;
                dst += 0x80;
            } while (k5 < c1);

            {
                s32 s0v = s6;
                s32 s4 = 0;
                s32 s3 = 0;
                do {
                    u8 *e;
                    u8 *f;
                    u8 *el;
                    u8 *r;
                    s32 idx;
                    s64 q;
                    e = func_00202E60(p, s3);
                    idx = s3;
                    s3 += 1;
                    f = D_003876A0 + s0v + s4 + 0x40;
                    *(s32 *)(e + 0) = *(s32 *)(f + 0xEC);
                    *(s32 *)(e + 4) = *(s32 *)(f + 0xF0);
                    *(s32 *)(e + 0x10) = 0x186A0;
                    *(s32 *)(e + 0xC) = *(s32 *)(f + 0xE8);
                    *(s32 *)(e + 0x14) = 0;
                    *(s32 *)(e + 0x18) = 0;
                    r = func_00202DA0(p, idx, s4 + 0x40, 0x186A0);

                    el = D_003876A0 + s0v + s4;
                    *(s32 *)(r + 0xC) = *(s32 *)(el + 0x10 + 0xF0);
                    *(s32 *)(r + 0x10) = *(s32 *)(el + 0x10 + 0xF4);
                    *(s32 *)(r + 0x14) = *(s32 *)(el + 0x20 + 0xE8);
                    *(s32 *)(r + 0x18) = *(s32 *)(el + 0x20 + 0xEC);
                    *(s32 *)(r + 0x1C) = *(s32 *)(el + 0x20 + 0xF0);
                    *(s32 *)(r + 0x20) = *(s32 *)(el + 0x20 + 0xF4);
                    *(s32 *)(r + 0x24) = *(s32 *)(el + 0x30 + 0xE8);
                    q = *(s64 *)(el + 0x30 + 0xF0);
                    *(s64 *)(r + 0x28) = q;
                    if (q & 0x100) {
                        *(s32 *)(e + 0xC) = *(s32 *)(e + 0x10);
                    }
                    s4 += 0x58;
                } while (s3 < c1);
            }
        }

        s6 += 0x1D0;
        a = BtlMember_GetActiveGauge(p);
        t = func_0023F9B0(p);
        prod = (s32)((u32)t * 0x186A0U);
        s7 += 8;
        s5 += 1;
        *(s32 *)(a + 0x18) = prod;
        c = BtlMember_GetActiveGauge(p);
        *(s32 *)(c + 8) = func_0023F960(p);
        *(s32 *)(p + 0x142C) = -1;
    }
}
