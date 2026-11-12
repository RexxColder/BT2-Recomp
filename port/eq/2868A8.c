#include "common.h"

void *memcpy(void *, const void *, unsigned int);
void Dma_AddData(void *arg0, s32 arg1);
void Dma_AddRef(s32 arg0, s32 arg1);
extern u8 D_00376F60 __attribute__((section(".data")));

/* 0x002868A8 (Tex_Upload): copies the 0x30-byte template D_00376F60 to a local block. For arg1 >= 0: word +0x20 = 0,
 * word +0x24 = arg1 | ((word at arg0+0x18 & 0xFFFF) << 16), Dma_AddData(block, 0x30) and
 * Dma_AddRef(word +0x38, word +8). For arg2 >= 0 the same with arg2, the word at +0x1C, then Dma_AddRef(+0x3C, +0xC). */
void Tex_Upload(u8 *arg0, s32 arg1, s32 arg2) {
    u8 blk[0x30];

    memcpy(blk, &D_00376F60, 0x30);
    if (arg1 >= 0) {
        *(s32 *)(blk + 0x20) = 0;
        *(s32 *)(blk + 0x24) = arg1 | (s32)((*(u32 *)(arg0 + 0x18) & 0xFFFF) << 16);
        Dma_AddData(blk, 0x30);
        Dma_AddRef(*(s32 *)(arg0 + 0x38), *(s32 *)(arg0 + 0x8));
    }
    if (arg2 >= 0) {
        *(s32 *)(blk + 0x20) = 0;
        *(s32 *)(blk + 0x24) = arg2 | (s32)((*(u32 *)(arg0 + 0x1C) & 0xFFFF) << 16);
        Dma_AddData(blk, 0x30);
        Dma_AddRef(*(s32 *)(arg0 + 0x3C), *(s32 *)(arg0 + 0xC));
    }
}
