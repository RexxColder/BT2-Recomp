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

/* Allocates the table, its packet memory and the head packets of both layers. */
void Ot_Init(void);

/* Frees everything Ot_Init allocated. */
void Ot_Term(void);

/* Default blend equations of the two layers (see the table at the top). */
void Ot_SetDefaultAlpha(void);

/* Rewinds the packet allocation cursor. */
void Ot_ResetCursor(void);

/* Empties the table for the next frame: reselects the three slot pointers, marks every chain empty, rewinds the cursor. Returns 1. */
/* Cleanup pass 2: the two extra copies are made by cse, not written in the source: each of the three loads
   recomputes `cur * 4 + gOt` as its own temporary and cse turns the later ones into copies of the one before
   (`ot = gOt; i = ot->cur; ... ot->slots[i + 1]; ot->slots[i + 2]` reproduces the copy for the third load: 10 of
   24). What is missing is the first load in the same operand order (`ot->slots[i]` expands to `ot + i * 4`, the
   other two to `i * 4 + ot`, so the first is a second addu instead of the source of the chain). Not found:
   `*(i + ot->slots)`, `(&ot->slots[i])[k]`, byte arithmetic, an inline accessor with the index as a parameter,
   pointer copies (a = b = c), post-increments and a 12-byte struct copy all give other code. */
#if 0
/* Differs: the original computes `gOt + gOt->cur * 4` once but then copies it to a new register for each
   of the next two loads (addu v1,a2,v0 / move a3,v1 / move a2,a3), so it is two instructions longer. */
s32 Ot_Reset(void);
#endif


/* Marks `count` chains empty (tail = head). */
s32 Ot_ResetEntries(OtEntry *entry, s32 count);

/* Changes a layer's ALPHA_1 value and rewrites its head packets. */
void Ot_SetLayerAlpha(s32 layer, u64 *alpha);

/* Appends one packet to a chain. */
void Ot_Add(OtPrim *prim, OtEntry *entry);

/* Appends an already linked run of packets (first..last) to a chain. */
void Ot_AddChain(OtPrim *first, OtPrim *last, OtEntry *entry);

/* Joins every non-empty chain, in table order, into one list (gOtHead..gOtTail). */
void Ot_Link(OtEntry *entry, s32 count);

/* Draws what was queued this frame (unless the battle hides it) and empties the table. */
s32 Ot_Draw(void);

/* Copies the GIF data of every linked packet into the display list, between the sorted-pass state and its restore. */
s32 Ot_Send(void);

/* Queues the GS state of the sorted pass on both contexts: current buffer, view scissor, depth test without depth writes. */
void Ot_AddEnv(s32 test);

/* Queues the state that follows the sorted pass: normal blending, depth writes off, depth test "greater", point sampling. */
void Ot_AddRestoreEnv(void);

/* Always 0. */
s32 Ot_Stub102C60(void);

/* Always 0. */
s32 Ot_Stub102C68(void);

/* Returns the usable size of the packet memory (0 before Ot_Init). */
s32 Ot_GetCapacity(void);

/* Records the packet memory and places the table right after its first `size` bytes. */
void Ot_SetBuffer(void *buf, s32 size);

/* Allocates and fills the head packets of both layers. */
void Ot_InitLayers(void);

/* Frees the head packets of both layers. */
void Ot_FreeLayers(void);

/* Writes one head packet at the cursor: a chain link plus the layer's ALPHA_1 / ALPHA_2 values. */
OtPrim *Ot_NewHead(s32 layer);

/* (Re)writes the head packet of every slot of one layer and points the table at them. */
void Ot_BuildHeads(s32 layer);

/* Rounds a size up to a multiple of 64. */
s32 func_002793C8(s32 size) {
    if (size & 0x3F) {
        size = size / 64 * 64 + 64;
    }
    return size;
}
