#include "common.h"

extern s32 D_00387E9C;
extern s32 gBtlCamView;
extern u8 D_002C3630[];

void Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Vu0Screen_StoreMtx(s32 arg0);
void Mtx_InverseRT(s32 arg0, s32 arg1);
s32 func_00126560(void);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00129DE0(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
void func_001DA3E8(s32 arg0, s32 arg1, s32 arg2);
void func_001DAF18(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);

/* cvt.w.s truncates toward zero; values >= 2^31 are split and the top bit is set back */
#define FIX_U32(dst, x) do { \
    f32 fx_ = (x); \
    if (fx_ >= 2147483648.0f) { \
        (dst) = (u32)(s32)(fx_ - 2147483648.0f) | 0x80000000u; \
    } else { \
        (dst) = (u32)(s32)fx_; \
    } \
} while (0)

/* Particle draw pass: for each live particle (0x70 bytes, from state+0x1420, count at state+0x16BC)
   that is not culled, build the screen matrix and submit it with its colour and alpha. */
s32 func_001D7B50(void) {
    u8 *gs;
    u8 *pi;
    u32 idx;
    s32 count;
    f32 vdown[4];
    f32 v15[16];
    f32 inv[16];
    u8 v14[0x110];   /* tamano de locales del original (antes 0x40) */
    f32 v17[4];
    f32 v18[4];
    f32 v20[4];
    s32 v21;
    s32 v22;
    s32 v23;
    s32 v24;
    u32 v13;
    f32 alpha;
    f32 f11;
    f32 f22;
    f32 len;
    f32 sum;

    Vec4_Set(vdown, 0.0f, -1.0f, 0.0f, 1.0f);
    gs = (u8 *)D_00387E9C;
    if (*(s32 *)(gs + 0x1444) == 0) {
        return (s32)gs;
    }

    Vu0Screen_StoreMtx((s32)v15);
    Mtx_InverseRT((s32)inv, gBtlCamView);

    gs = (u8 *)D_00387E9C;
    count = *(s32 *)(gs + 0x16BC);
    if (count == 0) {
        return 0;
    }

    pi = *(u8 **)(gs + 0x1420);
    alpha = 1.0f;
    f22 = 1.0f;

    for (idx = 0; idx < (u32)*(s32 *)((u8 *)D_00387E9C + 0x16BC); idx++, pi += 0x70) {
        if (pi[99] == 0) {
            continue;
        }
        if (pi[100] == 0) {
            continue;
        }

        if (!func_00126560()) {
            func_00312650((s32)v20, (s32)pi, (s32)v17);
            sum = v20[0] * v20[0] + v20[1] * v20[1] + v20[2] * v20[2];
            len = __builtin_sqrtf(__builtin_fabsf(sum));
            alpha = (len - 80.0f) / 70.0f;
            if (150.0f < len) {
                alpha = 1.0f;
            }
            if (len < 80.0f) {
                alpha = 0.0f;
            }
        }

        func_00129DE0(*(f32 *)(pi + 48), (s32)v18, (s32)vdown, (s32)(pi + 32));
        func_001DA3E8((s32)v14, (s32)v18, (s32)D_002C3630);

        gs = (u8 *)D_00387E9C;
        v21 = (s32)(*(f32 *)(gs + 0x14A0) * *(f32 *)(pi + 88));
        v22 = (s32)(*(f32 *)(gs + 0x14A4) * *(f32 *)(pi + 88));
        v23 = (s32)(*(f32 *)(gs + 0x14A8) * *(f32 *)(pi + 88));
        v24 = (s32)(*(f32 *)(pi + 64) * (*(f32 *)(gs + 0x14AC) * 0.0078125f));
        if ((f32)v24 < 0.0f) {
            v24 = 0;
        }
        f11 = (f32)v24;
        if (128.0f < (f32)v24) {
            v24 = 128;
            f11 = 128.0f;
        }

        FIX_U32(v13, f11 * alpha);

        func_001DAF18((s32)pi, (s32)v14, (s32)v15, (u8)v21, (u8)v22, (u8)v23, (u8)v13,
                      (s32)(gs + 0x14B0 + (pi[97] << 4)), pi[98],
                      *(f32 *)(pi + 52), *(f32 *)(pi + 76), 0.0f, *(f32 *)(pi + 80), 0.0f, 0.0f,
                      f22, f22);
    }
    return 0;
}
