#include "common.h"

extern u8 D_0036EEF0[] __attribute__((section(".data")));
extern u8 D_0036EE48[] __attribute__((section(".data")));
extern u8 D_0036EE4C[] __attribute__((section(".data")));
extern u8 D_0036EE54[] __attribute__((section(".data")));
extern f32 D_00385008;
extern f32 D_0038500C;
extern f32 D_00385010;
extern f32 D_00385014;
extern f32 D_00385018;
extern f32 D_0038501C;

f32 BtlCharApi_GetHeight(void *a0);
void func_00208DE8(void *a0, void *a1, s32 a2);
void func_00312680(f32 f12, void *a0, void *a1);
void func_00312638(void *a0, void *a1, void *a2);
void func_00312650(void *a0, void *a1, void *a2);
void sceVu0Normalize(void *a0, void *a1);
void func_003126C8(void *a0, void *a1);
f32 func_001B7788(void *a0);
void func_00312FB0(f32 f12, void *a0, void *a1);
s32 rand(void);
f32 EftMath_WrapAngle(f32 f12, void *a0);
f32 func_0012A3F8(f32 f12);
f32 Mathf_Cos(f32 f12);
void func_001B5A70(void *a0, void *a1, s32 a2, s32 a3, s32 t0, f32 f12, f32 f13, f32 f14,
                   f32 f15, f32 f16, f32 f17, f32 f18);

#define FR(o) (*(f32 *)(sp + (o)))
#define WR(o) (*(s32 *)(sp + (o)))

void func_001B6AF0(void *arg0, f32 farg0) {
    u8 sp[0x100] __attribute__((aligned(8)));
    s32 spA4;
    s32 spB0;
    s32 spB4;
    u8 *pB8;
    u8 *pS3;
    u8 *pS6;
    s32 n;
    s32 s1;
    s32 s7;
    s32 rnd;
    s32 rem;
    s32 tt;
    s32 t;
    f32 f29;
    f32 f31;
    f32 f30;
    f32 f21;
    f32 f22;
    f32 f25;
    f32 f26;
    f32 f27;
    f32 f6;
    f32 f0;
    f32 f1;
    f32 f12;
    f32 h;
    f32 h2;
    f32 r;
    f32 lim;
    f32 rr;
    f32 wa;

    *(s64 *)(sp + 0x00) = *(s64 *)(D_0036EEF0 + 0x00);
    *(s64 *)(sp + 0x08) = *(s64 *)(D_0036EEF0 + 0x08);
    spB0 = 0x10;
    spA4 = 0;

    f29 = BtlCharApi_GetHeight(arg0) * 0.5f;
    f21 = D_00385008;
    func_00208DE8(arg0, sp + 0x30, 3);
    spB4 = 0;
    func_00312680(f29 * 0.5f, sp + 0x10, sp + 0x00);
    func_00312638(sp + 0x10, sp + 0x10, sp + 0x30);
    func_00312680(-f29 * 0.5f, sp + 0x20, sp + 0x00);
    func_00312638(sp + 0x20, sp + 0x20, sp + 0x30);
    func_00312650(sp + 0x40, sp + 0x20, sp + 0x10);
    sceVu0Normalize(sp + 0x40, sp + 0x40);

    h = BtlCharApi_GetHeight(arg0);
    f31 = (h * f21) * 5.0f;
    h = BtlCharApi_GetHeight(arg0);
    f0 = h * f21;
    f30 = f0 * 7.0f;

    pB8 = D_0036EE48;
    do {
        f12 = *(f32 *)pB8;
        func_00312680(f29 * f12, sp + 0x50, sp + 0x40);
        func_00312638(sp + 0x50, sp + 0x10, sp + 0x50);
        func_003126C8(sp + 0x60, sp + 0x50);

        f0 = *(f32 *)(D_0036EE4C + spB4);
        if (f0 >= 0.0f) {
            func_00312680(f29 * f0, sp + 0x80, sp + 0x40);
            func_00312638(sp + 0x80, sp + 0x10, sp + 0x80);
            func_00312650(sp + 0x80, sp + 0x80, sp + 0x50);
            r = func_001B7788(sp + 0x80);
            lim = *(f32 *)(pB8 + 8);
            if (lim < r) {
                rr = (r / lim) + 1.0f;
                /* cvt.w.s: truncates toward zero */
                tt = (s32)rr;
                n = tt;
                func_00312FB0(1.0f / (f32)n, sp + 0x70, sp + 0x80);
            } else {
                *(f32 *)(sp + 0x78) = 0.0f;
                n = 1;
                FR(0x70) = 0.0f;
                FR(0x74) = 0.0f;
                FR(0x7C) = 1.0f;
            }
        } else {
            *(f32 *)(sp + 0x78) = 0.0f;
            n = 1;
            FR(0x70) = 0.0f;
            FR(0x74) = 0.0f;
            FR(0x7C) = 1.0f;
        }

        if (n > 0) {
            s7 = 0;
            do {
                pS3 = D_0036EE4C + spB0;
                f27 = D_0038500C;
                f26 = f27 / (f32)*(s32 *)pS3;
                s1 = 0;
                rnd = rand();
                f6 = (f32)rnd / D_00385010;
                f0 = (f32)s7;
                FR(0x50) = FR(0x60) + f0 * FR(0x70);
                FR(0x58) = FR(0x68) + f0 * FR(0x78);
                FR(0x54) = FR(0x64) + f0 * FR(0x74);
                f25 = f6 * f27;

                if (*(s32 *)pS3 > 0) {
                    pS6 = D_0036EE54 + spB4;
                    do {
                        s32 rand1;
                        s32 rand2;
                        s32 rnd3;
                        rand1 = rand();
                        h = BtlCharApi_GetHeight(arg0);
                        f22 = (f32)rand1;
                        f1 = *(f32 *)pS6;
                        f0 = h * D_00385014;
                        f22 = f22 / D_00385010;
                        f22 = f22 + f1;
                        rand2 = rand();
                        f22 = f22 * f0;
                        f21 = (f32)rand2;
                        h2 = BtlCharApi_GetHeight(arg0);
                        f12 = (f32)s1;
                        s1 += 1;
                        f0 = h2 * D_00385014;
                        f21 = f21 / D_00385010;
                        f12 = f26 * f12;
                        f1 = *(f32 *)(D_0036EE48 + spB0);
                        f12 = f25 + f12;
                        f21 = f21 * 0.5f;
                        f21 = f21 + f1;
                        f21 = f21 * f0;
                        wa = EftMath_WrapAngle(f12, D_0036EE48);
                        f0 = wa;
                        FR(0x90) = func_0012A3F8(f0);
                        FR(0x94) = Mathf_Cos(f0);
                        WR(0x98) = 0;
                        FR(0x9C) = 1.0f;
                        f12 = f21 * D_00385018;
                        func_00312680(f12, sp + 0x90, sp + 0x90);
                        rnd3 = rand();
                        rem = rnd3 % 16;
                        t = 0x50 - rem;
                        func_001B5A70(sp + 0x50, sp + 0x90, 0, 0, 0x32, f31, f22 + f22, f30,
                                      -10.0f, D_0038501C, (f32)t, farg0);
                    } while (s1 < *(s32 *)(D_0036EE4C + spB0));
                }
                s7 += 1;
            } while (s7 < n);
        }

        spB0 += 0x18;
        spA4 += 1;
        spB4 += 0x18;
        pB8 += 0x18;
    } while (spA4 < 6);
}
