#include "common.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "battle/btl_demo_cam.h"
#include "battle/stg_c.h"
#include "sys/dma.h"
#include "sys/fade.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/math3d.h"
#include "sys/ramp.h"
#include "sys/randf.h"

/*
 * Battle screen effects, 0x245F58..0x248F28. See include/battle/stg_c.h for the overview.
 * Everything here is drawing: no function reads or writes a fighter, a hit record, a rigid body or
 * stage collision.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Length(Vec4 *v);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);

/* The depth fog filter of the previous module (0x245370..0x245F58); only the fields used here. */
typedef struct StgFogView {
    /* 0x000 */ u8 unk0[0x500];
    /* 0x500 */ StgCurve curve;
    /* 0x5D0 */ u32 color;
    /* 0x5D4 */ s32 clearLast; /* the last CLUT entry is forced to 0 */
} StgFogView;

extern StgFogView *gStgFog;
extern void StgFog_BuildClut(StgFogView *fog, StgCurve *curve, s32 clearLast, f32 scale);

/* Stage parameter file readers (0x242B78..0x242F18, named in config/symbols/stg_a.txt; declared here with
   the types this file needs). */
extern void *BtlStage_GetList50(void);        /* fog section, or NULL */
extern StgHazeParam *BtlStage_GetListA0(void); /* haze section, or NULL */
extern u8 *BtlStage_GetList80(void);          /* tint section: two RGBA byte colours, or NULL */
extern s32 BtlStage_HasFeature(s32 feature);   /* 1 when the stage file turns the feature on */
extern f32 BtlStage_GetTop(void);        /* stage word +4 of the stage block's +0x40 table (see stg_a) */

/* Other members of the group (0x102F28..0x10A5A0, 0x2446B0..0x245F58). */
extern void StgPanBlur_Init(s32 base);
extern void StgPanBlur_Draw(void);
extern void StgPanBlur_Term(void);
extern void StgGlare_Update(void);
extern void StgGlare_Reset(void);
extern void StgGlare_Init(u16 base);
extern void StgGlare_Term(void);
extern void StgGlare_Draw(void);
extern void StgGlare_LoadParams(void);
extern void StgDepthTint_Rebuild(void);
extern void StgDepthTint_Init(u16 base);
extern void StgDepthTint_Term(void);
extern void StgDepthTint_Draw(void);
extern void StgDepthTint_LoadParams(void);
extern void GfxPost_InitNop(void);
extern void GfxPost_TermNop(void);
extern void GfxPost_DrawDepthClut(s32 mode, s32 base, s32 clutBase, u64 alpha);
extern void GfxPost_DrawTintRect(u64 alpha, Vec4 *color); /* blended full-screen rectangle */
extern void GfxLens_Init(void);
extern void GfxLens_Stub107758(void);
extern void GfxLens_Clear(void);
extern void GfxLens_DrawFull(void);
extern void GfxWater_Init(void);
extern void GfxWater_Term(void);
extern void GfxWater_LoadStageColor(void);
extern void GfxWater_Draw(void);
extern void GfxDepthFog_Init(u16 base);
extern void GfxDepthFog_Draw(void);
extern void GfxClut_InitPacket(StgHaze *haze, u16 clutBase);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_ClearTrans(Mtx44 *m);
extern void ScrXfade_Init(void);
extern void ScrXfade_Term(void);
extern void ScrXfade_Reset(void);
extern void ScrXfade_Update(void);
extern void ScrXfade_PostDraw(void);
extern void ScrWarp_Init(void);
extern void ScrWarp_Term(void);
extern void ScrWarp_Reset(void);
extern void ScrWarp_Update(void);
extern void StgFog_Init(s32 base);
extern void StgFog_Term(void);
extern void StgFog_ResetColor(void);
extern void StgFog_Draw(void);
extern void StgFog_SetParams(void *param);

/* 0x2FEC20: the two depth haze views. */
extern StgHaze *gStgHaze;
/* 0x2FEC28: the two radial blur views. */
extern StgBlur *gStgBlur;
/* 0x2FF208: the group's one word of state: non-zero = every draw pass is skipped. */
extern s32 *gStgFx;
/* 0x31C4A0: the four colour layers. */
extern StgTintWork gStgTint;
/* 0x31C630: slot 0's colour as integers (read by the effect code at 0x136FB8 / 0x137F60). */
extern s32 gStgTintColor0[4];

/* Sets the fog colour word. */
void StgFog_SetColor(s32 r, s32 g, s32 b, s32 a);

/* Returns the fog's depth curve. */
StgCurve *StgFog_GetCurve(void);

/* Rebuilds the fog look-up from its curve at full strength. */
void StgFog_RebuildClut(void);

/* Samples the Hermite segment k0 -> k1 at steps + 1 points into table[curve->count...]; returns the last value (0..255). */
f32 StgCurve_AddSegment(StgCurve *curve, f32 *table, StgCurveKey *k0, StgCurveKey *k1, s32 steps);

/* Computes the middle key's tangents and fills table[0..255] with the curve (0..1). */
void StgCurve_Build(StgCurve *curve, f32 *table);

/* Uploads the haze look-up, writes depth as alpha into the frame, and opens the packet that redraws the frame. */
void StgHaze_BeginDraw(StgHazeDraw *d, StgHaze *haze, s32 x0, s32 x1, s32 width, s32 h, s32 tmpW, s32 tmpH);

/* Closes the packet opened by StgHaze_BeginDraw. */
void StgHaze_EndDraw(StgHazeDraw *d);

/* Starts one textured triangle strip of nVerts vertices in the haze colour. */
void StgHaze_PutStripTag(StgHazeDraw *d, StgHaze *haze, s32 nVerts);

/* Does nothing (end of a strip). */
void StgHaze_EndStrip(StgHazeDraw *d);

/* Appends one strip vertex: texel (u, v) in pixels, position (x, y) in sixteenths. */
void StgHaze_PutVertex(StgHazeDraw *d, s32 u, s32 v, s32 x, s32 y);

/* Builds the packet template of one haze view. */
void StgHaze_Create(StgHaze *haze, u16 clutBase);

/* Fills the look-up: entry i (in CLUT storage order) = black with alpha curve(i) * 128 * scale. */
void StgHaze_BuildClut(StgHaze *haze, StgCurve *curve, f32 scale);

/* Allocates and creates the two haze views. */
void StgHaze_Init(u16 clutBase);

/* Frees the haze views. */
void StgHaze_Term(void);

/* Default parameters for both views. */
void StgHaze_Reset(void);

/* Rebuilds the look-up for the view's camera height: strength 1 - (cameraY / stageTop) * 0.5, so the haze
   is at full strength on the ground and at half strength at the top of the stage. */
void StgHaze_UpdateClut(StgHaze *haze, s32 split, s32 view);

/* Draws new random targets every `period` frames and moves the mesh offsets towards them. */
void StgHaze_Step(StgHaze *haze, s32 split, s32 view);

/*
 * Redraws the frame as rows - 1 triangle strips of cols * 2 vertices. Strip `row` spans the lines
 * row * 448 / (rows - 1) .. (row + 1) * 448 / (rows - 1) of the source (v) and half of that on the
 * target (y, in sixteenths; the target is one field, 224 lines); column `col` is at
 * col * width / (cols - 1). The top vertex is displaced by curX/curY[row][col], the bottom one by
 * curX/curY[row][col + 1] (the next column of the SAME row, not the next row), both clamped to the
 * view.
 * Matching notes: only the packet pointer is in memory (StgHazeDraw is one pointer). Everything the
 * original keeps at sp+4 .. sp+0x30 is a spilled pseudo register, in creation order: the parameter and
 * the declared locals first (haze, width, widthPx, xOffset, cols, y0, y1), then compiler temporaries in
 * the order the statements create them: the quotient of v0 (0x20), `row + 1` (0x24, first written in
 * the y1 statement, which therefore comes BEHIND v0), the quotient of v1 (0x28), and last the registers
 * that later passes create for `rows - 1` (0x2C) and `cols * 2` (0x30).
 * So there are no nextRow / lastRow / nVerts / divisor variables in the source: `rows - 1`, `row + 1`
 * and `cols * 2` are written out at every use. (v0 and v1 themselves disappear: a division always
 * lands in a temporary on this compiler and the copy is propagated.)
 */
void StgHaze_Draw(StgHaze *haze, s32 split, s32 view);

/* One view: look-up, jitter (not while paused), draw. */
void StgHaze_DrawView(s32 split, s32 view);

/* Draws the haze for whatever views are on screen. */
void StgHaze_DrawAll(void);

/* Loads the stage's haze parameters into both views (defaults when the stage has none). */
void StgHaze_SetParams(StgHazeParam *param);

/* Sets the mesh size of a view. */
void StgHaze_SetGrid(s32 view, s32 cols, s32 rows);

/* Sets the jitter range of a view. */
void StgHaze_SetAmplitude(s32 view, s32 ampX, s32 ampY);

/* Sets the colour of a view. */
void StgHaze_SetColor(s32 view, s32 r, s32 g, s32 b, s32 a);

/* Sets how often new targets are drawn and how fast the mesh follows them. */
void StgHaze_SetSpeed(s32 view, s32 period, f32 follow);

/* Returns a view's depth curve. */
StgCurve *StgHaze_GetCurve(s32 view);

/* Rebuilds a view's look-up. */
void StgHaze_RebuildClut(s32 view);

/* Turns every draw pass of the group off (1) or on (0). */
void StgFx_SetDisabled(s32 disabled);

/* Resets every member of the group and reloads the stage's fog and haze parameters. */
void StgFx_Reset(void);

/* Creates the group. The arguments are GS texture blocks reserved for each member. */
void StgFx_Init(void);

/* Destroys the group. */
void StgFx_Term(void);

/* First draw pass (after the scene): steps the tints, then the depth-based filters the stage turns on. */
void StgFx_DrawPre(void);

/* Second draw pass: nothing. */
void StgFx_DrawNop(void);

/* Third draw pass: the white stage-change fade, then the blur and its neighbours. */
void StgFx_DrawPost(void);

/* Fourth draw pass: the front tints, then releases finished tints. */
void StgFx_DrawOverlay(void);

/* The first pass without the stage-feature and flag tests (and without haze and back tints). */
void StgFx_DrawPreNoCheck(void);

/* color = from + delta * ramp.value. */
void StgTint_CalcColor(StgTint *tint);

/* Turns every slot off. */
void StgTint_Reset(void);

/* Clears the work block. */
void StgTint_Init(void);

/* Steps the ramp of every slot that is on. Slots 0..2 wait while the battle is paused; slot 3 does not. */
void StgTint_Update(void);

/* Turns off the slots whose way back has ended. */
void StgTint_Release(void);

/* Draws slots 0 and 1 over the scene and publishes slot 0's colour as integers. */
void StgTint_DrawBack(void);

/* Does nothing. */
void StgTint_Nop(void);

/* Draws slots 3 and 2 over everything, each only when its alpha is above 0.001. */
void StgTint_DrawFront(void);

/* Starts a slot's ramp: dir 0 goes to the slot's second colour, dir 1 back to the first. */
/* Starts a slot's ramp: dir 0 goes to the slot's second colour, dir 1 back to the first. A slot that is off
   ignores dir 1; a slot already going the asked way is left alone; a running slot restarts from its current
   colour. Slot 0's two colours come from the stage file when it has a tint section. */
void StgTint_Start(u32 slot, s32 dir, f32 seconds);

/* Copies slot 0's integer colour. */
void StgTint_GetColor0(s32 *out) {
    out[0] = gStgTintColor0[0];
    out[1] = gStgTintColor0[1];
    out[2] = gStgTintColor0[2];
    out[3] = gStgTintColor0[3];
}

/* Returns the work block. */
StgTintWork *StgTint_GetWork(void);

/* 1 when the slot is on. */
s32 StgTint_IsOn(u32 slot);

/* Opens the blur packet. */
void StgBlur_BeginDraw(StgBlurDraw *d, s32 x0, s32 srcW, s32 width, s32 srcH, s32 dstW, s32 dstH);

/* Closes the blur packet. */
void StgBlur_EndDraw(StgBlurDraw *d);

/* Starts one textured Gouraud triangle strip of nVerts vertices (colour, texel, position per vertex).
   Both callers pass 1 as a third argument, which is not used. */
void StgBlur_PutStripTag(StgBlurDraw *d, s32 nVerts, s32 unused);

/* Does nothing (end of a strip; StgBlur_Draw calls it with its packet cursor). */
void StgBlur_Nop(StgBlurDraw *d);

/* Allocates the two blur views. */
void StgBlur_Init(void);

/* Frees the blur views. */
void StgBlur_Term(void);

/* Defaults: 3 passes, scale 2, grey corners with alpha 0 (off). */
void StgBlur_Reset(void);

/* One strip vertex of the final rings: colour (q = 1), texel (u, v) of the work buffer, position (x, y) in view pixels. */
static inline void StgBlur_PutVertex(StgBlurDraw *d, u32 rgba, s32 x, s32 y, s32 u, s32 v);

/*
 * Radial blur of one view. Nothing is drawn unless one of the three ring colours (centre, middle, edge)
 * has a non-zero alpha.
 *   1. View rectangle: 512 x 448 at x 0, or 256 x 448 at x 0 / 256 in split screen. The work buffers are
 *      half that size (256 or 128 x 224).
 *   2. Centre: blur->center as it is when blur->screenSpace is set; otherwise the view matrix (third
 *      argument) is copied, its translation cleared, and blur->center (a world direction) rotated by it.
 *      Only x and y are used.
 *   3. StgBlur_BeginDraw, then the view's part of the frame is copied at half size into work buffer 0
 *      (frame block 0x150 = texture block 0x2A00).
 *   4. `passes` times, with f = 1, 2, 4, ...: buffer (i & 1) is copied into the other buffer (half a texel
 *      off, so it is filtered), then drawn over that copy again as a blended sprite in colour `color3`
 *      whose texels are pulled in by grow = (int)(f * scale) on every side and shifted by
 *      (int)((float)(int)f * shiftX * center.x) and (int)(f * shiftY * center.y): a positive shift moves
 *      the near edge of the texel rectangle, a negative one the far edge.
 *   5. The frame buffer, the view's scissor and the last written work buffer (as texture) are selected and
 *      two rings of ten-vertex Gouraud strips are drawn around the point (0.5 + 0.5 * center) * size:
 *      centre (colour 0) -> points half way to the corners (colour 1), then those -> the corners
 *      (colour 2). The alpha of the three colours is the strength of the blur at each ring.
 * With passes <= 0 the texture of step 5 is block 0 (lastTbp keeps its initial 0); the game never sets that.
 * Emits two local tables and one constant in .sdata: 0x2FEC30 = {0x2A00, 0x2D80}, 0x2FEC38 = {0x150, 0x16C},
 * 0x2FEC40 = 448 (the integer the compiler converts to float for the centre's y).
 * Matching notes: only `p` is in memory (StgBlurDraw is one pointer); blur, width, half, xOffset and x1
 * are plain locals that the allocator leaves on the stack, which is what the 0x134..0x150 slots are.
 */
void StgBlur_Draw(s32 split, s32 view, Mtx44 *viewMtx);

/* Draws the blur for whatever views are on screen. */
void StgBlur_DrawAll(void);

/* Sets the number of passes. */
void StgBlur_SetPasses(s32 view, s32 passes);

/* Sets the growth per pass and the two shift factors. */
void StgBlur_SetScale(s32 view, f32 scale, f32 shiftX, f32 shiftY);

/* Normalises `center` in place and selects how StgBlur_Draw reads the stored centre. */
void StgBlur_SetCenter(s32 view, Vec4 *center, s32 screenSpace);

/* Corner colour 0 from components. */
void StgBlur_SetColor0Rgba(s32 view, u8 r, u8 g, u8 b, u8 a);

/* Corner colour 0. */
void StgBlur_SetColor0(s32 view, u32 rgba);

/* Corner colour 1 from components. */
void StgBlur_SetColor1Rgba(s32 view, u8 r, u8 g, u8 b, u8 a);

/* Corner colour 1. */
void StgBlur_SetColor1(s32 view, u32 rgba);

/* Corner colour 2 from components. */
void StgBlur_SetColor2Rgba(s32 view, u8 r, u8 g, u8 b, u8 a);

/* Corner colour 2. */
void StgBlur_SetColor2(s32 view, u32 rgba);

/* Corner colour 3 from components. */
void StgBlur_SetColor3Rgba(s32 view, u8 r, u8 g, u8 b, u8 a);

/* Corner colour 3. */
void StgBlur_SetColor3(s32 view, u32 rgba);
