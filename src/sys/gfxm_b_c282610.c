#define Heap_Free func_0028BB60  /* fix_targets */ /* the original uses 0x28bb60 here */
#define gGfxWater D_00387B04  /* fix_targets */ /* the original uses 0x387b04 here */
#include "common.h"
/*
 * Screen-space passes of the battle (0x106D60..0x109938): full-screen strips that read the depth buffer through a
 * CLUT, the alpha-key overlay of the battle objects, the lens discs, the underwater wobble and the depth fog.
 * The strips rely on GfxPostQuad_Set of the neighbouring file (gfxm_a.c), so the two are probably one source.
 * Proper names: gfx_post_b.c (0x106D60..0x107730), gfx_lens.c (..0x1085E0), gfx_alpha_key.c (..0x1087A8),
 * gfx_water.c (..0x1094A8) and gfx_depth_fog.c (..0x109938) if they are split later; nothing forces a split.
 */
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/gfxm_b.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void GfxPostQuad_Set(GfxQuad *out, s32 baseX, s32 baseY, s16 u0, s16 v0, s16 u1, s16 v1, s32 dx, s32 dy, s32 w, s32 h,
                          s16 half);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 k);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Div(Vec4 *dst, Vec4 *src, f32 d);
extern void Vec4_ToFixed4(IVec4 *dst, Vec4 *src);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Mtx_Transpose(Mtx44 *dst, Mtx44 *src);
extern void Vu0Screen_StoreMtx(Mtx44 *dst);
/* gfxm_b_b.c; declared with this file's views of the structures */
void TexFile_UploadPacked(GfxTexFile *file, s32 tbp, s32 cbp);
s32 Tex_Log2Size(s32 n);
void GfxClut_InitPacket(GfxClutWork *work, u16 cbp);
extern GfxWaterStage *BtlStage_GetList90(void);
void GfxWater_SetColor(s32 view, u8 r, u8 g, u8 b, s32 a);
extern s32 BtlStage_GetWaterLevel(f32 *level);
extern s32 Battle_IsSplitScreen(void);
extern s32 DemoCam_IsActive(void);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern f32 sqrtf(f32 x);
extern f32 cosf(f32 x);

/* The part of the battle work this file reads. */
typedef struct GfxBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 paused, 0x2000 loading */
} GfxBattleWork;
extern GfxBattleWork *Battle_GetWork(void);

/* Stack vectors as 16-byte aligned arrays (Sony sceVu0FVECTOR style): the compiler copies them with 64-bit loads. */
typedef f32 GfxFVec[4] __attribute__((aligned(16)));
typedef s32 GfxIVec[4] __attribute__((aligned(16)));
typedef f32 GfxFMtx[4][4] __attribute__((aligned(16)));

void GfxLens_Draw(s32 split, s32 side);
void GfxLens_DrawAll(GfxLensView *view, s32 split, s32 side);
u64 *GfxLens_PutCapture(u64 *p, s32 split, s32 side);
void GfxWater_DrawView(s32 split, s32 view);
void GfxPost_ShiftHighWord(s32 fbp, s32 tbp, s32 h);

#define GFX_RGBAQ_NEUTRAL 0x3F80000080808080 /* grey 0x80, alpha 0x80, Q = 1.0f */

/* Draws the spare byte of the depth buffer through a CLUT over the whole screen (16 strips of 32 pixels). */
void GfxPost_DrawDepthClut(s32 mode, s32 tbp, s32 cbp, u64 alpha);

/* Copies the alpha of the colour buffer being drawn into the spare top byte of the 24-bit depth buffer. */
void GfxPost_CopyAlphaToDepth(void);

/* Draws one textured sprite: `tex0` at (x, y) with size (w, h); the texel box is the whole texture, or 448 rows of it. */
void GfxPost_DrawTexRect(u64 tex0, s32 x, s32 y, s32 w, s32 h, s32 fullHeight);

/* Draws a blended untextured rectangle over the whole screen (16 strips), depth writes off; colour from four floats.
   `x` has to be a second induction variable (not `i * 32`): the compiler then builds the strips' start values from
   its initial value at run time (`move v1,zero / sll v1,v1,4`) instead of folding them. */
void GfxPost_DrawTintRect(u64 alpha, Vec4 *color);

/* Clears the flare table and its trailing words. */
void GfxLens_Init(void);

/* Empty. */
void GfxLens_Stub107758(void);

/* Clears the eight flare slots. */
void GfxLens_Clear(void);

/* Starts a flare at a world position in the first free slot; returns the slot, or -1 when all eight are busy. */
s32 GfxLens_Start(Vec4 *pos, s32 life, u32 rgba, s32 blend, f32 size);

/* Frees a flare slot. */
void GfxLens_Stop(u32 slot);

/* Sets a slot's hold flag: while set, the flare does not age. */
void GfxLens_SetHold(u32 slot, s32 hold);

/* Moves a flare. */
void GfxLens_SetPos(u32 slot, Vec4 *pos);

/* Draws one lens from its seven projected points: a black screen wipe in the chosen blend, the four mirrored
   quarters of the lens texture, then the captured screen stretched over the lens. */
void GfxLens_DrawOne(IVec4 *pt, s32 split, s32 side, u32 rgba, s32 blend);

/* True when a lens is in front of the camera and its box (points 0 and 3) touches the 512x448 screen. */
static inline s32 GfxLens_IsOnScreen(GfxIVec *scr);

/* Ages every live lens, projects its seven points with the camera and draws those that touch the screen.
   Its `offs` initialiser is the 0x70-byte table at 0x2EB6A0 (.rodata).
   Matching notes: the first inner loop has an explicit BYTE OFFSET as a second induction variable (`o += 0x10`,
   added to `offs` and to the address of pos[0].w, itself a variable set between `i = 0` and `v = pos`) next to
   the walking pointer `v`. With `offs[i]` / `pos[i].w` the loop pass builds the address of the w store from the
   `i * 16` that gcse leaves as a copy with a multiplication note (cost 12) and gives it a pointer of its own;
   with a real variable the two addresses are plain sums of benefit 0 and stay `base + o`. The form is what
   matches; whether the original spelled it this way (a macro, or three cursors) is not known. */
void GfxLens_DrawAll(GfxLensView *view, s32 split, s32 side);


/* Matching notes (strip loop, from the loop pass's dump): `col` and `x` are two variables; `u` exists only in
   the two later arms; the first strip's right edge is `x + i * 32 + 32` written out (its own induction
   variable); the Y halves are `(0x78 + i) << 8` and `(0x79 + i) << 8` (two expressions that do not share
   `i * 0x100`). Where `p += 2` stands decides the schedule, because each arm is scheduled as a block of its own
   before identical tails are merged: the two `side` arms of the first strip each hold both stores AND their
   `p += 2`; the two later arms share ONE final `p += 2` behind their if / else (which also breaks an
   allocation tie between `split` and the hoisted constant 1); the three scissor arms each end in `p += 2`. */
/* Writes the packet that copies the screen (or one half of a split screen) into the 256x256 buffer at page 0x150,
   as 16 strips, and then restores the frame, offset and scissor. Returns the end of the packet. */
u64 *GfxLens_PutCapture(u64 *p, s32 split, s32 side);


/* Draws the lenses of one view: uploads the lens texture, captures the screen and draws every live lens. */
void GfxLens_Draw(s32 split, s32 side);

/* Draws the lenses for a full-screen view. */
void GfxLens_DrawFull(void);

/* Fills a 256-entry CLUT (GS order) that is transparent except for entries 0xF4..0xFE, which get eleven fixed
   colours with alpha 0x30. */
void GfxAlphaKey_BuildClut(u8 *clut);

/* Allocates the depth-tint work, builds its CLUT upload packet and fills the CLUT. */
void GfxAlphaKey_Init(void);

/* Frees the depth-tint work. */
void GfxAlphaKey_Term(void);


/* Uploads the CLUT and draws the depth buffer's spare byte through it over the screen. */
void GfxAlphaKey_Draw(void);

/* Gives both water layers their default scroll speeds and an opaque grey. */
void GfxWater_Reset(void);

/* Allocates the two water layers. */
void GfxWater_Init(void);

/* Frees the water layers. */
void func_00282610(void) {
    if (gGfxWater != NULL) {
        Heap_Free(gGfxWater);
        gGfxWater = NULL;
    }
}

/* Takes the colour of both layers from the stage's water record when it has one. */
void GfxWater_LoadStageColor(void);

ASM_STUB_BEGIN(); /* compiled so that GfxWater_Draw sees the definition (it decides a branch-likely there); the assembler skips it */
/* NOT MATCHING: 96 of 639 instructions differ (was about 390 aligned), and the instruction count is now the
   original's. Same operations and the same six .lit4 constants (0x2FC2A0..0x2FC2B4: pi, 2 pi, 2 pi, 0.8, 0.2,
   44.8; bits compared) plus the .sdata word 0x2FE8D0 = 224.
   Found in the third cleanup (each of these removed a block of differences):
   - `h = 0xE0` and `srcH = 0x1C0` are VARIABLES set at the top (as in StgHaze_Draw / StgBlur_Draw). That is
     why the original loads 0xE00 into a register for the gv clamp (`h << 4`), keeps `(s64)h << 34` apart
     from the `| 0xA` of the second CLAMP word, multiplies `srcH * row` with a real `mult`, and converts 224
     to float from a constant-pool word in .sdata (`fh = h`: the old attempt read D_002FE8D0 as a global).
   - the copy loop is the twin of the first loop of StgPanBlur_DrawView (same statements, other constants):
     `step = w / n` unshifted and `(i * step) << 4` in the loop.
   - there is no `y` variable: `cy = h * row / 5`. The slot at sp+0x234 that looked like one is the loop
     pass's strength-reduced `h * row` (it sits BEHIND the `view * 4` that gcse creates, so it was made later
     than any declared variable).
   - the three row loops share one counter (the original keeps it in s3 throughout).
   What still differs:
   1. float registers of the inner body: the original has ph in f20, d in f21, dx in f22; this has d, dx, ph
      (allocation priority: ph needs about a third more references). In the original the result of the
      SECOND sqrtf is computed straight into f20 (`sqrt.s f20,f12`, a callee-saved register, so that pseudo
      is live across a call) and copied to d; the first goes through f0. `ph = sqrtf(..); d = ph;` is folded
      back by cse.
   2. the 9-register packet header: the original loads x0 early and builds the ZBUF constant late; the first
      CLAMP word is `x0 << 4 | 0x1C0 << 34 | x1 << 14 | 0xA` with the two constants NOT merged, which
      `(s64)srcH << 34` reproduces locally but then the function's first third changes (the phase update
      stops spilling `view * 4`), so it is not in this attempt.
   3. in the last loop the original loads gv before gu (`gv << 16 | gu` makes other things worse).
   Also tried: `rows = 6` as a variable with `rows - 1` as the divisor (worse everywhere, although the
   original divides by a 5 held in a register without a zero check). */
/* Draws the underwater wobble for one view: advances the view's two phases, builds a 6 x N grid of texel positions
   pushed around two wave centres, copies the view into the half-height buffer at page 0x150 and draws it back over
   the screen as five triangle strips tinted with the view's colour. */
void GfxWater_DrawView(s32 split, s32 view);

ASM_STUB_END();


/* Draws the underwater wobble for every view whose camera is below the stage's water level. */
void GfxWater_Draw(void);

/* Sets the tint of a view's underwater wobble. */
void GfxWater_SetColor(s32 view, u8 r, u8 g, u8 b, s32 a);

/* Fills a 256-entry CLUT (GS order) with black whose alpha falls from 255 at index 0 to 0 at index 255. */
void GfxDepthFog_BuildClut(u8 *clut);

/* Moves the upper 16 bits of every pixel of the 32-bit buffer at block `tbp` into the top two bits of page `fbp`
   seen as a 16-bit buffer: 32 sprites of 8 x `h` shifted right by 8 pixels, write mask 0x3FFF.
   `w` and `tw` are two variables (both 8) and `u` is computed in front of the call: that gives the two strip
   counters their own step registers (s7, fp) in the original's order. */
void GfxPost_ShiftHighWord(s32 fbp, s32 tbp, s32 h);

/* Builds the depth fog's CLUT work: the upload packet for block `cbp` and the alpha ramp. */
void GfxDepthFog_Init(u16 cbp);

/* Draws the depth fog: uploads the ramp, moves the depth's high word into the frame's alpha bits, clears the
   colour of the depth page's alias and draws the depth through the ramp with the destination-alpha test on. */
void GfxDepthFog_Draw(void);

/* Empty. */
void GfxDepthFog_Stub109928(void);

/* Empty. */
void GfxDepthFog_Stub109930(void);
