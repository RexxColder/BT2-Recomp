#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);
extern s32 D_003B0A84 __attribute__((section(".data")));

void HudTeam_GsEndMask(void) {
    s32 dst[24];
    s32 tmpl[24];
    s32 i;

    tmpl[0] = 0x10000005;
    tmpl[1] = 0;
    tmpl[2] = 0x10000000;
    tmpl[3] = 0x50000005;
    tmpl[4] = 0x8004;
    tmpl[5] = 0x10000000;
    tmpl[6] = 0xE;
    tmpl[7] = 0;
    tmpl[8] = 0x30000;
    tmpl[9] = 0;
    tmpl[10] = 0x47;
    tmpl[11] = 0;
    tmpl[12] = (D_003B0A84 & 1) ? 0x80000 : 0x80070;
    tmpl[13] = 0;
    tmpl[14] = 0x4D;
    tmpl[15] = 0;
    tmpl[16] = 0;
    tmpl[17] = 0;
    tmpl[18] = 0x4B;
    tmpl[19] = 0;
    tmpl[20] = 0x30000;
    tmpl[21] = 0;
    tmpl[22] = 0x48;
    tmpl[23] = 0;

    for (i = 0; i < 24; i++) {
        dst[i] = tmpl[i];
    }
    Dma_AddData((s32)dst, 0x60);
}
