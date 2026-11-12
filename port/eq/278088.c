#include "common.h"

void *Dma_BeginDirect(void);
void Dma_EndDirect(u8 *arg0);
void TexFile_UploadOne(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00271370(void);

/* Builds two DMA packets: a header packet, then per texture an upload packet
   (the 8 texture entries, 4 per pass, two passes). */
void func_00278088(u8 *obj, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5) {
    u8 *dma;
    u8 *dma2;
    u8 *ent;
    u64 tag;
    u64 word_a0;
    u64 word_a1;
    s32 base;
    s32 ptr_lo;
    s32 ptr_hi;
    s32 tex_hi;
    s32 pass;
    s32 j;
    s32 idx;

    tag = (u64)p2 | ((u64)p5 << 24) | ((u64)p4 << 16) | ((u64)p3 << 8);

    dma = (u8 *)Dma_BeginDirect();
    *(u64 *)(dma + 0x00) = 0x1000000000008005ULL;
    *(u64 *)(dma + 0x08) = 14;
    *(u64 *)(dma + 0x10) = 68;
    *(u64 *)(dma + 0x18) = 66;
    *(u64 *)(dma + 0x20) = 0;
    *(u64 *)(dma + 0x28) = 74;
    *(u64 *)(dma + 0x30) = 0x30000;
    *(u64 *)(dma + 0x38) = 71;
    *(u64 *)(dma + 0x40) = tag;
    *(u64 *)(dma + 0x48) = 1;
    *(u64 *)(dma + 0x50) = 5;
    *(u64 *)(dma + 0x58) = 8;
    Dma_EndDirect(dma + 0x60);

    ptr_hi = 0x7000;
    tex_hi = 0x8000;
    for (pass = 0; pass < 2; pass++) {
        base = p1 << 4;
        ptr_lo = base + 0x7000;
        {
            s32 cursor = base + 0x7800;
            for (j = 0; j < 4; j++) {
                idx = 4 * pass + j;
                ent = *(u8 **)(obj + 0x10) + (idx << 6);
                TexFile_UploadOne(obj, idx, 0x3000, *(s32 *)(ent + 0x10) + 0x3000);
                func_00271370();

                dma2 = (u8 *)Dma_BeginDirect();
                *(u64 *)(dma2 + 0x08) = 5460742;
                *(u64 *)(dma2 + 0x00) = 0x6400000000008001ULL;

                word_a0 = (u64)ptr_lo | ((u64)ptr_hi << 16);
                ent = *(u8 **)(obj + 0x10) + (idx << 6);
                word_a1 = (u64)cursor | ((u64)tex_hi << 16);
                cursor += 0x800;
                ptr_lo += 0x800;

                *(u64 *)(dma2 + 0x10) = *(u64 *)(ent + 0x30) |
                                        ((u64)(*(s32 *)(ent + 0x10) + 0x3000) << 37) |
                                        0x400003000ULL;
                *(u64 *)(dma2 + 0x18) = 342;
                *(u64 *)(dma2 + 0x20) = 0;
                *(u64 *)(dma2 + 0x28) = word_a0;
                *(u64 *)(dma2 + 0x30) = 0x10000800ULL;
                *(u64 *)(dma2 + 0x38) = word_a1;
                Dma_EndDirect(dma2 + 0x40);
            }
        }
        ptr_hi += 0x1000;
        tex_hi += 0x1000;
    }
}
