#include "common.h"
#include "battle/eft_ae.h"
#include "sys/gfx_ot.h"

/*
 * 0x1AA7E8..0x1AE2A8: the end of the effect code. See include/battle/eft_ae.h for the layouts.
 *
 *   0x1AA7E8            EftSpr_IsOffScreen: the screen test the two sprite writers before it (0x1A9D90, 0x1AA188)
 *                       call; it is the last function of THEIR object.
 *   0x1AA818..0x1AD138  keyframed sprite animations (EftSprAnim_*) and their "V000" pack readers (EftSprPack_*).
 *                       Purely visual. The step draws libc rand() twice per layer per frame.
 *   0x1AD138..0x1ADBA8  the task tree (BtlTask*). Every effect module is a class of tasks in this tree.
 *   0x1ADBA8..0x1AE2A8  effect texture VRAM allocation (EftVram_*) and texture sets (EftTexSet_*); the same
 *                       source file goes on in eft_det_a.c (0x1AE2A8..0x1AE5F8).
 *
 * Callees outside this file are declared here with local views.
 */

/* The effect code's by-value vector: 16-byte aligned, copied by the callee. */
typedef union EftAeVec {
    struct {
        f32 x, y, z, w;
    };
    f32 v[4];
} __attribute__((aligned(16))) EftAeVec;

typedef struct EftAeMtx {
    f32 m[4][4];
} __attribute__((aligned(16))) EftAeMtx;

/* A GS screen position as the projection helpers write it. */
typedef struct EftAeScr {
    s32 x, y, z, w;
} EftAeScr;

/* The view being drawn (include/battle/btl_cam.h). */
typedef struct EftAeView {
    /* 0x000 */ u8 unk0[0x40];
    /* 0x040 */ EftAeMtx view;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ EftAeMtx world2screen;
} EftAeView;

/* Head of a packet in the ordering table: DMA tag, two VIF codes, GIF tag. */
typedef struct EftAePktHead {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 gif0;
    /* 0x18 */ u64 gif1;
} EftAePktHead;

/* A+D packet that sets two registers (CLAMP_1 and CLAMP_2 here). 0x40 bytes. */
typedef struct EftAeRegPkt {
    /* 0x00 */ EftAePktHead h;
    /* 0x20 */ u64 data0;
    /* 0x28 */ u64 reg0;
    /* 0x30 */ u64 data1;
    /* 0x38 */ u64 reg1;
} EftAeRegPkt;

/* GS XYZF2 register value. */
typedef struct EftAeXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftAeXyzf;

typedef struct EftAeGsVtx {
    /* 0x00 */ u8 rgba[4];
    /* 0x04 */ f32 q;
    /* 0x08 */ f32 s;
    /* 0x0C */ f32 t;
    /* 0x10 */ EftAeXyzf xyz;
} EftAeGsVtx; /* 0x18: RGBAQ, ST, XYZF2 */

/* One textured gouraud triangle between two CLAMP writes. 0x90 bytes, 14 registers. */
typedef struct EftAeTriPkt {
    /* 0x00 */ EftAePktHead h;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u64 clamp;     /* 5: clamp s and t */
    /* 0x38 */ EftAeGsVtx v[3];
    /* 0x80 */ u64 clampEnd;  /* 0: back to repeat */
    /* 0x88 */ u64 pad;
} EftAeTriPkt;

/* A vertex handed to the clipper. */
typedef struct EftAeClipVtx {
    /* 0x00 */ Vec4 pos;
    /* 0x10 */ Vec4 uv;
    /* 0x20 */ Vec4 col;
} EftAeClipVtx; /* 0x30 */

extern void ClipVtx_SetArray(EftAeClipVtx *out, Vec4 *pos, Vec4 *uv, Vec4 *color, s32 n); /* n clip vertices */
extern s32 ClipPoly_ClipPlane(EftAeClipVtx *poly, Vec4 *plane, s32 count);   /* clips in place, new count */
extern void ClipPoly_ProjectCur(EftAeScr *scr, Vec4 *stq, EftAeClipVtx *poly, s32 count); /* projects */
extern void EftGfx_UpdateClipPlanes(void);
extern Vec4 *EftGfx_GetClipPlanes(void);

extern f32 gEftSprGridUv2x2[4][4];
extern f32 gEftSprGridUv4x2[8][4];
extern f32 gEftSprGridUv3x3[9][4];
extern f32 gEftSprGridUv4x4[16][4];
extern s32 gEftSprSubdivCorner[4][4];

extern EftAeView *gBtlCamView;
extern EftSprSlot *gEftSprAnimPool;
extern BtlTaskList *gBtlTaskRoot;
extern BtlTask *gBtlTaskCur;
extern EftAeVram *gEftVram;

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern void *Heap_Alloc(s32 size, s32 align, s32 a2, s32 a3);
extern void Heap_Free(void *p);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern void Res_RelocateOffsets(void *out, void *base, void *hdr);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Mtx_StoreIdentity(EftAeMtx *m);
extern void Mtx_MulVec4(Vec4 *dst, EftAeMtx *m, Vec4 *v);
extern void Mtx_Mul(EftAeMtx *dst, EftAeMtx *a, EftAeMtx *b);   /* matrix product */
extern void Mtx_InverseRT(EftAeMtx *dst, EftAeMtx *src);             /* transpose (inverse of a rotation) */
extern void Mtx_RotateXYZ(EftAeMtx *dst, EftAeMtx *src, Vec4 *rot);  /* rotate by three angles */
extern void Mtx_ScaleDiag(EftAeMtx *dst, EftAeMtx *src, Vec4 *scale); /* scale */
extern void Vu0Cur_Push(void);                                     /* VU0 matrix stack push */
extern void Vu0Cur_LoadMtx(EftAeMtx *m);                              /* load the matrix */
extern void Vu0Cur_Pop(void);                                     /* pop */
extern s32 Vu0Cur_ProjectPoint(EftAeScr *out, Vec4 *pos);                  /* project to GS screen coordinates */
extern void Vec4_Mul(Vec4 *dst, Vec4 *a, Vec4 *b);              /* per-component product */
extern void Vec4_Lerp(Vec4 *dst, Vec4 *a, Vec4 *b, f32 t);       /* interpolate a..b */
extern void Vec3_Lerp(Vec4 *dst, Vec4 *a, Vec4 *b, f32 t);       /* interpolate b..a */
extern f32 EftMath_WrapAngle(f32 a);
extern void EftVram_Upload(EftAeTex *tex, s32 imageBlock, s32 clutBlock);

s32 EftSprAnim_IsPlaying(EftSprAnim *anim);
void EftSprAnim_Start(EftSprAnim *anim);
void EftSprAnim_Restart(EftSprAnim *anim);
void EftSprAnim_WrapDegrees(Vec4 *v);
s32 EftSprAnim_BuildMatrices(EftSprAnim *anim, EftAeMtx *oriented, EftAeMtx *billboard);
void EftSprAnim_DrawLayer(EftSprLayerDef *def, s32 frame, s32 time, EftAeTexSet32 *tex, EftAeMtx *m,
                          EftAeMtx *oriented, Vec4 *pos, Vec4 *spin, Vec4 *color, s32 mode, s32 rand1, s32 rand2);
void EftSprAnim_DrawLayerAt(EftAeMtx *m, EftAeMtx *oriented, Vec4 *objPos, EftSprLayerDef *def, s32 frame, s32 time,
                            EftAeTexSet32 *tex, Vec4 *spin, Vec4 *color, s32 mode, s32 rand1, s32 rand2);
void EftSprAnim_Jitter(Vec4 *scale, EftSprLayerDef *def, s32 frame, s32 rand1, s32 rand2);
s32 EftSprAnim_GetGridCells(s32 grid);
void EftSprAnim_SetGridUv(Vec4 *uv, s32 grid, s32 cell);
void EftSprAnim_DrawQuad(u64 tex0, Vec4 *corner, Vec4 *uv, Vec4 *color, s32 otLayer, s32 z, s32 mode);
void EftSprAnim_DrawQuadSubdiv(u64 tex0, Vec4 *corner, Vec4 *uv, Vec4 *color, s32 otLayer, s32 z, s32 mode);
EftSprPack *EftSprPack_Get(EftSprPack *pack);
void EftSprPack_Bind(EftSprPack *pack);
s32 EftSprPack_GetLayerCount(EftSprPack *pack);
EftSprLayerDef *EftSprPack_GetLayers(EftSprPack *pack);
s32 EftSprPack_GetLoopEndFrame(EftSprLayerDef *def);
s32 EftSprPack_GetLoopStartFrame(EftSprLayerDef *def);
s32 EftSprPack_FindKey(EftSprLayerDef *def, s32 frame);
f32 EftSprPack_GetKeyT(EftSprLayerDef *def, s32 frame, s32 key);
s32 EftSprPack_IsValid(EftSprPack *pack);
void BtlTaskList_Update(BtlTaskList *list);
BtlTaskList *BtlTaskList_Create(BtlTask *parent, u32 count, u32 workSize);
void BtlTaskList_Destroy(BtlTaskList *list);
BtlTask *BtlTask_AddAfter(BtlTask *task, BtlTaskCls *cls, void *arg);
BtlTask *BtlTask_AddBefore(BtlTask *task, BtlTaskCls *cls, void *arg);
void BtlTask_Init(BtlTask *task, BtlTaskCls *cls, void *arg);
void BtlTaskList_KillAll(BtlTaskList *list);
void BtlTask_SetDead(BtlTask *task);
void BtlTask_Kill(BtlTask *task);
u64 EftVram_AddTex(EftAeTex *tex, s32 tcc, s32 tfx);
void EftTexSet_CheckCount(s32 count, s32 max) __attribute__((const));

/* 1 when a projected point cannot be drawn: behind the camera or outside the GS coordinate range. */
s32 EftSpr_IsOffScreen(s32 x, s32 y, s32 z);

/* Allocates the pool of 32 animation slots (from BtlScene_Init). */
void EftSprAnim_InitPool(void);

/* Frees the pool. */
void EftSprAnim_TermPool(void);

/* Takes the first unused slot; NULL when all 32 are in use. */
EftSprSlot *EftSprAnim_AllocSlot(void);

/* Gives a slot back. */
void EftSprAnim_FreeSlot(EftSprSlot *slot);

/* Creates an animation object for a pack and a texture set, and starts it. */
void EftSprAnim_Create(EftSprAnim *anim, EftSprPack *pack, EftAeTexSet32 *tex);

/* Releases the object's slot. */
void EftSprAnim_Destroy(EftSprAnim *anim) {
    EftSprAnim_FreeSlot(anim->slot);
}

/* Puts every layer at its first frame. */
void EftSprAnim_Start(EftSprAnim *anim);

/* Advances every layer one step; restarts a looping pack when all layers are done. Returns the number of quads
   the object will draw. Draws libc rand() twice per layer. */
s32 EftSprAnim_Step(EftSprAnim *anim);

/* Draws every layer into the ordering table: builds the object's two frames, loads the view's world-to-screen
   matrix and hands each layer to EftSprAnim_DrawLayer with its frame, its two random values and the object's
   colour times the layer's fade. A layer's own flags pick the frame and the draw mode; the object's draw flags
   override them. Original bug kept: the layer pointer only advances when a layer is drawn, so a skipped layer
   (camera-facing while the frames could not be built, which never happens: BuildMatrices always returns 1) would
   be drawn again in place of the next one. */
/* Matching note: the two layer-definition flags have to be tested through an inline predicate that returns
   `!= 0`. Its extra instruction per test disappears in combine, but it is still there when the loop pass counts
   the loop (63 instructions instead of 61), and that count decides which constants get hoisted: with 62..64 the
   1 of EFT_SPR_DRAW_MODE1 is moved out of the loop and the 2 of EFT_SPR_DRAW_MODE2 is not (the pass moves a
   one-instruction constant only while `threshold >= count`, threshold 64 less 3 per move). Which tests went
   through a helper in the original is not known: one or both layer tests, or up to three of the draw-flag
   tests, all give the same code. */
static inline s32 EftSprLayerDef_TestFlag(const EftSprLayerDef *def, s32 flag);

void EftSprAnim_Draw(EftSprAnim *anim);

/* 1 while any layer has not finished. */
s32 EftSprAnim_IsPlaying(EftSprAnim *anim);

/* Sets the object's position. */
void EftSprAnim_SetPos(EftSprAnim *anim, Vec4 *pos);

/* Sets the object's forward axis. */
void EftSprAnim_SetDir(EftSprAnim *anim, Vec4 *dir);

/* Sets the object's scale. */
void EftSprAnim_SetScale(EftSprAnim *anim, Vec4 *scale);

/* Sets the object's colour (0..1 per channel, alpha included). */
void EftSprAnim_SetColor(EftSprAnim *anim, Vec4 *color);

/* Sets the slot's flag (draw mode of the layers that follow it). No caller. */
void EftSprAnim_SetSlotFlag(EftSprAnim *anim, s32 flag);

/* Sets the draw overrides (EFT_SPR_DRAW_*). */
void EftSprAnim_SetDrawFlags(EftSprAnim *anim, s32 flags);

/* Gives every texture the layers use VRAM for this frame, once per texture per set. */
void EftSprAnim_KeepTextures(EftSprAnim *anim);

/* Puts every layer back at its first frame (as EftSprAnim_Start, keeping the spin). */
void EftSprAnim_Restart(EftSprAnim *anim);

/* Keeps three angles in degrees inside 0..360. */
void EftSprAnim_WrapDegrees(Vec4 *v);

/* Builds the rotation whose third row is dir (first row right, second row up). 0 when dir has no length. */
s32 EftSprAnim_BuildDirMtx(EftAeMtx *out, Vec4 *dir);

/* Builds the object's two frames: oriented along its direction, and facing the camera; both scaled. */
s32 EftSprAnim_BuildMatrices(EftSprAnim *anim, EftAeMtx *oriented, EftAeMtx *billboard);

/* Draws one layer (argument order of the caller's loop). */
void EftSprAnim_DrawLayer(EftSprLayerDef *def, s32 frame, s32 time, EftAeTexSet32 *tex, EftAeMtx *m,
                          EftAeMtx *oriented, Vec4 *pos, Vec4 *spin, Vec4 *color, s32 mode, s32 rand1, s32 rand2);

/* Draws one layer at a frame: interpolates position, rotation, scale and colour between the two keys around
   the frame, applies jitter and spin, builds a 10 x 10 quad in the layer's frame `m` around the key position
   (rotated by the object's oriented frame), picks the flip-book cell or applies the blink, queues a packet that
   resets CLAMP at the quad's depth and then the quad itself. The depth is the projected centre's z >> 8, or the
   far end (0xFFF) in draw mode 2. rand1 / rand2 are the layer's two random values of this step. */
void EftSprAnim_DrawLayerAt(EftAeMtx *m, EftAeMtx *oriented, Vec4 *objPos, EftSprLayerDef *def, s32 frame, s32 time,
                            EftAeTexSet32 *tex, Vec4 *spin, Vec4 *color, s32 mode, s32 rand1, s32 rand2);

/* Adds this frame's random jitter to a layer's scale (x and y, x only, y only), on frames that are a multiple
   of the layer's jitter period. */
void EftSprAnim_Jitter(Vec4 *scale, EftSprLayerDef *def, s32 frame, s32 rand1, s32 rand2);

/* Number of cells of a texture grid kind. */
s32 EftSprAnim_GetGridCells(s32 grid);

/* Writes the four corner uv of one cell of a texture grid (nothing for an unknown grid kind). */
void EftSprAnim_SetGridUv(Vec4 *uv, s32 grid, s32 cell);

/*
 * EftSprAnim_DrawQuad (0x1ABF48) and EftSprAnim_DrawQuadSubdiv (0x1AC650) are left in assembly. Both end in the
 * same inlined code, read from the disassembly and reproduced by the attempt below except for register
 * allocation and the order of a few constant loads:
 *   - a triangle (three corners with uv and colour) is clipped against the five planes of the view
 *     (EftGfx_UpdateClipPlanes / GetClipPlanes, ClipPoly_ClipPlane), projected (ClipPoly_ProjectCur) and written as a fan;
 *   - each fan triangle is skipped when its three alphas are 0 or less; every projected z is capped at 0xFFFFFF;
 *   - the packet (0x90 bytes at gOtCur) is one gouraud textured alpha-blended triangle between CLAMP = 5 (clamp s
 *     and t) and CLAMP = 0: GIF tag of 14 registers PRIM, TEX0, CLAMP, 3 x (RGBAQ, ST, XYZF2), CLAMP, NOP; the
 *     second GS context is used for layers 2 and 3. Colours are the floats converted to bytes, q and s / t come
 *     from the projection. In draw mode 0 the vertex z is the projected z, in modes 1 and 2 it is 0xFFFFFF (drawn
 *     in front of everything);
 *   - the packet is linked into the ordering table at depth z (clamped to 0..0xFFF), in the chain of the layer
 *     (layer - 2 for layers 2 and 3).
 * DrawQuad sends the two triangles (0, 1, 2) and (1, 2, 3) of the quad. DrawQuadSubdiv cuts the quad into four
 * quarters first (corner 0 and the midpoints towards corners 1, 2, 3, shifted by each of the four half
 * diagonals) and gives every quarter the whole texture, mirrored so the pieces join (gEftSprSubdivCorner).
 * Neither reads anything but its arguments, the clip planes and the display list.
 */
#if 0 /* NON-MATCHING. DrawQuad: the same length and blocks; what differs is (1) the original computes the GS
         context bit as an int, uses it unextended for the TEX0 / first CLAMP register numbers and sign-extended
         from 8 bits for PRIM and the last CLAMP (here one s8 is used for all four), (2) it does so after the
         "i < n" entry test of the fan loop (here before it), (3) the two stq pointers swap registers and
         two header stores swap. DrawQuadSubdiv: the head (quarters, uv, 151 instructions) is identical; the
         rest is the same inlined code with the same differences.
         Second pass (cleanup step 12, about 200 variants, scratch in build/scratch_cleanup2_F/eftad/): the insns
         the original has are reproduced by `s32 ctx = otLayer >= 2;` inside QueueTri with
         prim = (abe << 6) | ((s64)(s8)ctx << 9) | 0x1B (abe an s64 local = 1) and
         gif1 = ((s64)ctx << 4) + ((s64)(s8)ctx << 48) + ((s64)ctx << 8) + 0xF8421421421860: the first loop pass
         hoists the chain into the fan loop's preheader as in the original, but the rerun of the loop pass then
         moves slti / xori (and what depends on them) out of the j loop as well (456 instructions, 98 differ).
         The rerun moves the slti when 64 * 2 * (1 + lifetime of the xori result) >= insns of the j loop (363),
         so it stays only when the xori result has ONE use, in the next insn. Forms with one use (an int copied
         to an s64, s8 taken from the s64) keep the chain in place (450 instructions, 46..51 differ) but add an
         `andi 0xff` (DI to QI truncation) the original does not have; an s8 variable or parameter gives SI
         sll / sra; ctx computed at the call site, at the top of the fan loop body or in an explicit
         `if (i < n) { ...; do { } while }` preheader is hoisted by the rerun all the same. Not found: a form in
         which the int has the two uses the original shows (64-bit shift pair on it, and << 4 / << 8) and is
         still left alone by the rerun. The z caps, the header store order (emitted: vif1, tag, vif0, gif0,
         clamp, next, prim, pad, gif1, clampEnd) and the t7 / s0 swap of the stq pointers were not settled
         either (best order tried: prim, tag, vif1, vif0, gif0, clamp, next, pad, gif1, clampEnd).
         Round 4 (no better attempt; a register-masked structural diff of this one is 37 lines, 35 with the
         header order prim, tag, vif0, vif1, gif0, gif1, clamp, next): what the dumps add to the above.
         (a) `slti` is not moved by the loop pass at all: gcse's PRE inserts `r = otLayer < 2` on the entry edge
         of the fan loop (behind the `i < n` test, where the original has it), so only the `xori` and what hangs
         on it are the loop pass's business. (b) A chain is moved as a whole only through "forces": a register
         used exactly once, by the next movable, hands its savings and lifetime to that one. The fan loop's
         first run therefore moves the xori only when its result lives 6 insns or more inside the fan loop
         (64 * 1 * lifetime >= 338), i.e. the context bit is computed EARLY in the loop body with code that is
         not moved between it and its uses; once hoisted the uses stand right behind it and the j loop's rerun
         sees a short lifetime. (c) In the rerun the slti (now inside the j loop, result used once) forces the
         xori, so the test is 64 * 2 * (1 + lifetime) against 364: lifetime 1 stays (256), lifetime 2 goes
         (384, 20 over). The original's xori result has two RTL uses at most two insns away (a sign extension
         to 64 bits for << 4 and << 8, which is a plain move, and the 8-bit sign extension for << 9 and << 48),
         so its j loop was at least 21 RTL insns longer than this attempt's at that point, or the slti did not
         force (its result used a second time). Neither was reproduced. (d) `li s1,2` sits in the delay slot of
         the ClipPoly_ProjectCur call in the original (here behind it), and the fan's entry test has the j
         reload `lw a0,748(sp)` as a dead slot instruction taken from the loop end. */
/* Queues one triangle (see above). ctx: 1 for the second GS context. */
static inline void EftSprAnim_QueueTri(EftAeScr *v0, EftAeScr *v1, EftAeScr *v2, Vec4 *c0, Vec4 *c1, Vec4 *c2,
                                       Vec4 *uv0, Vec4 *uv1, Vec4 *uv2, s32 otLayer, s32 z, u64 tex0, s32 mode, s8 ctx);

/* Clips a triangle against the five planes of the view, projects what is left and queues it as a fan. */
static inline void EftSprAnim_DrawTriClip(EftAeClipVtx *poly, s32 otLayer, s32 z, u64 tex0, s32 mode);

/* Draws a quad (two triangles from four corners), each clipped against the five planes of the view. */
void EftSprAnim_DrawQuad(u64 tex0, Vec4 *corner, Vec4 *uv, Vec4 *color, s32 otLayer, s32 z, s32 mode);

void EftSprAnim_DrawQuadSubdiv(u64 tex0, Vec4 *corner, Vec4 *uv, Vec4 *color, s32 otLayer, s32 z, s32 mode);
#else


#endif

/* Returns the pack (after a stripped check of its magic). */
EftSprPack *EftSprPack_Get(EftSprPack *pack);

/* Points every layer at its keys, which follow each other from the pack's key offset. */
void EftSprPack_Bind(EftSprPack *pack);

/* Number of layers. */
s32 EftSprPack_GetLayerCount(EftSprPack *pack);

/* The layer definitions. */
EftSprLayerDef *EftSprPack_GetLayers(EftSprPack *pack);

/* Frame of the key a looping layer jumps back from. */
s32 EftSprPack_GetLoopEndFrame(EftSprLayerDef *def);

/* Frame of the key a looping layer jumps back to. */
s32 EftSprPack_GetLoopStartFrame(EftSprLayerDef *def);

/* Number of keys. No caller. */
s32 EftSprPack_GetKeyCount(EftSprLayerDef *def);

/* Index of the key whose span contains a frame; -1 when none does. */
s32 EftSprPack_FindKey(EftSprLayerDef *def, s32 frame);

/* Position of a frame inside a key's span, 0..1 (1 for an empty span, 0 for no key). */
f32 EftSprPack_GetKeyT(EftSprLayerDef *def, s32 frame, s32 key);

/* Frame of the first key. No caller. */
s32 EftSprPack_GetFirstFrame(EftSprLayerDef *def);

/* Frame of the last key. No caller. */
s32 EftSprPack_GetLastFrame(EftSprLayerDef *def);

/* Whether the pack starts with "V000". */
s32 EftSprPack_IsValid(EftSprPack *pack);

/* Updates the root list. No caller. */
void BtlTaskList_UpdateRoot(void);

/* Runs the update callback of every task of a list, in list order, each followed by its child list; a task
   whose dead bit is set is removed instead. The task being updated is gBtlTaskCur. */
void BtlTaskList_Update(BtlTaskList *list);

/* Runs the post-update callbacks, in the same order. Dead tasks are left for the next update. */
void BtlTaskList_PostUpdate(BtlTaskList *list);

/* Runs the reset callback of every task (mask 0), or of the tasks tagged with mask (0x800, 0x1000, 0x2000);
   tasks whose dead bit is set afterwards are removed. */
void BtlTaskList_Reset(BtlTaskList *list, s32 mask);

/* Runs the draw callbacks of the tasks that have been updated at least once. */
void BtlTaskList_Draw(BtlTaskList *list);

/* Creates the root list. No caller (the scene keeps its own root). */
void BtlTaskList_CreateRoot(u32 count, u32 workSize);

/* Gives a task a child list of `count` tasks with `workSize` bytes of work each. */
BtlTaskList *BtlTask_CreateChildList(BtlTask *task, u32 count, u32 workSize);

/* The same for the task being updated; returns the list. No caller. */
BtlTaskList *BtlTask_CreateChildListCur(u32 count, u32 workSize);

/* Allocates a list, its tasks and their work blocks from the current battle pool. NULL when the parent already
   has a child list or the pool is full. */
BtlTaskList *BtlTaskList_Create(BtlTask *parent, u32 count, u32 workSize);

/* Destroys the root list. No caller. */
void BtlTaskList_DestroyRoot(void);

/* Destroys a task's child list. */
void BtlTask_DestroyChildList(BtlTask *task);

/* Kills every task of a list and frees its memory. */
void BtlTaskList_Destroy(BtlTaskList *list);

/* Adds a task to an empty list. Does not check that a free task exists. */
BtlTask *BtlTaskList_AddFirst(BtlTaskList *list, BtlTaskCls *cls, void *arg);

/* Adds a task at the head of a list (it is updated first). NULL when the list is full. */
BtlTask *BtlTaskList_AddHead(BtlTaskList *list, BtlTaskCls *cls, void *arg);

/* Adds a task at the tail of a list (it is updated last). NULL when the list is full. */
BtlTask *BtlTaskList_AddTail(BtlTaskList *list, BtlTaskCls *cls, void *arg);

/* Adds a task right after the one being updated. No caller. */
BtlTask *BtlTask_AddAfterCur(BtlTaskCls *cls, void *arg);

/* Adds a task right after another, in the same list. NULL when the list is full. */
BtlTask *BtlTask_AddAfter(BtlTask *task, BtlTaskCls *cls, void *arg);

/* Adds a task right before the one being updated. No caller. */
BtlTask *BtlTask_AddBeforeCur(BtlTaskCls *cls, void *arg);

/* Adds a task right before another, in the same list. NULL when the list is full. */
BtlTask *BtlTask_AddBefore(BtlTask *task, BtlTaskCls *cls, void *arg);

/* Clears a task's state, binds its class and runs the class's init callback with the creation argument. */
void BtlTask_Init(BtlTask *task, BtlTaskCls *cls, void *arg);

/* Removes every task of a list at once (term callbacks run). */
void BtlTaskList_KillAll(BtlTaskList *list);

/* Marks the task being updated as dead. No caller. */
void BtlTask_SetDeadCur(void);

/* Marks a task as dead: the list pass that next reaches it (update or reset) removes it. */
void BtlTask_SetDead(BtlTask *task);

/* Removes the task being updated at once. No caller. */
void BtlTask_KillCur(void);

/* Removes a task now: term callback, child list destroyed, unlinked, returned to the list's free tasks. */
void BtlTask_Kill(BtlTask *task);

/* Sets bits of a task's tag word (the hit pass reports its results with it). */
void BtlTask_SetTagBits(BtlTask *task, s32 bits);

/* Stores a position in a task (the hit pass reports the contact point with it). */
void BtlTask_SetPos(BtlTask *task, EftAeVec pos);

/* Sets bits of a task's tag word; used to tag a task with its owner (0x800 object id 0, else 0x1000). */
void BtlTask_SetOwnerTag(BtlTask *task, s32 bits);

/* The root list. No caller. */
BtlTaskList *BtlTaskList_GetRoot(void);

/* The task being updated. No caller. */
BtlTask *BtlTask_GetCurrent(void);

/* The task that owns the list a task is in. */
BtlTask *BtlTask_GetParent(BtlTask *task);

/* Allocates the effect VRAM list (from BtlScene_Init). */
void EftVram_Init(void);

/* Frees it. */
void EftVram_Term(void);

/* Sets the two allocation cursors. No caller. */
void EftVram_SetCursor(s32 imageBlock, s32 clutBlock);

/* Reads the two allocation cursors. No caller. */
void EftVram_GetCursor(s32 *imageBlock, s32 *clutBlock);

/* Gives a texture VRAM for this frame (image and CLUT), queues its upload and returns its TEX0 with the new
   TBP0 / CBP and the given TCC / TFX. The entry's own TEX0 keeps the base and palette fields cleared. */
u64 EftVram_AddTex(EftAeTex *tex, s32 tcc, s32 tfx);

/* The same for the image only (the CLUT field stays cleared). */
u64 EftVram_AddImage(EftAeTex *tex, s32 tcc, s32 tfx);

/* Gives a texture's CLUT VRAM for this frame and returns its block. */
u64 EftVram_AddClut(EftAeTex *tex);

/* Queues a texture's upload at given blocks and returns its TEX0. No caller. */
u64 EftVram_AddTexAt(EftAeTex *tex, s32 imageBlock, s32 clutBlock, s32 tcc, s32 tfx);

/* Gives every texture of a 32-entry set VRAM for this frame. */
void EftTexSet_Keep32(EftAeTexSet32 *set, s32 tcc, s32 tfx);

/* The same for a 4-entry set. */
void EftTexSet_Keep4(EftAeTexSet4 *set, s32 tcc, s32 tfx);

/* The same for an 8-entry set. No caller. */
void EftTexSet_Keep8(EftAeTexSet8 *set, s32 tcc, s32 tfx);

/* The same for a 16-entry set. No caller. */
void EftTexSet_Keep16(EftAeTexSet16 *set, s32 tcc, s32 tfx);

/* Uploads every texture queued this frame (from BtlScene_Draw, once per frame). */
void EftVram_UploadAll(void);

/* Empties the list and rewinds the cursors (from BtlScene_Draw, after the upload). */
void EftVram_Reset(void);

/* Empty: a stripped assert that a pack's texture count fits the set. */
void EftTexSet_CheckCount(s32 count, s32 max);

/* Builds a texture set of at most 32 entries from a texture pack. */
void EftTexSet_Load32(EftAeTexSet32 *set, void *pack);

/* Builds a texture set of at most 4 entries from a texture pack. */
void EftTexSet_Load4(EftAeTexSet4 *set, void *pack);
