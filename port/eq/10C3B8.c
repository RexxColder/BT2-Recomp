#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);

void func_0010C3B8(s32 arg0, s32 arg1) {
    s32 out[20];
    s32 c;
    s32 b;
    s64 v1_64;
    s64 a2_64;
    s64 a3_64;

    v1_64 = ((s64)(((arg0 < 0) ? (arg0 + 0x3F) : arg0) >> 6) << 16) | 0xE0;
    c = ((0x1000 - arg0) >> 1) * 16;
    b = ((0x1000 - arg1) >> 1) * 16;
    a2_64 = (s64)c | ((s64)b << 32);
    a3_64 = ((s64)(arg0 - 1) << 16) | ((s64)(arg1 - 1) << 48);

    out[0] = 0x10000004;
    out[1] = 0;
    out[2] = 0x10000000;
    out[3] = 0x50000004;
    out[4] = 0x8003;
    out[5] = 0x10000000;
    out[6] = 0xE;
    out[7] = 0;
    out[8] = (s32)v1_64;
    out[9] = (s32)(v1_64 >> 32);
    out[10] = 0x4C;
    out[11] = 0;
    out[12] = c;
    out[13] = (s32)(a2_64 >> 32);
    out[14] = 0x18;
    out[15] = 0;
    out[16] = (s32)a3_64;
    out[17] = (s32)(a3_64 >> 32);
    out[18] = 0x40;
    out[19] = 0;
    Dma_AddData((s32)out, 0x50);
}
