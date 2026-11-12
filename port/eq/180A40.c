#include "common.h"

#define F32AT(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define S32AT(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U8AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
/* cvt.w.s: truncates toward zero, written out */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(out, x) do { \
    (out) = (s32)(x); \
} while (0)

void Vu0Screen_StoreMtx(void *);
void Mtx_StoreIdentity(void *);
void Mtx_InverseRT(void *, s32);
void Mtx_Mul(void *, void *, void *);
void Mtx_RotateZ(f32, void *, void *);
void func_00128C28(void *, void *, void *);
void func_00129C50(void *, void *, void *);
void func_00129B28(void *, void *, void *);
void func_00180D98(f32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern u8 D_0036E870[] __attribute__((section(".data")));
extern u8 D_0036E8B0[] __attribute__((section(".data")));
extern s32 gBtlCamView;

void func_00180A40(void *arg0) {
    u8 sp[0x1E0];
    s32 i;
    s32 k;
    u8 *s0;
    u8 *s1;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f5;
    f32 f20;
    s32 t0u;
    s32 a2u;
    s32 a3u;
    s32 v1u;
    s32 t1;
    s32 y0;

    /* two 64-byte tables copied to the frame, in place */
    for (i = 0; i < 0x40; i++) {
        sp[0x130 + i] = D_0036E870[i];
    }
    for (i = 0; i < 0x40; i++) {
        sp[0x170 + i] = D_0036E8B0[i];
    }

    if (S32AT(arg0, 0x54) > 0) {
        return;
    }

    Vu0Screen_StoreMtx(sp + 0x70);
    Mtx_StoreIdentity(sp + 0x30);
    Mtx_StoreIdentity(sp + 0xB0);
    Mtx_InverseRT(sp + 0x30, gBtlCamView);
    Mtx_Mul(sp + 0xB0, sp + 0xB0, sp + 0x30);
    *(s32 *)(sp + 0x60) = 0;
    *(s32 *)(sp + 0x64) = 0;
    *(s32 *)(sp + 0x68) = 0;
    f20 = 0.0f;
    F32AT(sp, 0xE8) = 0.0f;
    F32AT(sp, 0xE4) = 0.0f;
    F32AT(sp, 0xE0) = 0.0f;

    for (k = 0; k < 4; k++) {
        /* 4 floats of record k of the first table */
        F32AT(sp, 0x1B0) = F32AT(sp, 0x130 + k * 0x10);
        F32AT(sp, 0x1B4) = F32AT(sp, 0x134 + k * 0x10);
        F32AT(sp, 0x1B8) = F32AT(sp, 0x138 + k * 0x10);
        F32AT(sp, 0x1BC) = F32AT(sp, 0x13C + k * 0x10);
        s1 = sp + 0xF0 + k * 0x10;
        s0 = sp + 0xFC + k * 0x10;

        Mtx_StoreIdentity(sp + 0x30);
        f5 = F32AT(arg0, 0x20);
        f2 = F32AT(arg0, 0x28);
        f0 = F32AT(arg0, 0x38) * f5 + f20;
        f1 = F32AT(arg0, 0x2C) * F32AT(arg0, 0x24) + f20;
        F32AT(sp, 0x1DC) = 1.0f;
        F32AT(sp, 0x1D8) = (f5 * -10.0f) * f2;
        F32AT(sp, 0x1D0) = f1 * f2;
        F32AT(sp, 0x1D4) = f0 * f2;
        func_00128C28(sp + 0x30, sp + 0x30, sp + 0x1D0);
        Mtx_RotateZ(F32AT(arg0, 0x10), sp + 0x30, sp + 0x30);
        func_00129C50(sp + 0x1C0, sp + 0x30, sp + 0x1B0);
        func_00129C50(s1, sp + 0xB0, sp + 0x1C0);
        func_00129B28(s1, s1, arg0);
        F32AT(s0, 0) = 1.0f;
    }

    /* float -> u8 conversions of (u8 0x5F) * f32 0x18 */
    v1u = U8AT(arg0, 0x5F);
    a2u = U8AT(arg0, 0x5C);
    a3u = U8AT(arg0, 0x5D);
    t0u = U8AT(arg0, 0x5E);
    f2 = F32AT(arg0, 0x18);
    f0 = (f32)v1u * f2;
    f1 = 2147483648.0f;
    if (f1 <= f0) {
        CVT_W_S(t1, f0 - f1);
        t1 = (s32)((u32)t1 | 0x80000000u);
    } else {
        CVT_W_S(t1, f0);
    }
    t1 = t1 & 0xFF;

    f0 = (f32)v1u * f2;
    if (f1 <= f0) {
        CVT_W_S(y0, f0 - f1);
        y0 = (s32)((u32)y0 | 0x80000000u);
    } else {
        CVT_W_S(y0, f0);
    }
    y0 = y0 & 0xFF;

    /* 9th..13th arguments go to the stack at sp+0, +8, +0x10, +0x18, +0x20 (GUESS arity 13) */
    func_00180D98(4.0f, sp + 0xF0, sp + 0x170, a2u, a3u, t0u, t1, a2u, a3u, t0u, y0, (s32)(sp + 0x70),
                  S32AT(arg0, 0x50), S32AT(arg0, 0x60));
}
