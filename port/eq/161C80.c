#include "common.h"

/* cvt.w.s under the default FCSR rounding mode: truncates toward zero */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { \
    (dst) = (s32)(x); \
} while (0)

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_0012D3A0(u8 *arg0, u8 *arg1, s32 arg2);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0);
void func_00283770(s32 arg0, u8 *arg1, s32 arg2);
void func_002837C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283800(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00283840(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern f32 D_0038474C;

void func_00161C80(u8 *arg0) {
    u8 sp[0x10];
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 s3;
    f32 f0;
    f32 f3;
    s32 xr;
    s32 yr;
    s32 zr;

    s0 = *(u8 **)(arg0 + 0x38);
    s1 = *(u8 **)(s0 + 0x70);
    s3 = func_0020B3D0(*(s32 *)s1);
    if (*(s32 *)(*(u8 **)(s1 + 0x20) + 0x30) & 0x200) {
        if (EftShot_TestBits(s3, 0x10) != 0) {
            s2 = s0 + 0x20;
            *(s32 *)s0 = *(s32 *)s0 | 0x80;
            func_00208DE8(*(s32 *)s1, sp, 0x11);
            func_0012D3A0(s2, sp, *(s32 *)s1);
        } else {
            s2 = s0 + 0x20;
        }
        if (EftShot_TestBits(s3, 0x20) != 0) {
            *(s32 *)(s0 + 0x14) = 0;
            *(s32 *)s0 = *(s32 *)s0 & ~0x80;
        }
        if (*(s32 *)s0 & 0x80) {
            f0 = *(f32 *)(s0 + 0x14) + D_0038474C;
            *(f32 *)(s0 + 0x14) = f0;
            if (f0 > 1.0f) {
                *(f32 *)(s0 + 0x14) = 1.0f;
            }
        }
    } else {
        s2 = s0 + 0x20;
    }

    f3 = *(f32 *)(s0 + 0x14);
    if (*(u8 *)(arg0 + 1) >= 4) {
        if (f3 < 0.0f) {
            *(f32 *)(s0 + 0x14) = 0.0f;
            f3 = 0.0f;
        }
    }

    CVT_W_S(xr, f3 * 8.0f);
    CVT_W_S(yr, f3 * 32.0f);
    CVT_W_S(zr, f3 * 128.0f);
    func_002837C0(0, 0x80, 0x80, 0x80, (u8)xr);
    func_00283800(0, 0x80, 0x80, 0x80, (u8)yr);
    func_00283840(0, 0x80, 0x80, 0x80, (u8)zr);
    func_00283770(0, s2, 0);
}
