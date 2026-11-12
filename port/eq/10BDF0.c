#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
void Dma_AddData(void *src, s32 size);
extern s32 D_003B0A84 __attribute__((section(".data")));

/* 0x0010BDF0: builds a 0x70-byte GIF/GS packet (tag, then register/data pairs) in a staging area at +0x70,
 * copies it to the start of the frame and queues it with Dma_AddData. The one flag from D_003B0A84 picks the
 * value at +0x90 (0x80000 when the flag bit is set, else 0x80070). */
void func_0010BDF0(void) {
    u8 fr[0xF0];
    s32 flag;
    s32 a1v;

    flag = D_003B0A84 & 1;
    a1v = (flag != 0) ? 0x80000 : 0x80070;

#define SW(off, v) (*(u32 *)(fr + (off)) = (u32)(v))
    SW(0x70, 0x10000006);
    SW(0x74, 0);
    SW(0x78, 0x10000000);
    SW(0x7C, 0x50000006);
    SW(0x80, 0x8005);
    SW(0x84, 0x10000000);
    SW(0x88, 0xE);
    SW(0x8C, 0);
    SW(0x90, a1v);
    SW(0x94, 0);
    SW(0x98, 0x4D);
    SW(0x9C, 0);
    SW(0xA0, 0x44);
    SW(0xA4, 0);
    SW(0xA8, 0x43);
    SW(0xAC, 0);
    SW(0xB0, 0);
    SW(0xB4, 0);
    SW(0xB8, 0x4A);
    SW(0xBC, 0);
    SW(0xC0, 0);
    SW(0xC4, 0);
    SW(0xC8, 0x4B);
    SW(0xCC, 0);
    SW(0xD0, 0x30000);
    SW(0xD4, 0);
    SW(0xD8, 0x48);
    SW(0xDC, 0);
#undef SW

    memcpy(fr, fr + 0x70, 0x70);
    Dma_AddData(fr, 0x70);
}
