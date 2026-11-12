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

/* Allocates the two 1 MB display-list buffers and points the write cursor at the first. */
void Dma_InitBuffers(void);

/* Copies `size` bytes (whole quadwords) of ready-made packet data to the display list. */
void Dma_AddData(void *src, s32 size);

/* Appends a REF tag: sends `size` bytes that live at `addr` without copying them. */
void Dma_AddRef(void *addr, s32 size);

/* Appends a NEXT tag that jumps to the chain at `addr`, and makes `retTag` point back to what follows. */
void Dma_AddNext(void *addr, u32 *retTag);

/* Closes the display list with a GS FINISH and an END tag, sends it on VIF1 and switches to the other buffer. */
void Dma_Flush(void);

/* Reserves `size` bytes (whole quadwords) in the display list and returns where they start. */
void *Dma_Alloc(s32 size);

/* Starts a GS packet: clears the quadword that will hold its DMA tag and returns the first data quadword. */
u64 *Dma_BeginDirect(void);

/* Ends a packet started by Dma_BeginDirect: writes its CNT tag + VIF DIRECT code and moves the cursor to `end`. */
void Dma_EndDirect(u64 *end);

/* Makes both buffers an empty list (a lone END tag) and rewinds the cursor to the current one. */
void Dma_ResetBuffers(void);

/* Returns the usable size of one display-list buffer. */
s32 Dma_GetBufSize(void);

/* Returns how many bytes of the current buffer are filled. */
s32 Dma_GetUsedSize(void);

/* Returns how many bytes are left in the current buffer. */
s32 Dma_GetFreeSize(void);

/* Shrinks both buffers to 0x51000 bytes and hands their upper 0xAF000 bytes to the caller. */
void Dma_LendBufferTails(u32 *tail0, u32 *tail1, s32 *size);

/* Gives the buffers their full 1 MB back. */
void Dma_ReclaimBufferTails(void);

/* Enables the DMA controller, sets the channel condition/interrupt mask and clears the status. */
void Dma_InitController(void);

/* Spins until the DMA condition flag (CPCOND0: the channels selected in D_PCR have finished) is set. */
void Dma_WaitCond(void);

/* Spins while the COP2 condition flag is set (VU1 still running a micro program). */
void Dma_WaitVu1(void);

/* Starts a source-chain transfer of `chain` on DMA channel 1 (VIF1) once VIF1, VU1 and the GIF path are idle. */
void Dma_SendVif1(u32 chain);

/* Like Dma_SendVif1, but always waits for the previous transfer first and for this one to finish. */
void Dma_SendVif1Sync(u32 chain);

/* Starts a VIF1 chain transfer of a list that lives in the scratchpad (address bit 31 set). */
void Dma_SendVif1Spr(u32 chain);

/* Dma_SendVif1Spr, then waits for the transfer to finish. */
void Dma_SendVif1SprSync(u32 chain);

/* Starts a source-chain transfer of `chain` on DMA channel 2 (GIF) once the channel and the GIF path are idle. */
void Dma_SendGifChain(u32 chain);

/* Dma_SendGifChain, then waits for the transfer to finish. */
void Dma_SendGifChainSync(u32 chain);

/* Starts a plain (normal mode) transfer of `qwc` quadwords at `addr` on the GIF channel. */
void Dma_SendGifNoWait(u32 addr, u32 qwc);

/* Sends `qwc` quadwords at `addr` on the GIF channel and waits for the transfer to finish. */
void Dma_SendGif(u32 addr, u32 qwc);

/* Waits until the GIF channel and the GIF path are idle. */
void Dma_WaitGif(void);

/* Copies `size` bytes at `data` to IOP memory at `iopAddr` over SIF DMA and waits for completion. */
void Dma_SendToIop(void *iopAddr, void *data, s32 size);

/* Queues a GS TEXFLUSH (wait for texture writes before the next primitive). */
void Dma_AddTexFlush(void);

/* Queues GS FRAME_1 and FRAME_2: frame buffer page, width (in 64-pixel units) and write mask; pixel format 0 (32-bit). */
void Dma_AddFrame(s32 fbp, s32 fbw, s32 fbmsk);

/* Queues GS CLAMP_1 and CLAMP_2: texture wrap modes and the clamp/repeat region. */
void Dma_AddClamp(s32 wms, s32 wmt, s32 minu, s32 maxu, s32 minv, s32 maxv);

/* Queues GS SCISSOR_1 and SCISSOR_2: the drawing window in pixels. */
void Dma_AddScissor(s32 x0, s32 x1, s32 y0, s32 y1);

/* Queues GS XYOFFSET_1 and XYOFFSET_2: the primitive coordinate offset, given in pixels. */
void Dma_AddXyOffset(s32 x, s32 y);

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

/* Unused stub that returns 0. */
s32 Dma_Stub101870(void);

/* Queues a flat-colour rectangle drawn as 32-pixel-wide sprites (depth test off, plain alpha blend). */
void Dma_AddFillRect(s32 x, s32 y, s32 w, s32 h, u32 rgba);

/* Writes a textured rectangle into the caller's packet as 32-texel-wide sprites, so that each one stays inside the
 * GS texture cache page. `blend` selects alpha blending. */
void Dma_PutTexStrips(GsQword **pp, s32 x0, s32 y0, s32 x1, s32 y1, s32 xFrac, s32 yFrac, s32 u0, s32 v0, s32 u1, s32 v1,
                      s32 uFrac, s32 vFrac, u32 rgba, s32 blend);
