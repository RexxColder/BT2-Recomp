#include "common.h"

s32 func_0020A758(s32 arg0);
s32 EftBurst_IsBusy(void);
f32 EftMath_WrapAngle(f32 farg0);
s32 func_001F0418(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10,
                  f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6, f32 farg7);
extern u8 *D_00387E9C;
extern f32 D_00385494;
extern f32 D_00385498;

void func_001D3288(void) {
    u8 *s0;
    s32 s2;
    f32 f20, ang, k;
    u8 *g;
    s32 a0, a1, a2, a3, t3;

    if (func_0020A758(0) != 0) return;
    if (func_0020A758(1) != 0) return;
    if (EftBurst_IsBusy() != 0) return;
    s0 = D_00387E9C;
    for (s2 = 0x1F; s2 >= 0; s2--, s0 += 0xA0) {
        if (s0[0x99] != 1) continue;
        if (*(s8 *)(s0 + 0x93) > 0) continue;
        if (!(0.0f < *(f32 *)(s0 + 0x6C))) continue;
        f20 = *(f32 *)(s0 + 0x4C) * (*(f32 *)(D_00387E9C + 0x14AC) * 0.0078125f);
        if (f20 < 0.0f) f20 = 0.0f;
        if (255.0f <= f20) f20 = 255.0f;
        ang = EftMath_WrapAngle(*(f32 *)(s0 + 0x78) / 180.0f * D_00385494);
        g = D_00387E9C;
        k = *(f32 *)(s0 + 0x8C);
        a0 = (u8)(u32)((f32)(u8)(u32)*(f32 *)(g + 0x14A0) * k);
        a1 = (u8)(u32)((f32)(u8)(u32)*(f32 *)(g + 0x14A4) * k);
        a2 = (u8)(u32)((f32)(u8)(u32)*(f32 *)(g + 0x14A8) * k);
        a3 = (u8)(u32)f20;
        t3 = (s32)(*(f32 *)(s0 + 0x6C) * 4096.0f);
        func_001F0418(a0, a1, a2, a3, 0x40, 0x40, 0, t3, 0, s0[0x91], (s32)(g + 0x14B0 + (s0[0x90] << 4)),
                      *(f32 *)(s0 + 0x20), *(f32 *)(s0 + 0x24), *(f32 *)(s0 + 0x28),
                      D_00385498, D_00385498, 0x1.fcp-1f, 0x1.fcp-1f, ang);
    }
}
