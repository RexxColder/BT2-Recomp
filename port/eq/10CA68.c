#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1);
extern s32 D_003B0A84 __attribute__((section(".data")));

void func_0010CA68(s64 arg0) {
    s32 buf[64];
    s64 temp_a0;
    s32 i;

    temp_a0 = (arg0 * 0x10) | 0x33009;
    buf[0x80 / 4] = 0x10000007;
    buf[0x90 / 4] = 0x8006;
    buf[0x8C / 4] = 0x50000007;
    buf[0x94 / 4] = 0x10000000;
    buf[0x98 / 4] = 0xE;
    buf[0xA0 / 4] = (D_003B0A84 & 1) ? 0x80000 : 0x80070;
    buf[0xA4 / 4] = 0xFFFFFF;
    buf[0xA8 / 4] = 0x4C;
    buf[0xB0 / 4] = (s32)temp_a0;
    buf[0xB4 / 4] = (s32)(temp_a0 >> 32);
    buf[0xB8 / 4] = 0x47;
    buf[0xC8 / 4] = 0x43;
    buf[0xD0 / 4] = 0x3C000;
    buf[0xD8 / 4] = 0x48;
    buf[0xE8 / 4] = 0x4A;
    buf[0xF0 / 4] = 1;
    buf[0xF8 / 4] = 0x4B;
    buf[0x84 / 4] = 0;
    buf[0x88 / 4] = 0x10000000;
    buf[0x9C / 4] = 0;
    buf[0xAC / 4] = 0;
    buf[0xBC / 4] = 0;
    buf[0xC0 / 4] = 0x48;
    buf[0xC4 / 4] = 0;
    buf[0xCC / 4] = 0;
    buf[0xD4 / 4] = 0;
    buf[0xDC / 4] = 0;
    buf[0xE0 / 4] = 1;
    buf[0xE4 / 4] = 0;
    buf[0xEC / 4] = 0;
    buf[0xF4 / 4] = 0;
    buf[0xFC / 4] = 0;

    /* 0x80 bytes of 64-bit copies: sp+0x80..0xFF to sp+0..0x7F */
    for (i = 0; i < 32; i++) {
        buf[i] = buf[i + 32];
    }
    Dma_AddData((s32)buf, 0x80);
}
