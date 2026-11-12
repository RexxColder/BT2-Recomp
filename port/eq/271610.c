#include "common.h"

void Dma_AddData(s32 arg0, u32 arg1);
extern u8 gGfx[] __attribute__((section(".data")));

void func_00271610(s32 arg0, s32 arg1) {
    s32 sp[16];
    s32 temp_t0;
    s64 temp_a3;
    s64 temp_t6;

    temp_t6 = arg1 * 0x10;
    temp_t0 = arg0 * 0x10;
    temp_a3 = (s64)(temp_t0 | (temp_t6 << 0x20)) >> 0x20;
    *(s32 *)(gGfx + 0x240) = (s32)temp_t6;
    *(s32 *)(gGfx + 0x23C) = temp_t0;
    sp[0] = 0x10000003;
    sp[1] = 0;
    sp[2] = 0x10000000;
    sp[3] = 0x50000003;
    sp[4] = 0x8002;
    sp[5] = 0x10000000;
    sp[6] = 0xE;
    sp[7] = 0;
    sp[8] = temp_t0;
    sp[9] = (s32)temp_a3;
    sp[10] = 0x18;
    sp[11] = 0;
    sp[12] = temp_t0;
    sp[13] = (s32)temp_a3;
    sp[14] = 0x19;
    sp[15] = 0;
    Dma_AddData((s32)sp, 0x40);
}
