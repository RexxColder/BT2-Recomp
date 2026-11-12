#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(s32)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
void Dma_AddData(void *src, s32 size);
void Dma_AddRef(s32 a, s32 b);
extern u8 D_00376F30[] __attribute__((section(".data")));

/* 0x00286768: queue the DMA of one texture entry of a file (arg1 indexes 64-byte records at *(arg0+0x10)):
 * a 48-byte tag built on the stack, then a reference to the data. arg2 >= 0 uses the record's +0x18 word
 * and +0x38/+8 pointers, arg3 >= 0 uses +0x1C word and +0x3C/+0xC. */
void TexFile_UploadOne(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 tmp[0x30];
    s32 s3;
    s32 w;

    memcpy(tmp, D_00376F30, 0x30);
    s3 = arg1 << 6;

    if (arg2 >= 0) {
        w = arg2 | ((LD32(LD32(arg0, 0x10) + s3, 0x18) & 0xFFFF) << 16);
        *(s32 *)(tmp + 0x20) = 0;
        *(s32 *)(tmp + 0x24) = w;
        Dma_AddData(tmp, 0x30);
        Dma_AddRef(LD32(LD32(arg0, 0x10) + s3, 0x38), LD32(LD32(arg0, 0x10) + s3, 0x8));
    }

    if (arg3 >= 0) {
        *(s32 *)(tmp + 0x20) = 0;
        w = arg3 | ((LD32(LD32(arg0, 0x10) + s3, 0x1C) & 0xFFFF) << 16);
        *(s32 *)(tmp + 0x24) = w;
        Dma_AddData(tmp, 0x30);
        Dma_AddRef(LD32(LD32(arg0, 0x10) + s3, 0x3C), LD32(LD32(arg0, 0x10) + s3, 0xC));
    }
}
