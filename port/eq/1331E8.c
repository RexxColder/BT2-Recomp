#include "common.h"

extern f32 D_0038772C __attribute__((section(".data")));
extern u8 *D_00388714 __attribute__((section(".data")));
void EftBurst_UpdateFlash(void);
void func_00133E28(void);

void func_001331E8(u8 *arg0) {
    u8 *t;

    t = arg0 + 0x10;
    *(s32 *)(arg0 + 0x50) = 0x7A;
    *(s32 *)(arg0 + 0x48) = *(s32 *)(D_00388714 + 0x10);
    *(s32 *)(arg0 + 0x44) = 0xA;
    *(f32 *)(arg0 + 0x4C) = 10.0f;
    *(f32 *)(arg0 + 0x8) = -55.0f;
    *(s32 *)(arg0 + 0x40) = 0xA;
    *(s32 *)(arg0 + 0x0) = 0;
    *(s32 *)(arg0 + 0x4) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    *(f32 *)(t + 0x8) = D_0038772C;
    *(s32 *)(t + 0xC) = 0;
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(t + 0x4) = 0;
    *(s32 *)(arg0 + 0x58) = (s32)func_00133E28;
    *(s32 *)(arg0 + 0x60) = 0x80;
    *(s32 *)(arg0 + 0x5C) = 0x808080;
    *(s32 *)(arg0 + 0x54) = (s32)EftBurst_UpdateFlash;
}
