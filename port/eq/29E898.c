#include "common.h"

void *Dma_Alloc(s32 arg0);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);

void Vu1Pkt_CallProg5(s32 arg0, s32 arg1) {
    u8 *temp_v0;

    temp_v0 = (u8 *)Dma_Alloc(0x60);
    sceVu0CopyMatrix((s32)(temp_v0 + 0x10), arg1);
    *(s32 *)(temp_v0 + 0x4) = arg0 & 0x0FFFFFFF;
    *(s32 *)(temp_v0 + 0x0) = 0x50000005;
    *(s32 *)(temp_v0 + 0x8) = 0x10000000;
    *(s32 *)(temp_v0 + 0xC) = 0x6C040000;
    *(s32 *)(temp_v0 + 0x50) = 0x15000000;
    *(s32 *)(temp_v0 + 0x54) = 0x0300008D;
    *(s32 *)(temp_v0 + 0x58) = 0x020001B4;
    *(s32 *)(temp_v0 + 0x5C) = 0;
}
