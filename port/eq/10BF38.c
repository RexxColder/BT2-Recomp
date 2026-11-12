#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);
extern s32 D_003B0A84 __attribute__((section(".data")));

void HudTeam_GsBeginMask(void) {
    s32 d[24];

    d[0] = 0x10000005;
    d[1] = 0;
    d[2] = 0x10000000;
    d[3] = 0x50000005;
    d[4] = 0x8004;
    d[5] = 0x10000000;
    d[6] = 0xE;
    d[7] = 0;
    d[8] = 0x34000;
    d[9] = 0;
    d[10] = 0x47;
    d[11] = 0;
    d[12] = (D_003B0A84 & 1) ? 0x80000 : 0x80070;
    d[13] = 0xFFFFFF;
    d[14] = 0x4D;
    d[15] = 0;
    d[16] = 1;
    d[17] = 0;
    d[18] = 0x4B;
    d[19] = 0;
    d[20] = 0x3000F;
    d[21] = 0;
    d[22] = 0x48;
    d[23] = 0;
    Dma_AddData((s32)d, 0x60);
}
