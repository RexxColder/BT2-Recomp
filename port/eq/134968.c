#include "common.h"

extern s32 D_003B0A84 __attribute__((section(".data")));

u8 *EftBurst_PutModelEnvEnd(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;

    *(s64 *)(arg0 + 0x0) = ((s64)0x10000000 << 32) | 0x8005;
    *(s64 *)(arg0 + 0x8) = 0xE;
    temp_a0_2 = arg0 + 0x10;
    *(s64 *)(temp_a0_2 + 0x8) = 0x14;
    *(s64 *)(arg0 + 0x10) = 0;
    temp_a0_3 = temp_a0_2 + 0x10;
    *(s64 *)(temp_a0_2 + 0x10) = 0x30000;
    *(s64 *)(temp_a0_3 + 0x8) = 0x47;
    temp_a0_4 = temp_a0_3 + 0x10;
    *(s64 *)(temp_a0_3 + 0x10) = 0x310000E0;
    *(s64 *)(temp_a0_4 + 0x8) = 0x4E;
    temp_a0_5 = temp_a0_4 + 0x10;
    *(s64 *)(temp_a0_4 + 0x10) = 1;
    *(s64 *)(temp_a0_5 + 0x8) = 0x46;
    temp_a0 = temp_a0_5 + 0x10;
    *(s64 *)(temp_a0 + 0x8) = 0x4C;
    *(s64 *)(temp_a0_5 + 0x10) = (s64)((D_003B0A84 & 1) ? 0x80000 : 0x80070);
    return temp_a0 + 0x10;
}
