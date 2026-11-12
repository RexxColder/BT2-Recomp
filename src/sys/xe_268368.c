#include "common.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/gfxm_e.h"

/*
 * GS environment packets of the battle object renderer, 0x112A30..0x1131D8. See include/sys/gfxm_e.h.
 * Each function builds a packet on the stack (DMA tag, VIF DIRECT, GIF tag, A+D registers) and queues a copy
 * with Dma_AddData. Callers: the object draw at 0x111358 and the pass function at 0x10FD98 (previous file) and
 * the shadow code of gfxm_e_b.c.
 */

#define GS_TEX0_1_REG 0x06
#define GS_TEXA 0x3B
#define GS_PRMODECONT 0x1A
#define GS_PRMODE 0x1B

/* FRAME_1 value of the frame's colour buffer with a write mask. */
#define OBJGS_FRAME(mask) GS_SET_FRAME((gGfx.frame & 1) ? 0 : 0x70, 8, 0, mask)


/* Queues the state of the flat shadow pass: depth writes off, alpha test, FBA on, blend by a fixed 0x46,
   PRMODECONT = 0 with PRMODE = gouraud + blend. */
void ObjGs_AddFlatShadowEnv(void) {
    u32 pkt[32] = {
        DMA_TAG_CNT | 7, 0, VIF_FLUSHE, VIF_DIRECT | 7,
        GIF_EOP | 6, 0x10000000, GIF_REG_AD, 0,
        0x310000E0, 1, GS_ZBUF_1, 0,
        0x54000, 0, GS_TEST_1, 0,
        1, 0, GS_FBA_1, 0,
        0x64, 0x46, GS_ALPHA_1, 0,
        0, 0, GS_PRMODECONT, 0,
        0x48, 0, GS_PRMODE, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}
