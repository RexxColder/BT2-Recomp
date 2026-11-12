#include "common.h"

s32 Dma_AddRef(s32 arg0, s32 arg1);
void *Dma_Alloc(s32 arg0);
extern u8 D_002C3080[] __attribute__((section(".data")));
extern u8 D_002C3380[] __attribute__((section(".data")));

/* Returns the packet: the asm leaves Dma_Alloc's result in v0 up to jr ra (callers such as 2729D0 use it). */
u8 *Vu1Pkt_LoadProg8(void) {
    u8 *v;

    /* PS2: D_002C3380 - D_002C3080 = 0x300 bytes (the 94-instruction microprogram). On PC the two arrays are not
       adjacent, so the label difference was garbage (REF qwc 30703: the VIF stream desynced -> B20 water stages) */
    Dma_AddRef((s32)D_002C3080, 0x300);
    v = (u8 *)Dma_Alloc(0x140);
    *(s32 *)(v + 0) = 0x10000013;
    *(s32 *)(v + 8) = 0x10000000;
    *(s32 *)(v + 0xC) = 0x6C120000;
    *(s32 *)(v + 0x134) = 0x03000012;
    *(s32 *)(v + 0x138) = 0x020001F7;
    *(s32 *)(v + 0x13C) = 0;
    *(s32 *)(v + 4) = 0;
    *(s32 *)(v + 0x130) = 0;
    return v;
}
