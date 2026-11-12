#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
void Dma_AddData(void *src, s32 size);
void Dma_AddRef(s32 a, s32 b);
extern u8 D_003768D8[] __attribute__((section(".data")));

/* 0x0026E310: queues two DMA entries built from the 64-byte records at arg0. The record is arg1 (or 0 when its
 * word +8 is zero) for the first entry (+0x18 halfword with arg2's low word) and arg1 for the second (+0x1C with
 * the low word of arg2 + +0x10 + 0x40); each entry's references are then queued. Returns the entry's +0x30
 * doubleword ORed with the shifted second word, arg2 and 0x40000000. */
s64 func_0026E310(s32 arg0, s32 arg1, s64 arg2) {
    u8 sp[0x30];
    s32 r;
    s32 e;
    s32 idx;
    s32 s1v;
    s32 word;

    r = arg0 + (arg1 << 6);
    memcpy(sp, D_003768D8, 0x30);

    idx = (LD32(r, 0x8) == 0) ? 0 : arg1;
    e = arg0 + (idx << 6);

    LD32(sp, 0x20) = 0;
    word = (s32)(((u32)arg2 & 0xFFFFFFFFu) | (((u32)LD32(e, 0x18) & 0xFFFFu) << 16));
    LD32(sp, 0x24) = word;
    Dma_AddData(sp, 0x30);
    Dma_AddRef(LD32(e, 0x38), LD32(e, 0x8));

    s1v = (s32)((u32)arg2 + (u32)LD32(e, 0x10) + 0x40u);
    LD32(sp, 0x20) = 0;
    word = (s32)(((u32)s1v) | (((u32)LD32(r, 0x1C) & 0xFFFFu) << 16));
    LD32(sp, 0x24) = word;
    Dma_AddData(sp, 0x30);
    Dma_AddRef(LD32(r, 0x3C), LD32(r, 0xC));

    return (s64)(*(s64 *)(e + 0x30)) | ((s64)s1v << 37) | arg2 | ((s64)0x8000 << 19);
}
