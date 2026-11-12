#include "common.h"
#include "sys/gfx.h"
#include "sys/gfx_ot.h"
#include "sys/heap.h"

/*
 * Ordering table for depth-sorted primitives (0x102458..0x102F28). Lives for the length of a battle.
 *
 * Memory (Ot_Init): one block of 0x73000 bytes of packet space followed by the table, 0x1002 slots of
 * 0x10 bytes. A slot holds two chains ("layers"), each {head, tail}. Every chain starts with a fixed
 * 0x40-byte head packet (Ot_NewHead) that sets ALPHA_1 / ALPHA_2 for its layer:
 *   layer 0: ALPHA_1 0x44 = (Cs - Cd) * As + Cd (normal),   ALPHA_2 0x42 = (0 - Cs) * As + Cd (subtractive)
 *   layer 1: ALPHA_1 0x48 = (Cs - 0) * As + Cd (additive),  ALPHA_2 0x49 = (Cd - 0) * As + Cd
 * so a primitive picks its blend mode by the layer it is queued on and by drawing with context 1 or 2.
 * gOtFirst is slot 0, gOtZ the 0x1000 depth slots, gOtLast the final slot.
 *
 * Queueing is done by the effect code directly (it uses gOtCur and the three slot pointers; Ot_Add /
 * Ot_AddChain are the out-of-line versions): a packet is a DMA-style header {qwc, next} + GIF data taken
 * from gOtCur, linked at the tail of a chain.
 *
 * Ot_Draw, called once per battle frame after the opaque passes: links all non-empty chains in table
 * order (slot 0 first, then depth slot 0x000 up to 0xFFF, then the last slot; layer 0 before layer 1
 * within a slot), and unless the battle hides them (0x23FBF8) copies their GIF data into the display list
 * between Ot_AddEnv and Ot_AddRestoreEnv. The head packets of empty chains are skipped, those of used
 * chains are sent, which is how the blend mode gets set. Then every chain is emptied.
 * Because the list is drawn in increasing slot order, low slot numbers are the far ones (painter's order);
 * that the index grows towards the camera is an inference from this, the users were not decompiled here.
 *
 * State of the sorted pass (Ot_AddEnv, both GS contexts): FRAME = current buffer, ZBUF with depth writes
 * masked, XYOFFSET default, SCISSOR = the scissor of gBtlCamView (so split-screen halves clip),
 * ALPHA 0x44, TEST = depth test GEQUAL plus 0xC (alpha test method bits GEQUAL, not enabled) | `test`,
 * TEX1 bilinear, CLAMP repeat, FBA off, COLCLAMP on. Afterwards (Ot_AddRestoreEnv, context 1 only apart
 * from ALPHA): ALPHA 0x44, depth writes still masked, depth test GREATER, TEX1 0 (point sampling,
 * as written), COLCLAMP on, CLAMP clamp/clamp.
 */

/* libc */
extern void *memset(void *dst, s32 c, u32 size);
extern void *memcpy(void *dst, const void *src, u32 size);

/* Other modules (local declarations). */
extern s32 BtlStage_IsReady(void);

/* Battle camera view being drawn; only its scissor rectangle is used here. */
typedef struct OtView {
    /* 0x000 */ u8 unk0[0x200];
    /* 0x200 */ s32 scissorX0;
    /* 0x204 */ s32 scissorX1;
    /* 0x208 */ s32 scissorY0;
    /* 0x20C */ s32 scissorY1;
} OtView;
extern OtView *gBtlCamView;


/* Queues the state that follows the sorted pass: normal blending, depth writes off, depth test "greater", point sampling. */
void Ot_AddRestoreEnv(void) {
    u32 pkt[36] = {
        DMA_TAG_CNT | 8, 0, VIF_FLUSHE, VIF_DIRECT | 8,
        GIF_EOP | 7, 0x10000000, GIF_REG_AD, 0,
        0x44, 0, GS_ALPHA_1, 0,
        0x44, 0, GS_ALPHA_2, 0,
        GS_SET_ZBUF(GFX_ZBP, GS_PSMZ24, 0), 1, GS_ZBUF_1, 0,
        0x70000, 0, GS_TEST_1, 0,
        0, 0, GS_TEX1_1, 0,
        1, 0, GS_COLCLAMP, 0,
        5, 0, GS_CLAMP_1, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}
