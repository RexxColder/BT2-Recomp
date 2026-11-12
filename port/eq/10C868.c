#include "common.h"

extern s32 D_003B0A84;
void Dma_AddData(void *src, s32 size);

/* 0x0010C868: a 0x30-byte DMA packet (12 words) built on the stack, the 9th word is 0x80000 when D_003B0A84 is odd, else 0x80070. */
void func_0010C868(void) {
    u32 buf[24];
    s32 flag;

    flag = D_003B0A84 & 1;
    buf[0] = 0x10000002;
    buf[1] = 0;
    buf[2] = 0x10000000;
    buf[3] = 0x50000002;
    buf[4] = 0x8001;
    buf[5] = 0x10000000;
    buf[6] = 0xE;
    buf[7] = 0;
    buf[8] = flag ? 0x80000 : 0x80070;
    buf[9] = 0;
    buf[10] = 0x4D;
    buf[11] = 0;
    Dma_AddData(buf, 0x30);
}
