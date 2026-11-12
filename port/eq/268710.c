#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);
extern s32 D_003B0A84 __attribute__((section(".data")));

void func_00268710(void) {
    s32 sp[48];
    s32 e;

    e = (D_003B0A84 & 1) ? 0x80000 : 0x80070;
    sp[0] = 0x1000000B;
    sp[1] = 0;
    sp[2] = 0x10000000;
    sp[3] = 0x5000000B;
    sp[4] = 0x800A;
    sp[5] = 0x10000000;
    sp[6] = 0xE;
    sp[7] = 0;
    sp[8] = e;
    sp[9] = 0;
    sp[10] = 0x4C;
    sp[11] = 0;
    sp[12] = 0x310000E0;
    sp[13] = 1;
    sp[14] = 0x4E;
    sp[15] = 0;
    sp[16] = 0xA1;
    sp[17] = 0x80;
    sp[18] = 0x42;
    sp[19] = 0;
    sp[20] = 0x5400F;
    sp[21] = 0;
    sp[22] = 0x47;
    sp[23] = 0;
    sp[24] = 0;
    sp[25] = 0;
    sp[26] = 0x14;
    sp[27] = 0;
    sp[28] = 1;
    sp[29] = 0;
    sp[30] = 0x4A;
    sp[31] = 0;
    sp[32] = 5;
    sp[33] = 0;
    sp[34] = 8;
    sp[35] = 0;
    sp[36] = 1;
    sp[37] = 0;
    sp[38] = 0x46;
    sp[39] = 0;
    sp[40] = 0x8080;
    sp[41] = 0x80;
    sp[42] = 0x3B;
    sp[43] = 0;
    sp[44] = 0x20112A00;
    sp[45] = 6;
    sp[46] = 6;
    sp[47] = 0;
    Dma_AddData((s32)sp, 0xC0);
}
