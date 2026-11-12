#include "common.h"
#include "sys/dma.h"

extern s32 D_003B0A84 __attribute__((section(".data")));

/* 0x0010C298: builds a 0x50-byte DMA packet of five qwords on the stack and hands it to
 * Dma_AddData. Word 0 is 0x10000004, word 1 0x50000004:0x10000000, word 2 0x10000000:0x8003,
 * then 0xE, the bus address (0x80070, or 0x80000 when the low bit of D_003B0A84 is set), 0x4C,
 * 0x30000, 0x47, 0x44 and 0x43 (each in the low word, the high word zero). */
void func_0010C298(void) {
    s64 pkt[10];
    s32 a1;

    a1 = (D_003B0A84 & 1) != 0 ? 0x80000 : 0x80070;

    pkt[0] = (s64)0x10000004;
    pkt[1] = ((s64)0x50000004 << 32) | (s64)0x10000000;
    pkt[2] = ((s64)0x10000000 << 32) | (s64)0x8003;
    pkt[3] = (s64)0xE;
    pkt[4] = (s64)a1;
    pkt[5] = (s64)0x4C;
    pkt[6] = (s64)0x30000;
    pkt[7] = (s64)0x47;
    pkt[8] = (s64)0x44;
    pkt[9] = (s64)0x43;

    Dma_AddData(pkt, 0x50);
}
