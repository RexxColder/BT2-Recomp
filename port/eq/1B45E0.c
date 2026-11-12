#include "common.h"

#define FLD(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define FLDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define FLDU8(p, off) (*(u8 *)((u8 *)(p) + (off)))
#define CVT_W_S(x) ((s32)(x)) /* cvt.w.s del R5900 trunca hacia cero */
#define UCVT(x) ({ f32 _u = (x); s32 _r; \
    if (_u >= 2147483648.0f) { _r = CVT_W_S(_u - 2147483648.0f) | (s32)0x80000000u; } \
    else { _r = CVT_W_S(_u); } \
    _r; })

extern u8 D_0036EB60[] __attribute__((section(".data")));
extern s32 gBtlCamView;
extern u8 *gEftRay __attribute__((section(".data")));

s32 BtlCtrl_IsInterruptible(s32 arg0);
s32 func_00126EC0(s64 a0, s64 a1, s64 a2, s64 a3);
s32 func_00126598(s32 arg0);
void Mtx_StoreIdentity(void *arg0);
void Mtx_InverseRT(void *arg0, s32 arg1);
void Mtx_Mul(void *arg0, void *arg1, void *arg2);
void Mtx_RotateZ(f32 farg0, void *arg0, void *arg1);
void Vec4_Set(f32 farg0, f32 farg1, f32 farg2, f32 farg3, void *arg0);
void func_00129C28(void *arg0, void *arg1);
void func_00129B28(void *arg0, void *arg1, void *arg2);
void func_00129C50(void *arg0, void *arg1, void *arg2);
void func_00128EF0(void);
void func_00128F08(void);
void func_00128F90(s32 arg0);
s32 func_0020B3D0(s32 arg0);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void sceVu0RotTransPers(void *arg0, s32 arg1, void *arg2, s32 arg3);
void func_001B4AA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 arg9, u8 *arg10); /* as defined in 1B4AA0.c */
void func_001B4C18(u8 *arg0, s32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7,
                   f32 f12, u32 st0, u32 st1, s32 st2, u64 *st3); /* as defined in 1B4C18.c (st3 is a pointer) */

void func_001B45E0(void *arg0) {
    u8 spb[0x140];
    u8 *sp = spb;
    u8 *E = (u8 *)arg0;
    s64 *src = (s64 *)D_0036EB60;
    s32 i;
    s32 s504;
    s32 cnt;

    for (i = 0; i < 8; i++) {
        *(s64 *)(sp + 0xB0 + 8 * i) = src[i];
    }

    if (FLD(E, 0x50C) < 0 ||
        (((func_00126EC0(src[1], src[2], src[3], src[4]) != 0) || (func_00126598(FLD(E, 0x50C)) != 0)) &&
         BtlCtrl_IsInterruptible(FLD(E, 0x50C)) == 0)) {
        s504 = FLD(E, 0x504);
        if (s504 == 0) {
            u8 *fp = E + 0x4A0;
            Mtx_StoreIdentity(sp + 0x70);
            Mtx_StoreIdentity(fp);
            Mtx_InverseRT(sp + 0x70, gBtlCamView);
            Mtx_Mul(fp, fp, sp + 0x70);
            func_00129C28(E + 0x4D0, E + 0x480);
        } else if (s504 == 1) {
            if ((u32)(FLD(E, 0x508) - 2) < 2u) {
                s32 dv = func_0020B3D0(FLD(E, 0x50C));
                func_00208DE8(dv, sp + 0xF0, 3);
                sceVu0RotTransPers(sp + 0x100, gBtlCamView + 0x100, sp + 0xF0, 1);
                if (FLD(spb, 0x108) < 0) {
                    return;
                }
                FLDF(E, 0x48C) = 1.0f;
                FLD(E, 0x488) = 0;
                FLDF(E, 0x480) = (f32)((FLD(spb, 0x100) - 0x7000) >> 4);
                FLDF(E, 0x484) = (f32)((FLD(spb, 0x104) - 0x7200) >> 4);
            }
            Mtx_StoreIdentity(E + 0x4A0);
            func_00129C28(E + 0x4D0, E + 0x480);
        }
        /* L47B0 */
        func_00128EF0();
        cnt = 0;
        func_00128F90(gBtlCamView + 0x100);
        if (FLD(E, 0x4FC) > 0) {
            do {
                u8 *s1 = E + 0x18 * cnt;
                u8 *s3p = sp + 0x30;
                s32 s4;
                s32 it0;
                s32 it1;
                s32 it2;
                s32 it3;
                s32 alpha;
                f32 f0;
                f32 f1;
                f32 f2;
                f32 f13;

                for (s4 = 0; s4 < 4; s4++) {
                    u8 *vk = sp + 0xB0 + 0x10 * s4;
                    f1 = FLDF(vk, 0) * FLDF(s1, 0x10) * FLDF(E, 0x490);
                    FLDF(sp, 0x110) = f1;
                    f0 = FLDF(vk, 4) * FLDF(s1, 8) * FLDF(E, 0x494);
                    FLDF(sp, 0x114) = f0;
                    FLDF(sp, 0x118) = FLDF(vk, 8);
                    FLDF(sp, 0x11C) = FLDF(vk, 0xC);
                    f13 = -(FLDF(E, 0x4F0) + FLDF(s1, 0x14));
                    Vec4_Set(0.0f, f13, 0.0f, 0.0f, sp + 0x20);
                    func_00129B28(sp + 0x110, sp + 0x110, sp + 0x20);
                    Mtx_StoreIdentity(sp + 0x70);
                    Mtx_RotateZ(FLDF(s1, 4), sp + 0x70, sp + 0x70);
                    func_00129C50(sp + 0x120, sp + 0x70, sp + 0x110);
                    func_00129C50(s3p, E + 0x4A0, sp + 0x120);
                    s3p += 0x10;
                }

                s504 = FLD(E, 0x504);
                it0 = FLDU8(s1, 0);
                it1 = FLDU8(s1, 1);
                it2 = FLDU8(s1, 2);
                it3 = FLDU8(s1, 3);
                f2 = FLDF(E, 0x4E8);
                f0 = (f32)it3 * f2;
                alpha = UCVT(f0) & 0xFF;
                if (s504 == 0) {
                    func_001B4AA0(sp + 0x30, it0, it1, it2, alpha, it0, it1, it2, alpha,
                                  FLD(E, 0x500), gEftRay);
                } else {
                    func_001B4C18(sp + 0x30, 0, it0, it1, it2, alpha, it0, it1, 4.0f, it2,
                                  alpha, FLD(E, 0x500), (u64 *)gEftRay);
                }
                cnt += 1;
            } while (cnt < FLD(E, 0x4FC));
        }
        func_00128F08();
    }
    return;
}
