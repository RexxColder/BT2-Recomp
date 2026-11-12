#include "common.h"

extern u8 D_00388D48[] __attribute__((section(".data")));

void func_00262280(void) {
    u8 *temp_a0;
    u8 *p;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_t0;

    p = *(u8 **)(D_00388D48 + 0x8);
    temp_a0 = *(u8 **)(D_00388D48 + 0x4) + (*(s32 *)(D_00388D48 + 0x10) * 0x30);
    temp_a2 = *(s32 *)(temp_a0 + 0x24);
    *(s32 *)(temp_a0 + 0x24) = *(s32 *)(p + 0x0);
    temp_t0 = *(s32 *)(temp_a0 + 0x18);
    temp_a3 = *(s32 *)(temp_a0 + 0xC);
    *(s32 *)(temp_a0 + 0x18) = *(s32 *)(p + 0x4);
    *(s32 *)(temp_a0 + 0xC) = *(s32 *)(p + 0x8);
    *(s32 *)(p + 0x0) = temp_a2;
    *(s32 *)(p + 0x4) = temp_t0;
    *(s32 *)(p + 0x8) = temp_a3;
}
