#include "common.h"

u8 *Dma_BeginDirect(s32 arg0);
s32 Dma_EndDirect(u8 *arg0, s64 arg1, s32 arg2, s64 arg3);
extern u8 gColorFade[] __attribute__((section(".data")));

void func_002437E8(void) {
    s32 temp_s0;
    s32 temp_s0_2;
    s64 temp_a1;
    s64 temp_a3;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;

    temp_s0 = (*(s32 *)(gColorFade + 0x10) >= 0x81) ? 0x80 : *(s32 *)(gColorFade + 0x10);
    temp_s0_2 = (temp_s0 < 0) ? 0 : temp_s0;
    temp_v0 = Dma_BeginDirect(0x80);
    *(s64 *)(temp_v0 + 0) = (s64)0x1000000000008002ULL;
    *(s64 *)(temp_v0 + 8) = 0xE;
    temp_v0_2 = temp_v0 + 0x10;
    *(s64 *)(temp_v0_2 + 8) = 0x42;
    *(s64 *)(temp_v0 + 0x10) = 0x44;
    temp_v0_3 = temp_v0_2 + 0x10;
    *(s64 *)(temp_v0_2 + 0x10) = 0x30000;
    *(s64 *)(temp_v0_3 + 8) = 0x47;
    temp_v0_4 = temp_v0_3 + 0x10;
    *(s64 *)(temp_v0_4 + 8) = 0x5510;
    *(s64 *)(temp_v0_3 + 0x10) = (s64)0x4400000000008001ULL;
    temp_v0_5 = temp_v0_4 + 0x10;
    *(s64 *)(temp_v0_4 + 0x10) = 0x46;
    temp_a3 = (s64)0x8E009000ULL;
    temp_a1 = (s64)*(s32 *)(gColorFade + 8) << 8;
    *(s64 *)(temp_v0_5 + 8) = (s64)(*(s32 *)(gColorFade + 4) | ((s64)temp_s0_2 << 0x18) | (((s64)*(s32 *)(gColorFade + 0xC) << 0x10) | temp_a1));
    temp_v0_6 = temp_v0_5 + 0x10;
    *(s64 *)(temp_v0_5 + 0x10) = 0x72007000;
    *(s64 *)(temp_v0_6 + 8) = temp_a3;
    Dma_EndDirect(temp_v0_6 + 0x10, temp_a1, 0x72007000, temp_a3);
}
