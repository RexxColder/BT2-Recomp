#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1, s64 arg2, s64 arg3);
extern s32 D_003B0A84 __attribute__((section(".data")));

void func_00276150(void) {
    s32 tab[40];
    s32 dma[40];
    s64 a2;
    s64 a3;
    s32 i;

    tab[0] = 0x10000009;
    tab[1] = 0;
    tab[2] = 0x10000000;
    tab[3] = 0x50000009;
    tab[4] = 0x8008;
    tab[5] = 0x10000000;
    tab[6] = 0xE;
    tab[7] = 0;
    tab[8] = (D_003B0A84 & 1) ? 0x80000 : 0x80070;
    tab[9] = 0;
    tab[10] = 0x4C;
    tab[11] = 0;
    tab[12] = 0x310000E0;
    tab[13] = 0;
    tab[14] = 0x4E;
    tab[15] = 0;
    tab[16] = 0x44;
    tab[17] = 0;
    tab[18] = 0x42;
    tab[19] = 0;
    tab[20] = 0x507FB;
    tab[21] = 0;
    tab[22] = 0x47;
    tab[23] = 0;
    tab[24] = 0x60;
    tab[25] = 0;
    tab[26] = 0x14;
    tab[27] = 0;
    tab[28] = 0;
    tab[29] = 0;
    tab[30] = 0x4A;
    tab[31] = 0;
    tab[32] = 0;
    tab[33] = 0;
    tab[34] = 8;
    tab[35] = 0;
    tab[36] = 1;
    tab[37] = 0;
    tab[38] = 0x46;
    tab[39] = 0;

    for (i = 0; i < 40; i++) {
        dma[i] = tab[i];
    }
    /* a2/a3 are the last two 64-bit loads of the copy loop (table words 36..39) */
    a2 = (s64)(u32)tab[36] | ((s64)(u32)tab[37] << 32);
    a3 = (s64)(u32)tab[38] | ((s64)(u32)tab[39] << 32);
    Dma_AddData((s32)dma, 0xA0, a2, a3);
}
