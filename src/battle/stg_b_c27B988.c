#define Heap_Free func_0028BB60  /* fix_targets */ /* the original uses 0x28bb60 here */
#define gScrWarp D_00387AEC  /* fix_targets */ /* the original uses 0x387aec here */
#include "common.h"

/*
 * Stage module, second part: 0x242D28..0x245F58 (88 functions). See include/battle/stg_b.h.
 *
 *   0x242D28..0x2435C0  BtlStage_*: readers of the loaded stage data (feature tests, flag word, ambient colour,
 *                       light direction, stage number), the stage timers and BtlStage_Update.
 *   0x2435C0..0x244170  StgAmb_*: the stage's looping background sound and its per-stage volume handler.
 *   0x244170..0x244890  ScrXfade_*: cross-fade from a captured frame.
 *   0x244890..0x245878  ScrWarp_*: screen shock waves (frame redrawn through displaced texture coordinates).
 *   0x245878..0x245F58  StgFog_*: depth look-up table and the depth blur pass (the module continues in stg_c.c).
 *
 * Nothing here answers a collision query and nothing here writes fighter or battle state; the only state with
 * a gameplay reader is the stage flag word (BtlStage_HasMoon) and the stage timers' flag bit.
 */
#include "battle/battle.h"
#include "battle/battle_work.h"
#include "battle/stg_b.h"
#include "battle/btl_cam.h"
#include "sys/adx.h"
#include "sys/common.h"
#include "sys/debug.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/mathf.h"
#include "battle/btl_scene.h"
#include "sys/randf.h"
#include "sys/snd.h"

s32 BtlStage_IsReady(void);
f32 Stg_CalcYaw(f32, f32, f32, f32);
void BtlStage_UpdateObjs(void);
void StgModel_UpdateAnims(void);
void StgRigid_Update(void);
void Vec4_Copy(Vec4 *dst, Vec4 *src);
void Mtx_InverseRT(Mtx44 *out, Mtx44 *in);
s32 BtlStage_GetWaterLevel(f32 *out);
f32 Vec3_Dist(Vec4 *a, Vec4 *b);
void *memset(void *, s32, u32);

extern StgAmb gStgAmb;

void sceGsSetDefStoreImage(void *sp, s16 sbp, s16 sbw, s16 spsm, s16 x, s16 y, s16 w, s16 h);
s32 sceGsExecStoreImage(void *sp, void *dst);
void FlushCache(s32 mode);
void GfxClut_InitPacket(void *tex, u16 arg);
void StgCurve_Build(StgFogPoint *pts, f32 *curve);
void Vec4_Set(Vec4 *v, f32 x, f32 y, f32 z, f32 w);
void GfxPost_DrawDepthClut(s32 a, s32 tbp, s32 cbp, u64 alpha);
s32 Tex_Log2Size(s32 size);
void Mtx_Copy(Mtx44 *out, Mtx44 *in);
void Vu0Screen_StoreMtx(Mtx44 *out);
void Mtx_ProjectInt(Vec4 *out, Mtx44 *m, Vec4 *in);
void IVec4_ToFloat(Vec4 *out, Vec4 *in);

/* The path of StgAmb_Update10 (16-byte aligned: it is copied by doublewords). */
typedef struct StgAmbPath {
    Vec4 p[8];
} __attribute__((aligned(16))) StgAmbPath;

extern Vec4 D_002C6C10;

/* Tells whether the stage data has feature `kind` (0..13). */
s32 BtlStage_HasFeature(u32 kind);

/* Returns member `index` of the stage file, NULL when it is empty. */
void *BtlStage_GetFileMember(s32 index);

/* Stage effect resource A, when the stage flags allow it. */
void *BtlStage_GetFxResA(void);

/* Stage effect resource B, when the stage flags allow it. */
void *BtlStage_GetFxResB(void);

/* Stage effect resource C, when the stage flags allow it. */
void *BtlStage_GetFxResC(void);

/* Second pointer of effect resource A, when the first exists. */
void *BtlStage_GetFxResA2(void);

/* Second pointer of effect resource B, when the first exists. */
void *BtlStage_GetFxResB2(void);

/* Second pointer of effect resource C, when the first exists. */
void *BtlStage_GetFxResC2(void);

/* Tests stage flag 8. */
s32 BtlStage_HasFlag8(void);

/* Tests stage flag 0x10: the stage has a moon. */
s32 BtlStage_HasMoon(void);

/* Reads the stage's ambient colour as four ints; 0x80 grey when there is no stage. */
s32 BtlStage_GetAmbient(s32 *rgba);

/* Writes the stage's ambient colour. */
s32 BtlStage_SetAmbient(s32 *rgba);

/* Returns the stage number, -1 when there is no stage. */
s32 BtlStage_GetId(void);

/* Copies the stage's light direction (and remembers it); the remembered one when there is no stage. */
s32 BtlStage_GetLightDir(Vec4 *out);

/* Gives the place stored in section +0x2C: its first point and the yaw from it toward its second point. */
s32 BtlStage_GetPlace2C(Vec4 *pos, Vec4 *rot);

/* What a stage change leads to: 0xF, 3 or -1 by the stage's change kind. */
s32 BtlStage_GetChangeTarget(void);

/* Advances the stage timers; raises bit 2 for the frame a timer wraps. */
void BtlStage_UpdateTimers(void);

/* Per-frame stage update. */
void BtlStage_Update(void);

/* Sets the volume of the stage's looping sound (0..128 before the scale). */
void StgAmb_SetBgmVolume(s32 volume);

/* Plays a one-shot stage sound with the ambience scale applied. */
s32 StgAmb_PlaySe(u32 mask, s32 id, s32 volume, s32 pan, s32 pitch);

/* 1 up to `near`, falling linearly to 0 at `far`. */
f32 StgAmb_Falloff(f32 x, f32 near, f32 far);

/* Stage 0: constant volume. */
void StgAmb_Update00(void);

/* Stage 1: constant volume. */
void StgAmb_Update01(void);

/* Stage 2: volume by the camera's height above or below the water level. */
void StgAmb_Update02(void);

/* Stage 3: random thunder, volume by the camera's distance from the water level. */
void StgAmb_Update03(void);

/* Stage 4: random thunder at a quarter volume. */
void StgAmb_Update04(void);

/* Stage 5: constant volume. */
void StgAmb_Update05(void);

/* Stage 6: constant volume. */
void StgAmb_Update06(void);

/* Stage 7: constant volume. */
void StgAmb_Update07(void);

/* Stage 8: constant volume. */
void StgAmb_Update08(void);

/* Stage 9: constant volume. */
void StgAmb_Update09(void);

/* Stage 10: random thunder; volume by height over the water level and by the distance to a path of 8 points. */
void StgAmb_Update10(void);

/* Stage 11: louder near the water level. */
void StgAmb_Update11(void);

/* Stage 12: louder near the water level. */
void StgAmb_Update12(void);

/* Stage 13: constant volume. */
void StgAmb_Update13(void);

/* Stage 14: louder near the water level. */
void StgAmb_Update14(void);

/* Stage 15: random thunder. */
void StgAmb_Update15(void);

/* Stage 16: constant volume. */
void StgAmb_Update16(void);

/* Stage 17: constant volume. */
void StgAmb_Update17(void);

/* Stage 18: constant volume. */
void StgAmb_Update18(void);

/* Stage 19: constant volume. */
void StgAmb_Update19(void);

/* Stage 20: constant volume. */
void StgAmb_Update20(void);

/* Stage 21: constant volume. */
void StgAmb_Update21(void);

/* Stage 22: constant volume. */
void StgAmb_Update22(void);

/* Starts the ambience of the current stage: picks the handler and starts the looping sound, silent. */
void StgAmb_Start(void);

/* Runs the stage's ambience handler. */
void StgAmb_Update(void);

/* Silences and stops the looping sound. */
void StgAmb_Stop(void);

/* Drops the handler, then silences and stops the looping sound. */
void StgAmb_Term(void);

/* Starts the ambience. */
void StgAmb_Init(void);

/* Sets the scale of the looping sound's volume. */
void StgAmb_SetBgmScale(f32 scale);

/* Sets the scale of the one-shot sounds' volume. */
void StgAmb_SetSeScale(f32 scale);

/* Allocates the two capture buffers when they do not exist. */
void ScrXfade_AllocBuffers(void);

/* Frees the two capture buffers. */
void ScrXfade_FreeBuffers(void);

/* Reads the frame being shown back from the GS, upper and lower half. */
void ScrXfade_Capture(void);

/* Reads w x h pixels at frame block `sbp` into buffer `index` and builds the packet that uploads them again. */
#if 0 /* 4 of 121 instructions differ: before the first call the original emits `sra a1,a0,16` / `move a0,sp` ahead of the two `addu` that form p and e; this C emits the two `addu` first. Everything else is identical. Second cleanup, about 30 more variants, none changed the four instructions: declaration / assignment order of p, e, tag; xf as a local or gScrXfade at each use; `&xf->chain[index]` (53 differ); sbp as s32 with a cast at the call, a local copy of sbp or si; other prototypes for sceGsSetDefStoreImage; `&p[14]` for the image address; p or e assigned after the call (34+ differ). In the second scheduling pass the two `addu` and the two argument loads have equal priority, so the order comes from the first pass, where this C schedules the `addu` of p early (it feeds the load of buf[index], which is on the path to sceGsExecStoreImage); the original must have had that chain one step shorter or the argument chain one step longer. */
void ScrXfade_StoreHalf(s16 sbp, u16 w, u16 h, s32 index);
#else

#endif

/* Uploads the captured halves as a 512 x 448 texture at block `tbp` and draws it over the frame. */
void ScrXfade_Draw(s32 unused, s32 tbp, u8 alpha);

/* Allocates and clears the cross-fade state. */
void ScrXfade_Init(void);

/* Frees the buffers and the state. */
void ScrXfade_Term(void);

/* Stops any fade and frees the buffers. */
void ScrXfade_Reset(void);

/* Steps the fade (not while paused) and draws the captured frame while its alpha is not 0. */
void ScrXfade_Update(void);

/* Captures the finished frame when a capture was asked for. */
void ScrXfade_PostDraw(void);

/* Starts the fade ramp over `seconds` and stores the request word. */
void ScrXfade_Start(s32 request, f32 seconds);

/* Asks for a capture at the end of this frame. */
void ScrXfade_RequestCapture(void);

/* Tells whether the captured frame is being drawn. */
s32 ScrXfade_IsActive(void);

/* Starts the packet: copies the frame region x0..x1 at half size into the work buffer at block 0x2A00, then
   points the frame, scissor, clamp and texture registers at drawing that copy back over the region. */
void ScrWarp_BeginPacket(u64 **pp, s32 x0, s32 x1, s32 w, s32 h, s32 tw, s32 th);

/* Sends the packet built by the ScrWarp_Put* helpers. */
void ScrWarp_EndPacket(u64 **pp);

/* Starts a textured, blended triangle strip of `count` vertices. */
void ScrWarp_BeginStrip(u64 **pp, s32 count);

/* Ends a strip: nothing to do. */
void ScrWarp_EndStrip(u64 **pp);

/* Adds one strip vertex: frame pixel, texel and colour. */
void ScrWarp_PutVertex(u64 **pp, s32 x, s32 y, s32 u, s32 v, s32 rgba);

/* Takes a free object and counts it for `view`. */
ScrWarpObj *ScrWarp_Alloc(s32 view);

/* Releases an object. */
void ScrWarp_Free(ScrWarpObj *o);

/* Tells whether a projected point is in front of the camera and inside the 512 x 448 frame. */
s32 ScrWarp_IsOnScreen(Vec4 *screen);

/* One frame of a shock wave: grows the ring and rebuilds its vertices; frees it when its time or size is up. */
void ScrWarp_Step(ScrWarpObj *o);

/* Draws the rings of one view (or of both when not split): two strips of 21 vertex pairs per ring. */
void ScrWarp_Draw(s32 split, s32 view);

/* Allocates the manager and its objects and fills the direction table. */
void ScrWarp_Init(void);

/* Frees the objects and the manager. */
void func_0027B988(void) {
    if (gScrWarp != NULL) {
        Heap_Free(gScrWarp->objs);
        Heap_Free(gScrWarp);
        gScrWarp = NULL;
    }
}

/* Releases every object. */
void ScrWarp_Reset(void);

/* Projects new objects with their view's camera (dropping those off screen) and steps all of them. */
void ScrWarp_UpdateAll(void);

/* Draws the objects: one pass full screen, or one pass per view that has objects. */
void ScrWarp_DrawAll(void);

/* Per-frame entry: steps (not while paused) and draws while any object is in use. */
void ScrWarp_Update(void);

#define SCRWARP_ALPHA (128.0f / 255.0f)

/* Starts a shock wave at a world position for one view. Returns 0 when all 10 objects are in use. */
s32 ScrWarp_Spawn(s32 view, Vec4 *pos, f32 seconds, f32 radius, f32 width, f32 speed, f32 jitter);

/* Sets up the texture object of the table and remembers where its entries are. */
void StgFog_SetupTex(StgFog *tone, u16 arg);

/* Builds the alpha table from the curve through the control points. */
void StgFog_BuildClut(StgFog *tone, StgFogPoint *pts, s32 clearLast, f32 scale);

/* Allocates the depth tone state. */
void StgFog_Init(u16 arg);

/* Frees the depth tone state. */
void StgFog_Term(void);

/* Sets the draw colour back to neutral grey. */
void StgFog_ResetColor(void);

/* Draws the depth tone: the table turns depth into the frame's alpha, the frame is copied at half size into the
   work buffer, and the copy is blended back over the frame through that alpha (a blur that grows with depth). */
/* Emits two local tables in .sdata: 0x2FEC10 = {0x2A00, 0x2D80} (the work buffers as textures) and
   0x2FEC18 = {0x150, 0x16C} (as frame buffers).
   Matching notes: as in StgBlur_Draw the sizes are VARIABLES set at the top (`width`, `half`, `srcH`, `h`) and
   passed to both Dma_PutTexStrips calls. All four are needed: they are what occupies the saved registers the
   way the original has it (448 in s8; 0x4E, 0x30000, 0x47 and the second TEX0 value pushed into s3 / s5 / s6 /
   s7 by local allocation; 0xE re-materialised twice). With literals, or with only some of the four as
   variables, the same instructions come out in another schedule (88 of 230). The TEX0 word is
   `tbp | fbw << 14 | tw << 26 | th << 30` in that order, with tw declared before th. */
void StgFog_Draw(void);

/* Takes the three control points from the stage's parameters (defaults when NULL) and rebuilds the table. */
void StgFog_SetParams(StgFogParams *prm);
