#include "common.h"

s32 rand(void);
void sceVu0Normalize(s32 a0, s32 a1);
void func_00312680(f32 f12, s32 a0, s32 a1);
extern f32 D_00384230;
extern f32 D_00384234;
extern u8 EftBurst_UpdateSpark[] __attribute__((section(".data")));
extern u8 func_00134280[] __attribute__((section(".data")));
extern u8 *gEftBurst;

void func_00132D78(u8 *arg0, s32 arg1) {
    f32 f21;
    f32 f22;
    f32 f3;
    s32 v;
    s32 a3;
    u8 *s1;

    f22 = (f32)arg1;
    s1 = arg0 + 0x10;
    *(s32 *)(arg0 + 0) = 0;
    *(f32 *)(arg0 + 8) = -40.0f - f22;
    *(s32 *)(arg0 + 4) = 0;
    f21 = D_00384230;
    *(s32 *)(arg0 + 0xC) = 0;
    *(f32 *)(arg0 + 0x10) = (f32)((rand() & 0xFF) - 0x7F) * f21 * 0.0078125f;
    *(f32 *)(arg0 + 0x14) = (f32)((rand() & 0xFF) - 0x7F) * f21 * 0.0078125f;
    v = rand();
    *(s32 *)(arg0 + 0x1C) = 0;
    *(f32 *)(arg0 + 0x18) = -(f32)(v & 0x7F) * 0.0078125f - 1.0f;
    sceVu0Normalize((s32)s1, (s32)s1);
    func_00312680(1.0f, (s32)s1, (s32)s1);
    a3 = 0x20 - arg1;
    *(f32 *)(arg0 + 0x18) = *(f32 *)(arg0 + 0x18) - 0.5f;
    *(s32 *)(arg0 + 0x48) = *(s32 *)(*(u8 **)0x00388714 + 0x10) + 0x140;
    *(s32 *)(arg0 + 0x58) = (s32)func_00134280;
    *(s32 *)(arg0 + 0x50) = 0x42;
    *(s32 *)(arg0 + 0x44) = a3;
    *(s32 *)(arg0 + 0x5C) = 0x306070;
    *(s32 *)(arg0 + 0x60) = 0x10;
    f22 = f22 * D_00384234;
    f3 = 17.0f - f22;
    f3 = f3 + *(f32 *)(gEftBurst + 0x10);
    *(f32 *)(arg0 + 0x4C) = f3;
    *(s32 *)(arg0 + 0x54) = (s32)EftBurst_UpdateSpark;
    *(s32 *)(arg0 + 0x40) = a3;
}
