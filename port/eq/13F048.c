#include "common.h"

extern u8 *gEftDust;
extern f32 D_003844C4;
extern f32 D_003844C8;

u8 *EftWaterRing_Alloc(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 a8);
s32 func_003126C8(u8 *a0, s32 a1);

/* 0x0013F048 (EftWaterRing_Spawn): allocates a ring record, links it into the two lists at arg0 /
 * arg1 and fills its fields; the flag word arg8 (bits 4 and 8) picks the speed or the fade setup. */
void EftWaterRing_Spawn(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                        s32 arg8, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6) {
    s32 t3m;
    u8 *s0;
    f32 f0;

    t3m = arg7 & 0xFF;
    s0 = EftWaterRing_Alloc(arg0, arg1, arg2, arg3, arg4, arg5, arg6, t3m, t3m);
    if (s0 == NULL) {
        return;
    }

    if (*(u8 **)arg0 == NULL) {
        *(u8 **)arg0 = s0;
        *(s32 *)(s0 + 0x40) = 0;
        *(s32 *)(s0 + 0x44) = 0;
    } else {
        *(u8 **)(s0 + 0x40) = *(u8 **)arg1;
        *(s32 *)(s0 + 0x44) = 0;
    }
    if (*(u8 **)arg1 != NULL) {
        *(u8 **)(*(u8 **)arg1 + 0x44) = s0;
    }
    *(u8 **)arg1 = s0;

    func_003126C8(s0, arg2);
    *(f32 *)(s0 + 0x10) = farg1;
    *(f32 *)(s0 + 0x14) = farg2;
    if (farg3 == 0.0f) {
        *(f32 *)(s0 + 0x18) = 0.0f;
    } else {
        *(f32 *)(s0 + 0x18) = 1.0f / farg3;
    }
    *(f32 *)(s0 + 0x28) = farg0;
    *(f32 *)(s0 + 0x30) = farg6 * 30.0f;
    *(u8 *)(s0 + 0x34) = (u8)(arg3 & 0xFF);
    *(u8 *)(s0 + 0x35) = (u8)(arg4 & 0xFF);
    *(u8 *)(s0 + 0x36) = (u8)(arg5 & 0xFF);
    *(u8 *)(s0 + 0x37) = (u8)(arg6 & 0xFF);
    *(u8 *)(s0 + 0x38) = (u8)t3m;
    *(s32 *)(s0 + 0x3C) = arg8;

    if ((arg8 & 4) != 0) {
        *(f32 *)(s0 + 0x24) = farg4;
        *(s32 *)(s0 + 0x1C) = 0;
        f0 = farg5 * D_003844C4;
        f0 = f0 * 30.0f;
        *(f32 *)(s0 + 0x2C) = farg5 * D_003844C8;
        *(f32 *)(s0 + 0x20) = farg4 / f0;
    } else if ((arg8 & 8) != 0) {
        f0 = farg5 * 30.0f;
        *(f32 *)(s0 + 0x2C) = farg5;
        *(f32 *)(s0 + 0x1C) = farg4;
        *(s32 *)(s0 + 0x24) = 0;
        *(f32 *)(s0 + 0x20) = farg4 / f0;
    }
    *(s32 *)(gEftDust + 0x30) = *(s32 *)(gEftDust + 0x30) + 1;
}
