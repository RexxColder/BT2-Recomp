#include "common.h"

void Dma_AddRef(void *arg0, s32 arg1);
u8 *Dma_Alloc(s32 arg0);
void Vu0Clip_StoreMtx(u8 *arg0);
void Vu0Screen_StoreMtx(u8 *arg0);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
extern u8 D_002C04F0[] __attribute__((section(".data")));
extern u8 D_002C1180[] __attribute__((section(".data")));

void Vu1Pkt_LoadProg4(s32 arg0) {
    u8 *temp_v0;

    Dma_AddRef(D_002C04F0, (s32)(D_002C1180 - D_002C04F0));
    temp_v0 = Dma_Alloc(0xE0);
    sceVu0CopyMatrix((s32)(temp_v0 + 0x90), arg0);
    Vu0Screen_StoreMtx(temp_v0 + 0x10);
    Vu0Clip_StoreMtx(temp_v0 + 0x50);
    *(s32 *)(temp_v0 + 0) = 0x1000000D;
    *(s32 *)(temp_v0 + 8) = 0x10000000;
    *(s32 *)(temp_v0 + 0xC) = 0x6C0C0000;
    *(s32 *)(temp_v0 + 0xD4) = 0x0300008D;
    *(s32 *)(temp_v0 + 0xD8) = 0x020001B4;
    *(s32 *)(temp_v0 + 0xDC) = 0;
    *(s32 *)(temp_v0 + 4) = 0;
    *(s32 *)(temp_v0 + 0xD0) = 0;
}
