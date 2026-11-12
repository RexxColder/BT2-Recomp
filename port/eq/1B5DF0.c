#include "common.h"

extern u8 *gEftShotFx;

void Vu0Screen_StoreMtx(u8 *arg0);
void func_001B60D8(u8 *arg0, u8 *arg1);
void func_001B6320(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6, s32 arg7);

/* cvt.w.s: truncates toward zero. */
/* cvt.w.s truncates toward zero (saturating): plain cast */
static s32 cvt_w_s(f32 x) {
    return (s32)x;
}

void func_001B5DF0(void) {
    u8 buf[0x80];
    u8 *out = buf + 0x40;
    u8 *s1;

    Vu0Screen_StoreMtx(buf);
    s1 = *(u8 **)(gEftShotFx + 0x54);
    while (s1 != NULL) {
        if (*(s32 *)(s1 + 0x48) & 2) {
            s32 t1;
            f32 f0;

            func_001B60D8(out, s1);
            f0 = *(f32 *)(s1 + 0x34);
            t1 = cvt_w_s(f0);
            if (f0 >= 2147483648.0f) {
                t1 = cvt_w_s(f0 - 2147483648.0f) | (s32)0x80000000u;
            }
            func_001B6320(out, buf, 0, 0, 0, t1 & 0xFF, *(u8 **)(gEftShotFx + 0x50) + (*(u8 *)(s1 + 0x44) << 4),
                          *(u8 *)(s1 + 0x45));
        }
        s1 = *(u8 **)(s1 + 0x50);
    }
}
