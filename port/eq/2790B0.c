#include "common.h"

extern u8 D_00376D30[] __attribute__((section(".data")));

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void Dma_AddData(u8 *arg0, s32 arg1);

void func_002790B0(void) {
    u8 buf[0x80];

    memcpy(buf, D_00376D30, 0x80);
    Dma_AddData(buf, 0x80);
}
