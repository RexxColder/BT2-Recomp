#include "common.h"

extern f32 D_00384254;
extern f32 D_00387730 __attribute__((section(".data")));
extern u8 *D_00388714 __attribute__((section(".data")));
void EftBurst_UpdateRing(void);
void func_00133E28(void);

void func_00133280(u8 *arg0) {
    u8 *temp_v1;

    *(s32 *)(arg0 + 0x50) = 0x4A;
    temp_v1 = arg0 + 0x10;
    *(s32 *)(arg0 + 0x48) = *(s32 *)(D_00388714 + 0x10) + 0x40;
    *(s32 *)(arg0 + 0x44) = 8;
    *(f32 *)(arg0 + 0x4C) = D_00384254;
    *(s32 *)(arg0 + 0x5C) = 0x708080;
    *(s32 *)(arg0 + 0x60) = 0x40;
    *(f32 *)(arg0 + 0x68) = 70.0f;
    *(f32 *)(arg0 + 0) = -5.0f;
    *(f32 *)(arg0 + 8) = -51.0f;
    *(s32 *)(arg0 + 0x40) = 8;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    *(f32 *)(temp_v1 + 8) = D_00387730;
    *(s32 *)(temp_v1 + 0xC) = 0;
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(temp_v1 + 4) = 0;
    *(s32 *)(arg0 + 0x58) = (s32)func_00133E28;
    *(s32 *)(arg0 + 0x54) = (s32)EftBurst_UpdateRing;
}
