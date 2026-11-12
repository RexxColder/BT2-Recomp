#include "common.h"

s32 Dma_AddRef(u8 *arg0, s32 arg1);
u8 *Dma_Alloc(s32 arg0);
extern u8 D_002C04F0[] __attribute__((section(".data")));
extern u8 D_0033BE70[] __attribute__((section(".data")));
extern u8 D_0033C190[] __attribute__((section(".data")));

u8 *func_0029E6D0(s32 arg0) {
    u8 *temp_v0;

    if (arg0 & 0xFF) {
        Dma_AddRef(D_0033C190, (s32)(D_002C04F0 - D_0033C190));
    } else {
        Dma_AddRef(D_0033BE70, (s32)(D_0033C190 - D_0033BE70));
    }
    temp_v0 = Dma_Alloc(0x150);
    *(s32 *)(temp_v0 + 0) = 0x10000014;
    *(s32 *)(temp_v0 + 8) = 0x10000000;
    *(s32 *)(temp_v0 + 0xC) = 0x6C130000;
    *(s32 *)(temp_v0 + 0x144) = 0x03000013;
    *(s32 *)(temp_v0 + 0x148) = 0x020001F6;
    *(s32 *)(temp_v0 + 0x14C) = 0;
    *(s32 *)(temp_v0 + 4) = 0;
    *(s32 *)(temp_v0 + 0x140) = 0;
    return temp_v0;
}
