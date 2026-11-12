#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
f32 func_00209730(s32 arg0, s32 arg1);
f32 func_00272FA8(void);
f32 func_00273000(void);
f32 func_00273048(void);
extern f32 D_00384524;
extern f32 D_00384528;
extern u8 *gEftBound;

void func_00145680(s32 arg0, s32 arg1) {
    s32 sp[4];
    u8 *s0;
    u8 *s2;
    f32 h;
    f32 t;

    s0 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(gEftBound + 0x218);
    memset((void *)s0, 0, 0x1050);
    *(s32 *)s0 = *(s32 *)arg1;
    h = BtlCharApi_GetHeight(*(s32 *)arg1) / D_00384524;
    *(f32 *)(s0 + 0x14) = h;
    if (h < D_00384528) {
        *(f32 *)(s0 + 0x14) = D_00384528;
    }
    *(f32 *)(s0 + 0x18) = func_00209730(*(s32 *)arg1, (s32)sp);
    *(f32 *)(s0 + 4) = func_00272FA8() + *(f32 *)(s2 + 0xC);
    *(f32 *)(s0 + 8) = *(f32 *)(s2 + 0x10) - func_00273000();
    t = func_00273048();
    *(s8 *)(s0 + 0x840) = 0;
    *(s32 *)(s0 + 0x48) = 0;
    *(s32 *)(s0 + 0x4C) = 0;
    *(s32 *)(s0 + 0x858) = 0;
    *(s32 *)(s0 + 0x85C) = 0;
    *(f32 *)(s0 + 0xC) = t - *(f32 *)(s0 + 8);
    *(s8 *)(s0 + 0x30) = 0;
}
