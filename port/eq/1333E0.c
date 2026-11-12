#include "common.h"

extern f32 D_00384258;
extern f32 D_0038425C;
extern f32 D_00384260;
extern u8 *D_00388714 __attribute__((section(".data")));
extern u8 EftBurst_UpdateDebris[] __attribute__((section(".data")));
extern u8 func_00134280[] __attribute__((section(".data")));

void *memset(void *, s32, u32);
s32 rand(void);
void func_00312650(f32 *arg0, f32 *arg1, u8 *arg2);
void sceVu0Normalize(f32 *arg0, f32 *arg1);
void func_00312680(f32 farg0, f32 *arg1, f32 *arg2);
void func_00312638(u8 *arg0, u8 *arg1, f32 *arg2);

void EftBurst_InitDebris(u8 *arg0) {
    f32 sp[4];
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    *(s32 *)(arg0 + 0x50) = 0x4B;
    *(f32 *)(arg0 + 0x4C) = (2.0f * (f32)(rand() & 0x7F) * 0.0078125f) + 4.0f;
    *(f32 *)(arg0 + 0x00) = (f32)((rand() & 0xFF) - 0x7F) * 8.0f * 0.0078125f;
    *(f32 *)(arg0 + 0x04) = (f32)((rand() & 0xFF) - 0x7F) * 8.0f * 0.0078125f;
    temp_v0 = rand() & 0x7F;
    *(s32 *)(arg0 + 0x0C) = 0;
    *(f32 *)(arg0 + 0x08) = (2.0f * -(f32)temp_v0 * 0.0078125f) - 51.0f;
    *(f32 *)(arg0 + 0x10) = (f32)((rand() & 0xFF) - 0x7F) * D_00384258 * 0.0078125f;
    *(f32 *)(arg0 + 0x14) = (f32)((rand() & 0xFF) - 0x7F) * D_00384258 * 0.0078125f;
    temp_v0_2 = rand() & 0x7F;
    *(s32 *)(arg0 + 0x1C) = 0;
    *(f32 *)(arg0 + 0x18) = -(f32)temp_v0_2 * D_0038425C * 0.0078125f;

    memset(sp, 0, 0x10);
    sp[2] = 45.0f;
    func_00312650(sp, sp, arg0);
    sp[2] = 0.0f;
    sceVu0Normalize(sp, sp);
    func_00312680(D_00384260, sp, sp);
    func_00312638(arg0 + 0x10, arg0 + 0x10, sp);

    temp_v0_3 = (rand() & 3) + 0x1F;
    *(s32 *)(arg0 + 0x40) = temp_v0_3;
    *(s32 *)(arg0 + 0x44) = temp_v0_3;
    *(s32 *)(arg0 + 0x54) = (s32)EftBurst_UpdateDebris;
    *(s32 *)(arg0 + 0x58) = (s32)func_00134280;
    *(s32 *)(arg0 + 0x48) = *(s32 *)(D_00388714 + 0x10) + 0xC0;
    *(s32 *)(arg0 + 0x5C) = 0x606060;
    *(s32 *)(arg0 + 0x60) = 0;
}
