#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
void Dma_AddData(void *src, s32 size);
void Dma_AddRef(s32 a, s32 b);
extern u8 D_00377020[] __attribute__((section(".data")));

/* 0x00286E88: sibling of TexFile_UploadOne (0x00286768): the 48-byte tag from D_00377020, then a DMA data
 * entry per flag: arg2 with the record's +0x20 and +0x18 words and +0x38/+8, arg3 with +0x24 and +0x1C and
 * +0x3C/+0xC. Record = *(arg0+0x10) + arg1*64. */
void func_00286E88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 tmp[0x30];
    s32 s0;
    s32 rec;
    s32 w;

    memcpy(tmp, D_00377020, 0x30);
    s0 = arg1 << 6;

    rec = LD32(arg0, 0x10) + s0;
    if (LD32(rec, 0x8) != 0) {
        w = (LD32(rec, 0x20) + arg2) | ((LD32(rec, 0x18) & 0xFFFF) << 16);
        LD32(tmp, 0x20) = 0;
        LD32(tmp, 0x24) = w;
        Dma_AddData(tmp, 0x30);
        rec = LD32(arg0, 0x10) + s0;
        Dma_AddRef(LD32(rec, 0x38), LD32(rec, 0x8));
    }

    rec = LD32(arg0, 0x10) + s0;
    if (LD32(rec, 0xC) != 0) {
        LD32(tmp, 0x20) = 0;
        w = (LD32(rec, 0x24) + arg3) | ((LD32(rec, 0x1C) & 0xFFFF) << 16);
        LD32(tmp, 0x24) = w;
        Dma_AddData(tmp, 0x30);
        rec = LD32(arg0, 0x10) + s0;
        Dma_AddRef(LD32(rec, 0x3C), LD32(rec, 0xC));
    }
}
