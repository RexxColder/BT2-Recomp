#include "common.h"

s32 rand(void *arg0, s32 arg1);
extern f32 D_00387734 __attribute__((section(".data")));
extern void *D_00388714 __attribute__((section(".data")));
extern u8 EftBurst_UpdateGlow[] __attribute__((section(".data")));
extern u8 func_00133AD8[] __attribute__((section(".data")));

void func_00133328(u8 *arg0) {
    s32 temp_v0;
    u8 *temp_v1;

    temp_v1 = arg0 + 0x10;
    *(f32 *)(arg0 + 8) = -51.0f;
    *(s32 *)(arg0 + 0) = 0;
    *(s32 *)(arg0 + 4) = 0;
    *(s32 *)(arg0 + 0xC) = 0;
    *(f32 *)(temp_v1 + 8) = D_00387734;
    *(s32 *)(temp_v1 + 0xC) = 0;
    *(s32 *)(arg0 + 0x10) = 0;
    *(s32 *)(temp_v1 + 4) = 0;
    *(f32 *)(arg0 + 0x4C) = 40.0f;
    *(s32 *)(arg0 + 0x50) = 3;
    *(s32 *)(arg0 + 0x48) = *(s32 *)((u8 *)D_00388714 + 0x10) + 0x100;
    /* the asm passes the %hi part of &D_00388714 in $a0 (lui only) */
    temp_v0 = (rand((void *)((((u32)&D_00388714) + 0x8000) & 0xFFFF0000), 3) & 0xF) + 0x2F;
    *(u8 **)(arg0 + 0x54) = EftBurst_UpdateGlow;
    *(s32 *)(arg0 + 0x44) = temp_v0;
    *(f32 *)(arg0 + 0x4C) = 10.0f;
    *(u8 **)(arg0 + 0x58) = func_00133AD8;
    *(s32 *)(arg0 + 0x40) = temp_v0;
}
