#include "common.h"

extern u8 *gEftWeather;
extern u8 *gBtlCamView;
extern f32 D_00384534;
extern f32 D_00384538;
extern f32 D_0038453C;
extern f32 D_00384540;
extern f32 D_00384544;
extern f32 D_00384548;
extern f32 D_0038454C;
extern f32 D_00384550;
extern u8 D_003B0580[];

s32 func_00126588(void);
s32 rand();
void Vec4_Set(u8 *a0, f32 f12, f32 f13, f32 f14, f32 f15);
void Mtx_StoreIdentity(u8 *a0);
void func_00128900(u8 *a0, u8 *a1);
void Mtx_InverseRT(u8 *a0, u8 *a1);
void func_00129C28(u8 *a0, u8 *a1);
void func_00129B28(u8 *a0, u8 *a1, u8 *a2);
void func_00129C50(u8 *a0, u8 *a1, u8 *a2);
f32 func_00145AA8(u8 *a0, u8 *a1);
void func_00145A30(u8 *a0, u8 *a1, u8 *a2);
void func_00145A58(u8 *a0, u8 *a1, u8 *a2);
s32 func_00145A80(u8 *a0);
void StgTint_GetColor0(u8 *a0);
s32 func_00276D00();
void func_00312650(u8 *a0, u8 *a1, u8 *a2);
f32 sceVu0InnerProduct(u8 *a0, u8 *a1);

#define W(o) (*(s32 *)(sp + (o)))
#define F(o) (*(f32 *)(sp + (o)))

void func_00145DF0(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 sp[0x180] __attribute__((aligned(16)));
    u8 *s3 = arg0;
    u8 *a1, *p;
    s32 s0, s1, s2, s6, s7, fp, v0, v1, a0, wf;
    f32 f0, f1, f2, f3, f20, f21, f22, f24, f25, f26, f23;
    s64 col, a64, rgb;
    s32 s4, s5;

    *(u8 **)(sp + 0xD0) = arg1;
    s0 = func_00126588();
    W(0xD8) = 0;
    f24 = *(f32 *)(gEftWeather + 0x2AC);
    Vec4_Set(sp, 0.0f, 0.0f, 55.0f, 0.0f);
    s2 = *(s32 *)(gEftWeather + 0x2A8);
    Mtx_StoreIdentity(sp + 0x70);
    if (gBtlCamView) {
        func_00128900(sp + 0x30, gBtlCamView);
        Mtx_InverseRT(sp + 0x70, sp + 0x30);
    }
    func_00129C28(sp + 0x20, sp + 0xA0);
    s1 = s0 << 4;
    f1 = func_00145AA8(sp + 0x20, arg1 + s1);
    if (15.0f < f1) {
        s0 = s0 << 2;
        W(0xE4) = s0;
        W(0xD8) = 2;
        *(s32 *)(arg1 + s0 + 0x20) = 0;
    } else if (4.0f < f1) {
        s0 = s0 << 2;
        W(0xE4) = s0;
        W(0xD8) = 1;
        p = arg1 + (s0 + 0x20);
        v1 = *(s32 *)p;
        if (v1 < 15) *(s32 *)p = v1 + 1;
    } else {
        s0 = s0 << 2;
        W(0xE4) = s0;
        p = arg1 + (s0 + 0x20);
        v0 = *(s32 *)p;
        if (v0 != 0) {
            W(0xD8) = 1;
            *(s32 *)p = v0 - 1;
        }
    }
    func_00129C28(arg1 + s1, sp + 0x20);
    func_00145A30(sp + 0x60, sp + 0x60, sp);
    if (arg2 <= 0) return;
    W(0xDC) = s2 & 1;
    s2 = s2 & 2;
    f26 = D_00384534;
    f25 = D_00384538;
    W(0xD4) = arg2;
    f23 = D_0038453C;
    W(0xE0) = s2;
    do {
        v0 = rand();
        f1 = *(f32 *)(s3 + 0x10);
        f0 = (f32)((v0 & 0x1FF) - 0xFF);
        f0 = f0 * f26;
        f0 = f0 * f25;
        *(f32 *)(s3 + 0x10) = f1 + f0;
        v0 = rand();
        f1 = *(f32 *)(s3 + 0x14);
        f0 = (f32)((v0 & 0x1FF) - 0xFF);
        f0 = f0 * f26;
        f0 = f0 * f25;
        *(f32 *)(s3 + 0x14) = f1 + f0;
        v0 = rand();
        f1 = *(f32 *)(s3 + 0x18);
        f3 = *(f32 *)(s3 + 0x10);
        f0 = (f32)((v0 & 0x1FF) - 0xFF);
        f0 = f0 * f26;
        f0 = f0 * f25;
        f1 = f1 + f0;
        *(f32 *)(s3 + 0x18) = f1;
        if (f3 < f23) {
            *(f32 *)(s3 + 0x10) = f23;
            f3 = f23;
        }
        f2 = *(f32 *)(s3 + 0x14);
        if (f2 < f23) {
            *(f32 *)(s3 + 0x14) = f23;
            f2 = f23;
        }
        f1 = *(f32 *)(s3 + 0x18);
        if (f1 < f23) {
            *(f32 *)(s3 + 0x18) = f23;
            f1 = f23;
        }
        f0 = D_00384540;
        if (f0 < f3) *(f32 *)(s3 + 0x10) = f0;
        if (f0 < f2) *(f32 *)(s3 + 0x14) = f0;
        if (f0 < f1) *(f32 *)(s3 + 0x18) = f0;
        func_00129C28(sp + 0x10, s3);
        func_00129B28(sp + 0x10, sp + 0x10, gEftWeather + 0x230);
        func_00129B28(sp + 0x10, sp + 0x10, s3 + 0x10);
        F(0x1C) = 40.0f;
        func_00129C50(sp + 0x10, sp + 0x30, sp + 0x10);
        v1 = func_00145A80(sp + 0x10);
        if (v1 != 0) {
            f20 = -80.0f;
            do {
                *(s32 *)(s3 + 0x28) = 3;
                if (v1 & 1) F(0x10) = F(0x10) + f20;
                if (v1 & 2) F(0x10) = F(0x10) - f20;
                if (v1 & 4) F(0x14) = F(0x14) + f20;
                if (v1 & 8) F(0x14) = F(0x14) - f20;
                if (v1 & 0x10) F(0x18) = F(0x18) + f20;
                if (v1 & 0x20) F(0x18) = F(0x18) - f20;
                v1 = func_00145A80(sp + 0x10);
            } while (v1 != 0);
        }
        if (W(0xD8) == 2) *(s32 *)(s3 + 0x28) = 0;
        func_00145A58(sp + 0x10, sp + 0x10, sp);
        F(0x1C) = 1.0f;
        func_00129C50(sp + 0x10, sp + 0x70, sp + 0x10);
        f21 = F(0x14);
        if (W(0xE0) != 0) {
            if (0.0f <= f21) f21 = D_00384544;
        }
        f0 = -500.0f;
        if (f21 < f0) f21 = f0;
        f0 = f21 / f0;
        f21 = 1.0f - f0;
        f0 = func_00145AA8(sp + 0x20, sp + 0x10);
        f20 = f0 * D_00384548;
        f22 = 1.0f;
        if (1.0f < f20) {
            f20 = 0.0f;
        } else if (f20 < 0.5f) {
            f0 = D_0038454C;
            if (f20 <= f0) {
                f20 = 0.0f;
            } else {
                f20 = (f20 - f0) * 2.5f;
            }
        } else {
            f0 = f20 - 0.5f;
            f0 = f0 + f0;
            f20 = 1.0f - f0;
        }
        v1 = *(s32 *)(s3 + 0x28);
        if (v1 != 0) {
            v0 = 3 - v1;
            *(s32 *)(s3 + 0x28) = v1 - 1;
            f0 = (f32)v0 / 3.0f;
            f20 = f20 * f0;
        }
        if (W(0xD8) == 1) {
            v1 = *(s32 *)(arg1 + W(0xE4) + 0x20);
            if (v1 != 0) {
                f0 = (f32)(30 - v1) / 30.0f;
                f20 = f20 * f0;
            }
        }
        f20 = f20 * f21;
        if (W(0xDC)) {
            f0 = f24 + 4.0f;
            f1 = F(0x14);
            f0 = f1 + f0;
            f2 = 0.0f;
            if (f2 < f0) {
                f1 = f1 + f24;
                if (f1 < f2) {
                    f0 = f1 * 0.25f;
                    f0 = -f0;
                    f20 = f20 * f0;
                } else {
                    f20 = f2;
                }
            }
        }
        f22 = 1.0f;
        s1 = *(s32 *)(gEftWeather + 0x218);
        s2 = *(s32 *)(gEftWeather + 0x210);
        s0 = *(s32 *)(gEftWeather + 0x214);
        StgTint_GetColor0(sp + 0xB0);
        v0 = W(0xBC);
        if (v0 != 0) {
            f0 = (f32)v0;
            f0 = f0 / 100.0f;
            s0 = s0 - v0;
            s1 = s1 - v0;
            s2 = s2 - v0;
            if (s2 < 0) s2 = 0;
            if (s0 < 0) s0 = 0;
            if (s1 < 0) s1 = 0;
            f22 = f22 - f0;
        }
        s6 = s1;
        s7 = s0;
        fp = s2;
        f0 = f20 * 128.0f;
        f1 = 2147483648.0f;
        rgb = ((s64)s6 << 16) | ((s64)s7 << 8);
        col = (s64)fp | 0x3F80000000000000LL | rgb;
        f0 = f0 * f22;
        if (f1 <= f0) {
            a0 = (s32)(f0 - f1) | (s32)0x80000000;
        } else {
            a0 = (s32)f0;
        }
        v0 = a0 & 0xFF;
        col = col | ((s64)v0 << 24);
        *(s64 *)(s3 + 0x20) = col;
        if (func_00276D00()) {
            f20 = 1.0f;
            v0 = *(s32 *)(D_003B0580 + 0x100);
            if (v0 > 0) {
                f21 = f20;
                for (s4 = 0; s4 < *(s32 *)(D_003B0580 + 0x100); s4++) {
                    func_00312650(sp + 0xC0, D_003B0580 + s4 * 0x10, sp + 0x10);
                    W(0xC4) = 0;
                    F(0xCC) = f21;
                    f0 = sceVu0InnerProduct(sp + 0xC0, sp + 0xC0);
                    f1 = *(f32 *)(D_003B0580 + 0xC + s4 * 0x10);
                    f1 = f1 * f1;
                    f0 = f0 / f1;
                    if (f0 < f20) f20 = f0;
                }
            }
            if (f20 < 1.0f) {
                f0 = D_00384550;
                if (f20 < f0) {
                    *(s64 *)(s3 + 0x20) = (s64)fp | rgb | 0x3F80000000000000LL;
                } else {
                    f0 = f20 - f0;
                    f0 = f0 * 2.5f;
                    f0 = f0 * 128.0f;
                    f0 = f0 * f22;
                    v0 = (s32)f0;
                    a64 = (s64)(s32)((u32)v0 << 24);
                    *(s64 *)(s3 + 0x20) = a64 | (s64)fp | rgb | 0x3F80000000000000LL;
                }
            }
        }
        W(0xD4) = W(0xD4) - 1;
        func_00129C28(s3, sp + 0x10);
        s3 += 0x30;
    } while (W(0xD4) != 0);
}
