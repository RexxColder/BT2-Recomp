#include "common.h"
#include "sys/dma.h"

extern u32 D_003B0A84;

/* The 0x70-byte DMA packet built on the stack (words at sp+0x70..0xDF) and sent with Dma_AddData. */
void func_0010C4E0(void) {
    u32 pkt[28];
    u32 a0;

    a0 = (D_003B0A84 & 1) ? 0x80000 : 0x80070;

    pkt[0] = 0x10000006;
    pkt[1] = 0;
    pkt[2] = 0x10000000;
    pkt[3] = 0x50000006;
    pkt[4] = 0x8005;
    pkt[5] = 0x10000000;
    pkt[6] = 0xE;
    pkt[7] = 0;
    pkt[8] = a0;
    pkt[9] = 0;
    pkt[10] = 0x4C;
    pkt[11] = 0;
    pkt[12] = 0x7000;
    pkt[13] = 0x7200;
    pkt[14] = 0x18;
    pkt[15] = 0;
    pkt[16] = 0x1FF0000;
    pkt[17] = 0x1BF0000;
    pkt[18] = 0x40;
    pkt[19] = 0;
    pkt[20] = 0x44;
    pkt[21] = 0;
    pkt[22] = 0x42;
    pkt[23] = 0;
    pkt[24] = 0x30000;
    pkt[25] = 0;
    pkt[26] = 0x47;
    pkt[27] = 0;

    Dma_AddData(pkt, 0x70);
}
