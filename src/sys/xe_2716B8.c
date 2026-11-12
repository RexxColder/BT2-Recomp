#include "common.h"
#include "sys/dma.h"
#include "sys/heap.h"

/* libc */
extern void *memcpy(void *dst, const void *src, u32 size);

/* Sony kernel */
extern void FlushCache(s32 mode);
extern u32 sceSifSetDma(SifDmaData *data, s32 count);
extern s32 sceSifDmaStat(u32 id);

extern u32 gDmaBuf[2];    /* addresses of the two buffers */
extern u32 gDmaBufEnd[2]; /* address just past each buffer */
extern s32 gDmaBufSize;
extern s32 gDmaBufIdx;
extern u32 *gDmaCur;
extern s32 gDmaVif1Started;


/* Queues GS ZBUF_1: depth buffer page (24-bit format) and the "do not write depth" flag. */
void Dma_AddZbuf(s32 zbp, s32 zmsk) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, VIF_FLUSHE, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        GS_SET_ZBUF(zbp, GS_PSMZ24, zmsk), GS_SET_ZBUF(zbp, GS_PSMZ24, zmsk) >> 32, GS_ZBUF_1, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Queues GS TEX0_1 with a ready-made register value. */
void Dma_AddTex0(u64 tex0) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, VIF_FLUSHE, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        tex0, tex0 >> 32, GS_TEX0_1, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Queues GS TEX1_1 with a ready-made register value. */
void Dma_AddTex1(u64 tex1) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, VIF_FLUSHE, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        tex1, tex1 >> 32, GS_TEX1_1, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Queues GS FBA_1 (forces the alpha bit of written pixels). */
void Dma_AddFba(s32 fba) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, VIF_FLUSHE, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        (u64)fba, (u64)fba >> 32, GS_FBA_1, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Queues GS COLCLAMP (clamp or wrap colour after blending). */
void Dma_AddColClamp(u64 clamp) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, VIF_FLUSHE, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        clamp, clamp >> 32, GS_COLCLAMP, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Queues GS ALPHA_1 (blend equation) with a ready-made register value. */
void Dma_AddAlpha(u64 alpha) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, 0, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        0, 0, GS_ALPHA_1, 0,
    };

    pkt[8] = alpha;
    pkt[9] = alpha >> 32;
    Dma_AddData(pkt, sizeof(pkt));
}
