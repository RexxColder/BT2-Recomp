#define Heap_Free func_002F44A0  /* fix_targets */ /* the original uses 0x2f44a0 here */
#define gStgPanBlur D_00387F1C  /* fix_targets */ /* the original uses 0x387f1c here */
#include "common.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/math3d.h"
#include "sys/gfxm_a.h"

/*
 * Full-screen post effects, 0x102F28..0x106D60. See include/sys/gfxm_a.h for the overview.
 * Everything here is drawing: nothing reads a pad, the clock or a random generator.
 *
 * One function is INCLUDE_ASM with a behaviourally exact attempt in `#if 0` above it: StgDepthTint_Draw.
 * StgPanBlur_UpdateView matches since cleanup 4 (with two stand-in constructs, see its note) and emits the
 * file's .lit4 (0x2FC280..0x2FC290).
 */

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Length(Vec4 *v);
extern void Vu0Screen_StoreMtx(Mtx44 *dst);              /* the current world-to-screen matrix */
extern void Mtx_ProjectInt(s32 *dst, Mtx44 *m, Vec4 *v); /* v through m, perspective divide, to integers */

extern void GfxClut_InitPacket(GfxPostClut *blk, u16 cbp); /* creates a CLUT texture block */
extern s32 Tex_Log2Size(s32 size);                   /* log2 of a texture size */
extern void GfxPost_DrawDepthClut(s32 mode, s32 tbp, s32 cbp, u64 alpha); /* 0x106D60, next file */

/* Stage parameter file readers (stg_a). */
extern void BtlStage_GetLightVecA(Vec4 *out);
extern s32 BtlStage_GetWaterLevel(f32 *level);
extern StgDepthTintParam *BtlStage_GetList40(s32 index);
extern StgGlareParam *BtlStage_GetList48(void);

/* GS registers the shared headers do not define. */
#define GS_TEX0_2 0x07
#define GS_TEX1_2 0x15
#define GS_SET_TEXA(ta0, aem, ta1) ((u64)(ta0) | ((u64)(aem) << 15) | ((u64)(ta1) << 32))
/* The engine's ready-made textured sprite packet (DMA tag, GIF tag, 8 registers in REGLIST form). */
typedef struct GfxPostSpritePkt {
    /* 0x00 */ union {
        u32 w; /* 0x20000005 */
        struct {
            u16 qwc;
            u16 id;
        } h;
    } tag;
    /* 0x04 */ void *next;
    /* 0x08 */ u32 vif0;   /* 0x10000000 */
    /* 0x0C */ u32 vif1;   /* 0x50000005 */
    /* 0x10 */ u64 gifTag; /* 0x8400000000008001: REGLIST, 8 registers */
    /* 0x18 */ u64 regs;   /* PRIM, TEX0_1, RGBAQ, UV, XYZF2, UV, XYZF2, NOP */
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ struct {
        u8 r, g, b, a;
        f32 q;
    } rgbaq;
    /* 0x38 */ struct {
        u16 u, v;
        u32 pad;
    } uv0;
    /* 0x40 */ struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } xyz0;
    /* 0x48 */ struct {
        u16 u, v;
        u32 pad;
    } uv1;
    /* 0x50 */ struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } xyz1;
    /* 0x58 */ u64 nop;
} GfxPostSpritePkt; /* size 0x60 */

#define GFX_RGBAQ_NEUTRAL 0x3F80000080808080 /* grey 0x80, alpha 0x80, Q = 1.0f */

/* Creates the pan blur: the CLUT block and the two views (halves of the screen in split screen). */
void StgPanBlur_Init(s32 cbp);

/* Updates the views (unless the battle is paused) and draws those with a strength. */
void StgPanBlur_Draw(void);

/* Frees the pan blur. */
void func_00101560(void) {
    Heap_Free(gStgPanBlur);
}

/* CLUT of the pan blur: grey, alpha 0x80 - depth byte / 2. */
void StgPanBlur_BuildClut(u8 *clut);

/* Follows the camera of one view: strength from its horizontal speed, the two layers from that. Returns 0 when
   the strength has run out. */
/* History (it matches now, see the last note). Third cleanup: 13 of 197 instructions (was 60 of 191): the
   layer loop now matches. What remains is in the
   straight-line part in front of it: two callee-saved registers are exchanged (the original keeps
   `view->prev.m[3]` in s3 and `&move` in s4, this has them the other way round), and with that the
   `addiu s1,sp,48` / `li a2,16` pair of the fourth clear is in the other order. Same behaviour.
   What made the loop match (third cleanup): the two layers are written as ONE FLAT float array,
   `layer[i * 12 + k]`, an array member (not a pointer) indexed with the constant inside the subscript.
   The compiler then adds the whole constant (0xB0 + 4 * k) to the index before adding `view`, cse cannot
   relate the eight addresses, combine re-associates each one into `(i * 48 + view) + K`, and only the
   post-reload cse sees that the eight sums are the same value and turns seven of them into register copies:
   that is the copy chain t3 -> v1 -> a1 -> a2 -> a3 -> t1 -> t0 -> v0 of the original. (The same thing
   explains Ot_Reset in gfx_ot.c: its later loads are `slots[cur + 1]`, `slots[cur + 2]` with the constant in
   the subscript.) The four vectors are `{0, 0, 0, 1}` initialisers (same code as memset + store).
   Tried for the s3 / s4 exchange without effect (about 25 variants): pointer variables for the two matrix
   rows declared or assigned in several places, the rows written as `&m[3][0]`, the two `dist` stores in
   either order or chained, `cam` and `dist` initialised in their declarations, a local for gBtlCam or for
   the index, pointers to the two matrices. Local register allocation decides it: the two row addresses
   (three references each, born where the scheduler puts them, in front of Mtx_Copy) and the three
   `sp + N` addresses compete for s1..s5, and the original ranks `view + 0x70` between `&dirCur` and
   `&move` while this ranks both row addresses last. */
/* MATCHED in cleanup 4, with two constructs whose original form is not known (treat as stand-ins):
   - `side.y` is read through a pointer variable declared right behind `side` (`Vec4 *sp = &side;`). The pointer
     itself disappears (it is sp + 0), but its one RTL instruction in the first block changes where the
     scheduler puts the two row addresses, and s3 / s4 come out as in the original (13 -> 2 differing). It
     must be declared directly behind `side` or `move`; a pointer to another vector, a later assignment, an
     inline reader, or `dist` / `cam` initialised among the vectors do not do it.
   - `do { dist = Vec3_Length(&move); } while (0);` (found by the permuter): without it one pair of argument
     loads of the second memset is swapped (`move a0,s4 / move a1,zero`). A plain block does not do it; the
     loop notes are what matters (they bound the first scheduling region). Reads like a statement macro.
   The function emits the file's whole .lit4: 0.1f, 0.15f, 0.1f, 0.15f (0x2FC280..0x2FC28C, bits compared). */
typedef struct StgPanBlurViewF {
    u8 pad[0xB0];
    f32 layer[24];
} StgPanBlurViewF;
#define L(i, k) ((StgPanBlurViewF *)view)->layer[(i) * 12 + (k)]
s32 StgPanBlur_UpdateView(StgPanBlurView *view);


/* Copies the frame, halved, to the 256x256 work page. */
void StgPanBlur_CopyScreen(void);

/* Draws one view of the pan blur. The work page (256x256 copy of the frame, or the view's half of it in split
   screen) goes to the 128x128 page 0x170 with alpha = strength; the two layers are blended over it, shifted
   sideways; the result is stretched back over the view's rectangle of the frame, blended by its alpha. */
/* Matching notes: the strip x of the layer loop is `i * step + x - r` / `(i + 1) * step + r + x` (the operand
   order decides the order in which the loop pass emits the four start values, and with it the registers);
   in the last loop the view's x is a plain running variable (`x += 32`, read BEFORE `step` is computed, so
   that `view` is dead when `u` is created and u takes its register), the packet is filled in its natural
   member order (prim first; the scheduler emits the stores whose source register dies first), and the
   per-strip members are written texels first, then the two XYZ words. */
void StgPanBlur_DrawView(StgPanBlurView *view, s32 split);


/* Back to the frame's colour buffer with the default offset, scissor and depth writes. */
void StgPanBlur_RestoreEnv(void);

/*
 * The glow pass. The frame's destination alpha is the mask (set up by the caller through a depth CLUT).
 *   1. clear the 256x256 work page (0x150) and draw the frame into it, halved, blended by the frame's alpha and
 *      tinted with `color`;
 *   2. halve it again to 128x128 (page 0x170), and again to 64x64 (page 0x1F6, two sprites one texel apart);
 *   3. `passes` (rounded up to even) blur passes between the 64x64 pages 0x1F6 and 0x1F8, bilinear, every other
 *      one shifted by a texel, each averaged 50/50 with what is there;
 *   4. back up to 128x128 tinted with `glow`, to 256x256, and added to the frame (ALPHA 0x68);
 *   5. restore the frame environment.
 */
/* The two up-scaling loops (4 and 8 strips) are written the way the induction variables require: the two texel
   coordinates go through `s64` temporaries (so that the `|` with the V half is not narrowed to 32 bits and they
   step as 64-bit values), and the first corner's X comes from `i`, not from `x` (so the loop cannot be reversed
   before the second loop pass, which puts the counter's initial value behind that corner's). */
void GfxPost_DrawGlow(s32 passes, u32 color, u32 glow);

/* Draws a 16-bit texture over the screen, one line up, with the given blend. */
void GfxPost_DrawTex16(s32 tbp, u64 alpha);

/* Queues FRAME_1: a 16-bit page, 512 wide, with a write mask. */
void GfxPost_AddFrame16(s32 fbp, s32 fbmsk);

typedef struct GfxPostPkt40 {
    u32 w[16];
} GfxPostPkt40;

/* Queues FRAME_1 = the frame's colour buffer and the default XYOFFSET_1. */
void GfxPost_AddScreenFrame(void);

/* CLUT of the outline pass: id byte -> red and green (id * 8, or 0x80), id 0xFF -> nothing. */
void ObjOutline_BuildClut(u8 *clut);

/* Draws the depth page through a CLUT over the screen, shifted by (dx, dy) sixteenths of a pixel. */
void GfxPost_DrawDepthClutAt(s32 half, s32 tbp, s32 cbp, u64 alpha, s32 dx, s32 dy);

/* Draws a 16-bit texture over the screen, one line up, bilinear, skipping texels of alpha 0 (TEST 0x3000F);
   `ta0` is the alpha given to texels whose alpha bit is clear (TEXA). */
void GfxPost_DrawTex16Texa(s32 tbp, u64 alpha, u8 ta0);

/* Blends an untextured rectangle over the screen. */
void GfxPost_FillBlend(u64 alpha, u64 rgbaq);

/* Points FRAME_1 at a 16-bit page, clears it to black and then sets its write mask. */
void GfxPost_ClearWork(s32 fbp, s32 fbmsk);

/* Queues XYOFFSET_1. */
void GfxPost_AddXyOffset(s32 x, s32 y);

/* Creates the outline pass. */
void ObjOutline_Init(void);

/* Frees the outline pass. */
void ObjOutline_Term(void);


/* The outline pass: edges of the id image into the frame's alpha, then a dark rectangle blended by it. */
void ObjOutline_Draw(void);

/* CLUT of the sky glare: white; alpha = the stage's value, 0x80 for depth byte 0xFF. */
void StgGlare_BuildClut(u8 *clut);

/* Nothing. */
void StgGlare_Nop(void);

/* Steps the glare level: up while the stage's light is on screen, down otherwise. */
void StgGlare_Update(void);

/* Restarts the level of a glare that is off. */
void StgGlare_Reset(void);

/* Creates the sky glare. */
void StgGlare_Init(u16 cbp);

/* Nothing (the block is static). */
void StgGlare_Term(void);

/* The sky glare: clears the frame's alpha, writes the CLUT alpha by depth, then the glow pass. */
void StgGlare_Draw(void);

/* Takes the glare parameters from the stage file (defaults: off) and rebuilds the CLUT. */
void StgGlare_LoadParams(void);

/* CLUT of a depth tint: curve(depth) scales the colour (additive) or the alpha (blended). */
void StgDepthTint_BuildClut(u8 *clut, StgDepthTint *tint);

/* Rebuilds both CLUTs. */
void StgDepthTint_Rebuild(void);

/* Creates the two depth tints. Both get the same CLUT block, cbp + 4. */
void StgDepthTint_Init(u16 cbp);

/* Nothing (the blocks are static). */
void StgDepthTint_Term(void);

/* Draws the tint of the medium the camera is in. */
/* NOT MATCHING (51 of 59 instructions): the original keeps a zero in a callee-saved register across
   Battle_IsSplitScreen() and copies it to the medium index on the split-screen path; here the constant is
   propagated, which shifts the register allocation. Same behaviour. */
/* Cleanup pass 2: with a second variable (`s32 zero = 0;` at the top, `medium` assigned in every arm and
   `else { medium = zero; }` for the split-screen case) the code is the original's except for one thing: cse
   folds `medium = zero` to `move v1,zero`, so the zero is not kept in s0 across Battle_IsSplitScreen
   (28 of 65 aligned by count, but only the `move s0,zero` / `move v1,s0` pair and the registers that follow from
   it). Needed: a zero that cse cannot see at that point. Tried: a loop that runs once (`for (i = 0; i < 1; i++)`
   with `medium = i`), an inline helper returning the variable, a dead conditional in front (the trick that
   matched IopHeap_PrintFree), none keeps the copy. */
/* Cleanup pass 3: read the copy as `medium = zero` done BEFORE the split-screen test (`move v1,s0` sits in the
   delay slot of that branch, so it is in the first block, behind the call), with `medium` set again in the two
   water arms. A zero whose address goes to an inline reader (`medium = Get(&zero)`, an ADDRESSOF that is purged
   after the first cse) is still folded (cse does not treat such memory as clobbered by the call). The zero has
   to reach register allocation as a register copy, so whatever hides it must survive cse, gcse, cse2 AND
   combine: not found. */
#if 0
void StgDepthTint_Draw(void);
#endif


/* Takes both tints' parameters from the stage file (defaults: off) and rebuilds the CLUTs. */
void StgDepthTint_LoadParams(void);

/* CLUT of the object glow: white, alpha from the table. */
void ObjGlow_BuildClut(void);

/* Creates the object glow. */
void ObjGlow_Init(void);

/* Frees the object glow. */
void ObjGlow_Term(void);

/* Takes this frame's alpha table. */
void ObjGlow_SetAlphaTable(ObjGlowTable *table);

/* The object glow: the table's alpha into the frame by id byte, then the glow pass. */
void ObjGlow_Draw(void);

/* Nothing; first call of StgFx_Init. */
void GfxPost_InitNop(void);

/* Nothing; last call of StgFx_Term. */
void GfxPost_TermNop(void);

/* Nothing. */
void GfxPost_Nop106C70(void);

/* Returns 0. */
s32 GfxPost_Stub106C78(void);

/* Sets a quad's colour. */
void GfxPostQuad_SetColor(GfxPostQuad *q, s32 r, s32 g, s32 b, s32 a);

/* Works out a quad of w x h pixels at (dx, dy) from the base, textured from (u0, v0) to (u1, v1); `half` adds
   half a texel. Everything goes to 12.4 fixed point. */
void GfxPostQuad_Set(GfxPostQuad *q, s32 baseX, s32 baseY, s16 u0, s16 v0, s16 u1, s16 v1, s32 dx, s32 dy, s32 w, s32 h,
                     s16 half);
