#include "common.h"
#include "sys/dma.h"

extern u32 D_003B0A84;

/* The 0x70-byte DMA packet built on the stack (words at sp+0x70..0xDF) and sent with Dma_AddData. */
void func_0010BB80(s64 arg0) {
    u32 pkt[28];
    s64 q;
    u32 a3;

    q = (arg0 << 4) | 0x33009;
    a3 = (D_003B0A84 & 1) ? 0x80000 : 0x80070;

    pkt[0] = 0x10000006;
    pkt[1] = 0;
    pkt[2] = 0x10000000;
    pkt[3] = 0x50000006;
    pkt[4] = 0x8005;
    pkt[5] = 0x10000000;
    pkt[6] = 0xE;
    pkt[7] = 0;
    pkt[8] = a3;
    pkt[9] = 0xFF000000;
    pkt[10] = 0x4D;
    pkt[11] = 0;
    pkt[12] = 1;
    pkt[13] = 0;
    pkt[14] = 0x4A;
    pkt[15] = 0;
    pkt[16] = 1;
    pkt[17] = 0;
    pkt[18] = 0x4B;
    pkt[19] = 0;
    pkt[20] = (u32)q;
    pkt[21] = (u32)(q >> 32);
    pkt[22] = 0x47;
    pkt[23] = 0;
    pkt[24] = 0x44;
    pkt[25] = 0;
    pkt[26] = 0x43;
    pkt[27] = 0;

    Dma_AddData(pkt, 0x70);
}
