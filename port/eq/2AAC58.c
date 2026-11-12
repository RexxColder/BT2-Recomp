#include "common.h"

/* cvt.w.s: truncates toward zero (FCSR RN), then store the integer bits */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, src) do { \
    (dst) = (s32)(src); \
} while (0)

extern u8 D_003B26B0[] __attribute__((section(".data")));
extern s32 D_003B2654 __attribute__((section(".data")));
extern u8 *D_00387A40;
extern f32 D_003872F0;
extern f32 D_003872F4;
extern f32 D_003872F8;
extern f32 D_003872FC;
extern f32 D_00387300;
extern f32 D_00387304;
extern f32 D_00387308;
extern f32 D_0038730C;
extern f32 D_00387310;
extern f32 D_00387314;
extern f32 D_00387318;

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_002AA1D8(void *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_003126C8(void *arg0, void *arg1);
s32 func_00276B00(s32 arg0, void *arg1, void *arg2);
s32 func_002AD340(s32 arg0);
s32 func_002AD188(s32 arg0);
void sceVu0ApplyMatrix(void *arg0, void *arg1, void *arg2);

void func_002AAC58(void) {
    u32 spw[0x40];
    u8 *sp;
    u8 *B;
    u8 *X;
    u8 *P;
    u8 *Q;
    u8 *s1;
    u8 *M;
    u8 *s0p;
    s32 v0;
    s32 v1;
    s32 k;
    s32 r;
    s32 s0v;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;

    sp = (u8 *)spw;
    B = D_003B26B0;
    X = B + 0x35C;
    P = B + 0x378;

    memset(P, 0, 0x20C);

    v0 = *(s32 *)(X + 0x18);
    if (X[3] != 0) {
        v0 = v0 + 0x20;
    } else {
        v0 = v0 - 0x20;
    }
    *(s32 *)(X + 0x18) = v0;
    v1 = *(s32 *)(X + 0x18);
    if (v1 >= 0xC9) {
        v1 = 0xC8;
        *(s32 *)(X + 0x18) = 0xC8;
    }
    if (v1 < 0) {
        *(s32 *)(X + 0x18) = 0;
        return;
    }

    P[0x208] = 1;
    func_002AA1D8(sp, 0, 0, 1.0f, D_003872F0, 2048.0f, 2048.0f);

    if (D_003B2654 < 0) {
        Q = P + 0x14;
        Q[0] = 1;
        *(s32 *)(Q + 0x10) = (s32)0x800000FF;
        Q[1] = 0;
        M = *(u8 **)(D_00387A40 + 8);
        func_003126C8(sp + 0x40, M + 0x1EE0);
        s0p = M + 0x1EC0;
        *(s32 *)(sp + 0x44) = 0;
        f1 = D_003872F4;
        f3 = D_003872F8;
        f0 = *(f32 *)(s0p + 0x44) + f1;
        *(f32 *)(Q + 0xC) = f0;
        f2 = *(f32 *)(sp + 0x40);
        f1 = *(f32 *)(sp + 0x48);
        if (f2 < f3) {
            f2 = f2 + D_003872FC;
            *(f32 *)(sp + 0x40) = f2;
            f1 = *(f32 *)(sp + 0x48);
        }
        if (f1 < f3) {
            f1 = f1 + D_00387300;
            *(f32 *)(sp + 0x48) = f1;
        }
        f3 = D_00387304;
        if (f3 < f2) {
            f2 = f2 + D_00387308;
            *(f32 *)(sp + 0x40) = f2;
        }
        if (f3 < f1) {
            f1 = f1 + D_0038730C;
            *(f32 *)(sp + 0x48) = f1;
        }
        sceVu0ApplyMatrix(sp + 0x50, sp, sp + 0x40);
        CVT_W_S(*(s32 *)(Q + 4), *(f32 *)(sp + 0x50));
        CVT_W_S(*(s32 *)(Q + 8), *(f32 *)(sp + 0x54));
    }

    /* L2AAE10 */
    P[0] = 1;
    *(s32 *)(P + 0x10) = (s32)0x80FFFFFF;
    P[1] = 0;
    M = *(u8 **)(D_00387A40 + 8);
    func_003126C8(sp + 0x40, M + 0x9C0);
    s0p = M + 0x9A0;
    f1 = D_00387310;
    f3 = D_00387314;
    f0 = *(f32 *)(s0p + 0x44) + f1;
    *(f32 *)(P + 0xC) = f0;
    *(s32 *)(sp + 0x44) = 0;
    f2 = *(f32 *)(sp + 0x40);
    f1 = *(f32 *)(sp + 0x48);
    if (f2 < f3) {
        f2 = f3;
        *(f32 *)(sp + 0x40) = f2;
        f1 = *(f32 *)(sp + 0x48);
    }
    if (f1 < f3) {
        f1 = f3;
        *(f32 *)(sp + 0x48) = f3;
    }
    f0 = D_00387318;
    if (f0 < f2) {
        *(f32 *)(sp + 0x40) = f0;
    }
    if (f0 < f1) {
        *(f32 *)(sp + 0x48) = f0;
    }
    sceVu0ApplyMatrix(sp + 0x50, sp, sp + 0x40);
    s1 = P + 0x28;
    CVT_W_S(*(s32 *)(P + 4), *(f32 *)(sp + 0x50));
    CVT_W_S(*(s32 *)(P + 8), *(f32 *)(sp + 0x54));

    for (k = 0; k < 0x18; k++) {
        v1 = 1 << k;
        if ((*(s32 *)(B + 0x20) & v1) != 0) {
            if ((*(s32 *)(B + 0x14) & v1) != 0) {
                r = func_00276B00(k, sp + 0x60, sp + 0x70);
                if (r > 0) {
                    s0v = (s32)0x800000FF;
                    if (func_002AD188(func_002AD340(k)) != 2) {
                        s0v = (s32)0x8000FFFF;
                    }
                    if (k == 0) {
                        s0v = (s32)0x80FFFFFF;
                    }
                    *(s32 *)(sp + 0x64) = 0;
                    sceVu0ApplyMatrix(sp + 0x80, sp, sp + 0x60);
                    s1[0] = 1;
                    *(s32 *)(s1 + 0x10) = s0v;
                    s1[1] = 1;
                    CVT_W_S(*(s32 *)(s1 + 4), *(f32 *)(sp + 0x80));
                    CVT_W_S(*(s32 *)(s1 + 8), *(f32 *)(sp + 0x84));
                }
            }
        }
        s1 += 0x14;
    }
}
