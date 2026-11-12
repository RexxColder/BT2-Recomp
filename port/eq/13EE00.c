#include "common.h"

/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, x) do { \
    (dst) = (s32)(x); \
} while (0)

void Vu0Screen_StoreMtx(s32 arg0);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_001407D0(f32 farg0, f32 farg1, s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 s8);
extern u8 *gEftDust;

void EftWaterDrop_DrawList(s32 arg0, s32 arg1) {
    u8 *s0;
    s32 sp10[16];
    f32 sp50[4];
    f32 f0;
    f32 two31 = 2147483648.0f;
    s32 conv;

    Vu0Screen_StoreMtx((s32)sp10);
    s0 = (u8 *)arg0;
    if (s0 == NULL) {
        return;
    }
    do {
        if (*(s32 *)(s0 + 0x64) & 2) {
            func_00312638((s32)sp50, (s32)s0, arg1);
            sp50[3] = 1.0f;
            if (*(s32 *)(s0 + 0x64) & 0x100) {
                f0 = *(f32 *)(s0 + 0x44);
                if (f0 >= two31) {
                    CVT_W_S(conv, f0 - two31);
                    conv = conv | (s32)0x80000000;
                } else {
                    CVT_W_S(conv, f0);
                }
                conv = conv & 0xFF;
                func_001407D0(*(f32 *)(s0 + 0x30), *(f32 *)(s0 + 0x3C),
                    (s32)sp50, (s32)sp10,
                    *(u8 *)(s0 + 0x5C), *(u8 *)(s0 + 0x5D), *(u8 *)(s0 + 0x5E),
                    0x60, conv,
                    (s32)gEftDust + (*(u8 *)(s0 + 0x5F) << 4) + 0xB0,
                    *(u8 *)(s0 + 0x60));
            } else {
                f0 = *(f32 *)(s0 + 0x44);
                if (f0 >= two31) {
                    CVT_W_S(conv, f0 - two31);
                    conv = conv | (s32)0x80000000;
                } else {
                    CVT_W_S(conv, f0);
                }
                conv = conv & 0xFF;
                func_001407D0(*(f32 *)(s0 + 0x30), *(f32 *)(s0 + 0x3C),
                    (s32)sp50, (s32)sp10,
                    *(u8 *)(s0 + 0x5C), *(u8 *)(s0 + 0x5D), *(u8 *)(s0 + 0x5E),
                    conv, 0,
                    (s32)gEftDust + (*(u8 *)(s0 + 0x5F) << 4) + 0xB0,
                    *(u8 *)(s0 + 0x60));
            }
        }
        s0 = *(u8 **)(s0 + 0x6C);
    } while (s0 != NULL);
}
