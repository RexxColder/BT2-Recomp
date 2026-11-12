#include "m2c_macros.h"

void *memcpy(void *, const void *, u32);
void Dma_AddData(void *, s32);
extern u8 D_004218A8[] __attribute__((section(".data")));

void func_003B5840(void) {
    u8 buf[0x80];

    memcpy(buf, D_004218A8, 0x80);
    Dma_AddData(buf, 0x80);
}
