#include "common.h"

void *Dma_BeginDirect(void);
void Dma_EndDirect(void *arg0, s32 arg1, s64 arg2, s32 arg3);
extern s32 D_003B0A84 __attribute__((section(".data")));

void EftBurst_ClearAlphaPlane(void) {
    s64 *q;
    s64 a1_70;
    s64 a1_nolow;
    s64 temp_a2;
    s64 t0;

    q = (s64 *)Dma_BeginDirect();
    a1_70 = (((s64)0xFFFFFF << 16) | 8) << 16;
    a1_70 = a1_70 | 0x70;
    a1_nolow = (((s64)0xFFFFFF << 16) | 8) << 16;
    temp_a2 = ((s64)0x7200 << 32) | 0x7000;
    t0 = (((s64)0x01BF0000 << 16) | 0x1FF) << 16;

    q[0] = ((s64)0x10000000 << 32) | 0x8009;
    q[1] = 0xE;
    q[2] = 0x44;
    q[3] = 0x43;
    q[4] = 0x60;
    q[5] = 0x15;
    q[6] = 0;
    q[7] = 0x4B;
    q[8] = 0x30000;
    q[9] = 0x48;
    q[10] = 5;
    q[11] = 9;
    q[12] = (((s64)((1 << 16) | 0x3100)) << 16) | 0xE0;
    q[13] = 0x4F;
    q[14] = (D_003B0A84 & 1) ? a1_nolow : a1_70;
    q[15] = 0x4D;
    q[16] = temp_a2;
    q[17] = 0x19;
    q[18] = t0;
    q[19] = 0x41;
    q[20] = ((s64)0x44000000 << 32) | 0x8001;
    q[21] = 0x5510;
    q[22] = 0x206;
    q[23] = (s64)0xFE00 << 46;
    q[24] = 0x72007000;
    q[25] = (((s64)0x8E00) << 16) | 0x9000;
    Dma_EndDirect((void *)(q + 26), 0x72007000, temp_a2, 0x19);
}
