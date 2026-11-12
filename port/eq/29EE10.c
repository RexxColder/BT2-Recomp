#include "common.h"

s32 Dma_Alloc(s32 arg0);

/* asm: v0 = Dma_Alloc result at jr ra: returns the packet (was void: Vu1Node_Draw wrote the batch matrices
   through garbage, the VU1 got a stale header -> runaway program on water stages, B19) */
s32 Vu1Pkt_CallProg8(s32 arg0) {
    s32 temp_v0;

    temp_v0 = Dma_Alloc(0xC0);
    *(s32 *)(temp_v0 + 0x4) = (arg0 + 0xF0) & 0x0FFFFFFF;
    *(s32 *)(temp_v0 + 0x0) = 0x5000000B;
    *(s32 *)(temp_v0 + 0x8) = 0x10000000;
    *(s32 *)(temp_v0 + 0xC) = 0x6C0A0000;
    *(s32 *)(temp_v0 + 0xB0) = 0x15000000;
    *(s32 *)(temp_v0 + 0xB4) = 0x03000012;
    *(s32 *)(temp_v0 + 0xB8) = 0x020001F7;
    *(s32 *)(temp_v0 + 0xBC) = 0;
    return temp_v0;
}
