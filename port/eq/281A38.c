#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *Dma_BeginDirect(void);
void Dma_EndDirect(void *arg0, s64 arg1, s32 arg2, s64 arg3);

extern s32 D_003B0A84 __attribute__((section(".data")));

void func_00281A38(s32 arg0, u8 *arg1) {
    s64 *d;
    s64 a1v;
    s64 a3v;

    d = (s64 *)Dma_BeginDirect();

    d[0] = ((s64)0x10000000 << 32) | 0xA;
    d[1] = 0xE;
    d[2] = (s64)arg0 | ((s64)0xFF00 << 48);
    d[3] = 0x4C;
    d[4] = (s64)0x1310000E0;
    d[5] = 0x4E;
    d[6] = ((s64)0x7F00 << 32) | 0x7F00;
    d[7] = 0x18;
    d[8] = (s64)0x1F0000001F0000;
    d[9] = 0x40;
    d[10] = (s64)0x7C0007C00A;
    d[11] = 8;
    d[12] = 0x30000;
    d[13] = 0x47;
    d[14] = 0x44;
    d[15] = 0x42;
    d[16] = 0;
    d[17] = 0x14;
    d[18] = 0x46;
    d[19] = 0;

    a3v = (s64)0xFE00 << 46;
    d[20] = (s64)W(arg1, 0) | a3v | (((s64)W(arg1, 8) << 16) | ((s64)W(arg1, 4) << 8)) |
            ((s64)W(arg1, 0xC) << 24);
    d[21] = 1;
    d[22] = ((s64)0x24000000 << 32) | 1;
    d[23] = 0x55;
    d[24] = 0x7F007F00;
    d[25] = (s64)0x81008100;
    d[26] = ((s64)0x10000000 << 32) | 6;
    d[27] = 0xE;
    d[28] = ((D_003B0A84 & 1) != 0) ? 0x80000 : 0x80070;
    d[29] = 0x4C;
    d[30] = (s64)0x1310000E0;
    d[31] = 0x4E;
    a1v = ((s64)0x7200 << 32) | 0x7000;
    d[32] = a1v;
    d[33] = 0x18;
    a3v = (((s64)0x1BF0000 << 16) | 0x1FF) << 16;
    d[34] = a3v;
    d[35] = 0x40;
    d[36] = 5;
    d[37] = 8;
    d[38] = 0x60;
    d[39] = 0x14;

    Dma_EndDirect((void *)(d + 40), a1v, 0x80000, a3v);
}
