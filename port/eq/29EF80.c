#include "common.h"

s32 Dma_AddRef(u8 *arg0, s32 arg1);
u8 *Dma_Alloc(s32 arg0);
void func_003126C8(u8 *arg0, u8 *arg1);
void *memset(void *arg0, s32 arg1, u32 arg2);
void sceVu0CopyMatrix(u8 *arg0, u8 *arg1);
void sceVu0MulMatrix(u8 *arg0, u8 *arg1, u8 *arg2);
extern u8 D_002C2D30[] __attribute__((section(".data")));
extern u8 D_0033DED0[] __attribute__((section(".data")));

void func_0029EF80(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *temp_v0;

    Dma_AddRef(D_0033DED0, (s32)(D_002C2D30 - D_0033DED0));
    temp_v0 = Dma_Alloc(0x130);
    memset(temp_v0, 0, 0x130);
    sceVu0CopyMatrix(temp_v0 + 0x90, arg0 + 0xC0);
    sceVu0MulMatrix(temp_v0 + 0x10, arg0 + 0x40, arg0);
    sceVu0MulMatrix(temp_v0 + 0x50, arg0 + 0x80, arg0);
    sceVu0CopyMatrix(temp_v0 + 0xD0, arg1);
    func_003126C8(temp_v0 + 0x110, arg2);
    *(s32 *)(temp_v0 + 0) = 0x10000012;
    *(s32 *)(temp_v0 + 8) = 0x10000000;
    *(s32 *)(temp_v0 + 0xC) = 0x6C110000;
    *(s32 *)(temp_v0 + 0x124) = 0x03000092;
    *(s32 *)(temp_v0 + 0x128) = 0x020001B2;
    *(s32 *)(temp_v0 + 0x12C) = 0;
    *(s32 *)(temp_v0 + 4) = 0;
    *(s32 *)(temp_v0 + 0x120) = 0;
}
