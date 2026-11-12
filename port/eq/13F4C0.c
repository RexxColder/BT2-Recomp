#include "common.h"

void Vu0Screen_StoreMtx(void *arg0);
void func_00140D18(f32 farg0, f32 farg1, void *arg0, void *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 *arg6, u8 arg7);
extern s32 gEftDust;

void EftWaterRing_DrawList(void *arg0) {
    s32 sp[16];
    u8 *s0;
    f32 x;
    s32 q;
    u8 t1;

    s0 = arg0;
    Vu0Screen_StoreMtx(sp);
    while (s0 != NULL) {
        if (*(s32 *)(s0 + 0x3C) & 2) {
            x = *(f32 *)(s0 + 0x1C);
            if (x >= 2147483648.0f) {
                x = x - 2147483648.0f;
            }
            /* cvt.w.s truncates toward zero (saturating); only the low byte is kept */
            q = (s32)x;
            t1 = (u8)(q & 0xFF);
            func_00140D18(*(f32 *)(s0 + 0x10), *(f32 *)(s0 + 0x28), s0, (void *)sp, s0[0x34], s0[0x35],
                          s0[0x36], t1, (u8 *)gEftDust + (s0[0x37] << 4) + 0xB0, s0[0x38]);
        }
        s0 = *(u8 **)(s0 + 0x44);
    }
}
