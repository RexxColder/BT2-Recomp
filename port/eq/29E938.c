#include "common.h"

void Dma_AddRef(void *arg0, s32 arg1);
u8 *Dma_Alloc(s32 arg0);
void Vu0Clip_StoreMtx(void *arg0);
void Vu0Screen_StoreMtx(void *arg0);
void sceVu0CopyMatrix(void *arg0, void *arg1);
void sceVu0UnitMatrix(void *arg0);
extern u8 D_002C1180[] __attribute__((section(".data")));
extern u8 D_0033DED0[] __attribute__((section(".data")));

void func_0029E938(void *arg0) {
    u8 *temp_v0;

    Dma_AddRef(D_002C1180, (s32)(D_0033DED0 - D_002C1180));
    temp_v0 = Dma_Alloc(0x120);
    sceVu0UnitMatrix(temp_v0 + 0x10);
    Vu0Screen_StoreMtx(temp_v0 + 0x50);
    sceVu0CopyMatrix(temp_v0 + 0xD0, arg0);
    Vu0Clip_StoreMtx(temp_v0 + 0x90);
    *(s32 *)(temp_v0 + 0) = 0x10000011;
    *(s32 *)(temp_v0 + 8) = 0x10000000;
    *(s32 *)(temp_v0 + 0xC) = 0x6C100000;
    *(s32 *)(temp_v0 + 0x114) = 0x0300008D;
    *(s32 *)(temp_v0 + 0x118) = 0x020001B4;
    *(s32 *)(temp_v0 + 0x11C) = 0;
    *(s32 *)(temp_v0 + 4) = 0;
    *(s32 *)(temp_v0 + 0x110) = 0;
}
