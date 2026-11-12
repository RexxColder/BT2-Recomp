#include "common.h"

s32 Dma_BeginDirect(void);
void Dma_EndDirect(s32 arg0, s32 arg1, s32 arg2);

void func_00137728(s32 arg0) {
    u8 *p;
    s64 s0;

    s0 = arg0 & 0xFF;
    p = (u8 *)Dma_BeginDirect();
    *(s64 *)(p + 0x00) = ((s64)0x10000000 << 32) | 0x800B;
    *(s64 *)(p + 0x08) = 0xE;

    s0 = (s0 == 0);
    s0 = s0 | (s0 * 4);
    /* the values of the asm, one 16-byte chunk per (lo, hi) pair */
    *(s64 *)(p + 0x10) = 0x44;
    *(s64 *)(p + 0x18) = 0x42;
    *(s64 *)(p + 0x20) = 0x60;
    *(s64 *)(p + 0x28) = 0x14;
    *(s64 *)(p + 0x30) = 0x50000;
    *(s64 *)(p + 0x38) = 0x47;
    *(s64 *)(p + 0x40) = s0;
    *(s64 *)(p + 0x48) = 8;
    *(s64 *)(p + 0x50) = 0x310000E0;
    *(s64 *)(p + 0x58) = 0x4E;
    *(s64 *)(p + 0x60) = 0;
    *(s64 *)(p + 0x68) = 0x46;
    *(s64 *)(p + 0x70) = 0x44;
    *(s64 *)(p + 0x78) = 0x43;
    *(s64 *)(p + 0x80) = 0x60;
    *(s64 *)(p + 0x88) = 0x15;
    *(s64 *)(p + 0x90) = 0x50000;
    *(s64 *)(p + 0x98) = 0x48;
    *(s64 *)(p + 0xA0) = s0;
    *(s64 *)(p + 0xA8) = 9;
    *(s64 *)(p + 0xB0) = 0x310000E0;
    *(s64 *)(p + 0xB8) = 0x4F;
    Dma_EndDirect((s32)(p + 0xC0), 0x50000, 0x60);
}
