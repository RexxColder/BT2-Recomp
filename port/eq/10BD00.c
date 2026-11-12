#include "common.h"

extern u8 D_0036C588[];
void Dma_AddData(void *src, s32 size);
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x0010BD00: copies the 0x70-byte constant block D_0036C588 to a stack buffer and hands it to Dma_AddData. */
void func_0010BD00(void) {
    u8 buf[0x70];

    memcpy(buf, D_0036C588, 0x70);
    Dma_AddData(buf, 0x70);
}
