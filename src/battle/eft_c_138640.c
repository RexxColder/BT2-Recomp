#include "common.h"
#include "battle/eft_c.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "battle/btl_pool.h"
#include "battle/btl_scene.h"
#include "sys/common.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/gfx_ot.h"

/*
 * Stage-attached effects, 0x136760..0x13A9D0. See include/battle/eft_c.h.
 * Everything in this file only builds draw data: no fighter, battle object or hit record is read or written.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern f32 Mathf_Sin(f32 angle);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);  /* inverse of a rigid transform (inferred) */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern f32 Vec3_Dist(Vec4 *a, Vec4 *b);         /* distance */
extern f32 Vec3_DistSq(Vec4 *a, Vec4 *b);         /* squared distance */
extern void Vu0Cur_Push(void);                    /* saves the VU0 matrix state */
extern void Vu0Cur_LoadMtx(Mtx44 *m);                /* loads a matrix into VU0 */
extern void Vu0Cur_Pop(void);                    /* restores the VU0 matrix state */
extern void Vu0Cur_ProjectInt(s32 *out, Vec4 *pos);     /* projects to GS screen coordinates */
extern void ClipVtx_Set(EftSurfVtx *out, f32 *pos, f32 *st, f32 *color);

extern void *BtlTask_CreateChildList(void *task, s32 capacity, s32 workSize);
extern void *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void BtlTask_DestroyChildList(void *task);
extern s32 BtlStage_IsReady(void);

/* Stage records (stg_b.c). */
extern u8 *BtlStage_GetFxResA2(void);
extern u8 *BtlStage_GetFxResB2(void);
extern u8 *BtlStage_GetFxResC2(void);
extern u32 *BtlStage_GetList90(void);
extern StgWeatherRec *BtlStage_GetList60(void);
extern StgSurfRec *BtlStage_GetList58(void);
extern u8 *BtlStage_GetList80(void);
extern void BtlStage_GetWaterLevel(f32 *out);
extern void StgTint_GetColor0(s32 *out);
extern s32 StgTint_IsOn(s32 arg);

/* Texture tables (0x1AD..0x1AE). */
extern void EftTexSet_Load32(EftTexTbl *tbl, s32 *data);
extern void EftTexSet_Load4(EftTexEntry *tex, s32 *data);
extern void EftTexSet_Load34(EftSurfTexTbl *tbl, s32 *data);
extern void EftTexSet_Keep32(EftTexTbl *tbl, s32 a, s32 b);
extern void EftTexSet_Keep4(EftTexEntry *tex, s32 a, s32 b);
extern u64 EftVram_AddTex(EftSurfSlot *slot, s32 a, s32 b);
extern void GfxClut_InitPacket(EftSurfBuf *buf, s32 id);

/* Sprite draws of the effect core. */
extern void EftGfx_DrawSprite(Vec4 *pos, Vec4 *color, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 rot, s32 a,
                          s32 b, u64 tex0);
extern void EftPrim_DrawQuadDepth(Vec4 *pos, Vec4 *color, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 rot, s32 a,
                          s32 b, u64 tex0);

/* The geyser (eft_b.c) and the emitters it starts (eft_g.c smoke, eft_e.c steam). */
extern void EftGeyser_Update(EftTask *task);
extern s32 EftSmoke_Create(EftGeyserSmokeArg *arg);
extern s32 EftSmoke_GetPos(s32 handle);
extern s32 EftSteam_Create(EftGeyserSteamArg *arg);
extern void EftSteam_SetPaused(s32 handle, s32 on);
extern s32 EftSteam_GetWork(s32 handle);

extern void EftGndDust_InitTemplate(void);

/* Clip planes and helpers of the effect core. */
extern void EftGfx_UpdateClipPlanes(void);
extern Vec4 *EftGfx_GetClipPlanes(void);
extern s32 ClipPoly_ClipPlane(EftSurfVtx *poly, Vec4 *plane, s32 count); /* clips in place, returns the new count */
extern void ClipPoly_ProjectCur(s32 (*xyz)[4], Vec4 *st, EftSurfVtx *poly, s32 count); /* projects count vertices */
extern void EftMath_CalcTangentFrame(Mtx44 *out, EftVec *a, EftVec *b);
extern void EftGfx_LightClutDiffuse(EftSurfClut *dst, EftSurfClut *src, Vec4 *light, u8 r, u8 g, u8 b);
extern void EftGfx_LightClutSpecular(EftSurfClut *dst, EftSurfClut *src, Mtx44 *view, Mtx44 *frame, Vec4 *light, f32 k);
extern u64 EftVram_AddImage(EftTexEntry *tex, s32 a, s32 b);
extern u64 EftVram_AddClut(EftTexEntry *tex);

/* eft_d.c */
extern void EftSurf_DrawPolyOtClipped(EftSurfVtx *poly, s32 unused, u64 *tex, Vec4 *fog, s32 zBias);
extern void EftSurf_DrawTriDirect(s32 *xyz0, s32 *xyz1, s32 *xyz2, Vec4 *rgba0, Vec4 *rgba1, Vec4 *rgba2, Vec4 *st0,
                                  Vec4 *st1, Vec4 *st2, s32 a, u64 *tex, Vec4 *fog, s32 b);

/* Stage manager (stg_b.c); only the flag word is used here. */
typedef struct EftStageMgrView {
    /* 0x00 */ s32 unk0[2];
    /* 0x08 */ s32 flags; /* bit 0: the stage is not drawn */
} EftStageMgrView;
extern EftStageMgrView *gBtlStage;

/* Battle resources at gCommonRes + 0x20: only the stage pack. */
typedef struct EftCommonResView {
    /* 0x00 */ u8 unk0[0x24];
    /* 0x24 */ s32 *stage;
} EftCommonResView;
#define STAGE_PACK() (((EftCommonResView *)gCommonRes)->stage)

extern EftTaskClass gEftWeatherPtclClass;
extern EftStageKind gEftStageKinds[10];

static inline u8 EftTask_IsDead(EftTask *task);

/* Returns EftSmoke_GetPos of a live geyser's smoke emitter, 0 when the task is not a geyser or has none. */
s32 EftGeyser_GetSmokePos(EftTask *task);

/* Returns EftSteam_GetWork of a live geyser's steam emitter, 0 when the task is not a geyser or has none. */
s32 EftGeyser_GetSteamWork(EftTask *task);

/* Starts the geyser's smoke emitter with the colours of the stage's record. Two rand() calls (the
   description's unk38 and unk48). */
#if 0
/* Not matching: 17 of 162 instructions, all in the block that fills `init`. Same instructions and constants,
 * but the stores are scheduled in another order: the original emits them in field order except colorA.y (after
 * colorA.z) and colorB.y (last), this emits the last store of each shared constant first and the others at the
 * end; 2.0 and 0.985 then swap $f4 / $f5. Tried: field order permutations, chained assignments, an inline
 * setter, float-array fields, an initializer list.
 * Second pass (cleanup 2): the order is the first scheduling pass's, and it follows a simple rule that the natural
 * code obeys elsewhere (EftPrim_DrawBillboard's UV stores): among stores that are ready together, those whose
 * source register DIES there go first in source order, then the others in source order. With one register per
 * constant (which is what CSE makes of any spelling tried) that rule cannot give the original order: it would
 * need the x store of each vector (colorA.x, colorB.x, and pos.w / colorA.w) to be the last use of its own value.
 * So in the original the first component of each vector did not share its value with the others at that point.
 * A hill-climb over all orders of the 19 statements (build/scratch_cleanup2_A/search.py) stops at 11 differing
 * instructions, with an order that is not credible as source; the field-order attempt is kept. */
void EftGeyser_StartSmoke(EftTask *task);
#endif


/* Starts the geyser's steam emitter with the colour of the stage's record, and pauses it. */
#if 0
/* Not matching: 19 of 126 instructions, the same store-order problem as EftGeyser_StartSmoke: the original stores
 * color.x right after unk10.w and color.y / color.z / unk44 last; this stores color.x with them. The three
 * position loads then alternate $f1 / $f0 the other way round.
 * Second pass: see EftGeyser_StartSmoke. Here the original order is exactly "color.x has a value of its own,
 * color.y / z / w share another": then x and w are both last uses and go first, y / z / unk44 wait. No spelling
 * found gives two values (chained assignments in every grouping, copies of color.x, a brace initialiser: that one
 * also clears the tail and is 19 instructions longer). The memset + unk10.w pair does look like the compiler's
 * own expansion of a mostly-zero `{ 0, 0, 0, 1 }` constructor. The search over statement orders stops at 12. */
void EftGeyser_StartSteam(EftTask *task);
#endif


/* Outcode of a clip-space point: which of the six planes +-w it is outside of. */
s32 EftWeather_ClipCode(Vec4 *v);

/* Task init: when the stage's weather record is on, allocates the state and adds the particle task. */
void EftWeather_Init(EftTask *task);

/* Task term: frees the state. */
void EftWeather_Term(void);

/* Task update: wind of this frame = base wind plus a sine on x and z; the angle advances 0..3 degrees (rand). */
void EftWeather_Update(void);

/* Particle task init: scatters the particles. */
void EftWeatherPtcl_Init(EftTask *task);

/* Particle task term: nothing. */
void EftWeatherPtcl_Term(void);

/* Classifies the camera movement since the last frame: 2 = jumped (more than 15 units), 1 = moving (more than
   4, or still settling), and keeps the per-view settle counter. */
static inline void EftWeather_TrackCam(Vec4 *cam, EftWeatherView *view, s32 second, s32 *moving);

/* Moves the particles of one view. Each particle random-walks its velocity (3 rand()), drifts with the wind,
   and wraps around an 80-unit box centred 55 units in front of the camera. The alpha fades with the distance
   to the camera, after a wrap, while the camera moves, with height, near y = 0 and with the stage tint.
   Camera-dependent and called from the draw callback: purely visual. */
void EftWeather_Move(EftWeatherPtcl *p, EftWeatherView *view, s32 count);

/* Particle task update: refreshes the weather textures. */
void EftWeatherPtcl_Update(void);

/* Particle task post-update: nothing. */
void EftWeatherPtcl_PostUpdate(void);

/* Particle task reset: random position within +-51 units of the camera, random texture (4 rand() each). */
void EftWeatherPtcl_Reset(EftTask *task);

/* Draws count particles as sprites of size * 16. */
void EftWeather_DrawPtcls(EftWeatherPtcl *p, s32 count);

/* Particle task draw: moves this view's particles (unless paused), then draws them. In split-screen each
   view owns half of the particles. */
void EftWeatherPtcl_Draw(EftTask *task);

/* Sets the number of particles. */
void EftWeather_SetCount(s32 count);

/* Returns the number of particles. */
s32 EftWeather_GetCount(void);

/* Sets the particle flags. */
void EftWeather_SetFlags(s32 flags);

/* Returns the particle flags. */
s32 EftWeather_GetFlags(void);

/* Returns the base wind vector, NULL without weather. */
Vec4 *EftWeather_GetWindPtr(void);

/* Sets the particle size. */
void EftWeather_SetSize(f32 size);

/* Returns the particle size. */
f32 EftWeather_GetSize(void);

/* Sets the weather colour. */
void EftWeather_SetColor(u8 r, u8 g, u8 b);

/* Returns the weather colour, alpha 0x80. */
void EftWeather_GetColor(s32 *out);

/* Sets the base wind. */
void EftWeather_SetWind(f32 x, f32 y, f32 z);

/* Returns the base wind. */
void EftWeather_GetWind(Vec4 *out);

/* Same as EftWeather_SetCount. */
void EftWeather_SetCount2(s32 count);

/* Same as EftWeather_GetCount. */
s32 EftWeather_GetCount2(void);

/* Same as EftWeather_SetFlags. */
void EftWeather_SetFlags2(s32 flags);

/* Same as EftWeather_GetFlags. */
s32 EftWeather_GetFlags2(void);

/* Turns the particles on or off. */
void EftWeather_SetEnabled(s32 on);

/* Destroys and recreates layer 0 of the effect scene (all stage effects). */
void EftStage_Recreate(void);

/* Resets every effect task and frees the stage effect tasks. */
void EftStage_ResetAll(void);

/* Returns 1 when the stage effects are to be drawn. */
s32 EftStage_IsDrawOn(void);

/* Turns drawing of the stage effects on or off. */
void EftStage_SetDrawOn(s32 on);

/* Layer-0 task init: state from pool slot 2, one child task per stage effect kind, drawing on. */
void EftStage_Init(EftTask *task);

/* Layer-0 task term: frees the state and empties pool slot 2. */
void EftStage_Term(void);

/* Layer-0 task update: nothing. */
void EftStage_Update(void);

/* Destroys the child tasks of the layer. */
void EftStage_FreeKinds(void);

/* Creates the child list and one task for every kind the stage has data for; loads the sprite. */
void EftStage_CreateKinds(void);

/* Returns 1 when the loaded stage has the data a stage effect kind needs (-1: always). */
s32 EftStage_HasKind(s32 kind);

/* Nothing. */
void EftStage_Nop(void);

/* Brightness factor from the stage tint: 1 - alpha / 100, kept within 0.5..1. */
f32 EftStage_GetTintScale(void);

/* Loads the stage's single sprite texture (pack entry 0x14) when it exists. Declared with a result it never
   sets: the original does not turn the last call into a tail call. */
s32 EftStage_LoadSprite(void);

/* Refreshes the sprite texture. */
void EftStage_UpdateSprite(void);

/* Draws the sprite, 16 units wide, at a world position. */
void EftStage_DrawSprite(Vec4 *pos);

/* Surface task init: locates the surface file in the stage pack and, when a mesh uses the reflection, sets up
   the palette renderer. */
void EftSurf_Init(void);

/* Surface task term: turns the file's pointers back into offsets and frees the state. */
void EftSurf_Term(void);

/* Surface task update: scrolls the meshes (unless paused) and refreshes the textures. */
void EftSurf_Update(void);

/* Surface task draw. */
void EftSurf_Draw(void);

/* Surface task post-update: nothing. */
void EftSurf_PostUpdate(void);

/* Surface task reset: nothing. */
void EftSurf_Reset(void);

/* Turns the file offsets of a surface file into pointers. A file that is not version 4 is emptied. */
void EftSurf_Relocate(EftSurfFile *file);

/* Turns the pointers of a surface file back into offsets. (The texture pointers come out negated: file - ofs.) */
void EftSurf_Unrelocate(EftSurfFile *file);

/* Gets this frame's TEX0 of every texture of the file; allows the palettes to be built again. */
void EftSurf_UpdateTextures(EftSurfFile *file);

/* Advances the texture scroll of every mesh by its per-frame step. */
void EftSurf_Animate(EftSurfFile *file);

/* Projects the eight corners of a box. Returns 1 when one corner is on screen or the corners lie on several
   sides of it, 0 when the box is certainly outside the view. */
s32 EftSurf_IsBoxVisible(Vec4 *min, Vec4 *max);

/* Returns an entry of the reflection renderer's texture table. */
static inline EftTexEntry *EftSurfRt_GetTex(EftSurfRt *rt, s32 idx);

/* Draws every mesh of the surface file: scrolls and tints the vertices of each triangle, then sends it through
   the draw routine its flags select. */
void EftSurf_DrawMeshes(void);

#define EFT_F2RGBA(c) \
    ((u64)(s32)(c)->x | ((u64)(s32)(c)->y << 8) | ((u64)(s32)(c)->z << 16) | ((u64)(s32)(c)->w << 24))

/* Sends one textured, Gouraud-shaded, alpha-blended triangle: a REGLIST packet of PRIM, TEX0 and three
   RGBAQ / ST / XYZ2 groups. */
void EftSurf_PutTri(s32 *xyz0, s32 *xyz1, s32 *xyz2, Vec4 *st0, Vec4 *st1, Vec4 *st2, Vec4 *rgba0, Vec4 *rgba1,
                    Vec4 *rgba2, u64 tex0);

/* GS state for the surfaces, both contexts: blend mode, linear filtering, depth test (always when
   noDepthTest), no depth writes; context 2 draws into the other colour buffer. */
void EftSurf_BeginDraw(s32 blend, s32 noDepthTest);

/* Restores the GS state after the surfaces: normal blend, depth test and depth writes; texture clamping
   unless arg is set. */
void EftSurf_EndDraw(s32 arg);

/* Returns 1 when a projected vertex is behind the camera or outside the screen of the view being drawn
   (GS coordinates * 16: x within 272 of 2048, or the half of it of a split-screen view; y within 240). */
static inline s32 EftSurf_IsOffScreen(s32 *xyz);

/* Draws a triangle as it is, unless its three vertices are all off screen. */
void EftSurf_DrawTri(EftSurfVtx *tri, u64 tex0);

/* Clips a triangle against the five planes and draws the resulting polygon as a fan. */
void EftSurf_DrawTriClipped(EftSurfVtx *tri, u64 tex0);

/* Draws a triangle of the reflecting surface as it is, unless its three vertices are all off screen. */
void EftSurf_DrawReflectTri(EftSurfVtx *tri, u64 *tex, Vec4 *fog);

/* Clips a triangle of the reflecting surface against the five planes and draws the fan. */
void EftSurf_DrawReflectTriClipped(EftSurfVtx *tri, u64 *tex, Vec4 *fog);

/* GS vertex register with fog (XYZF2), and the triangle packet this file queues in the ordering table. */
typedef struct EftSurfXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftSurfXyzf;

typedef struct EftSurfRgbaq {
    u8 r, g, b, a;
    f32 q;
} EftSurfRgbaq;

typedef struct EftSurfSt {
    f32 s, t;
} EftSurfSt;

/* DMA tag + REGLIST GIF tag (12 registers): PRIM, TEX0, three (RGBAQ, ST, XYZF2), NOP. */
typedef struct EftSurfTriPkt {
    /* 0x00 */ u32 dmaTag; /* 0x20000007: NEXT, 7 quadwords */
    /* 0x04 */ struct EftSurfTriPkt *next;
    /* 0x08 */ u32 vif0;   /* 0x10000000 */
    /* 0x0C */ u32 vif1;   /* 0x50000007: DIRECT, 7 quadwords */
    /* 0x10 */ u64 gifTag; /* 0xC400000000008001: NLOOP 1, EOP, REGLIST, 12 registers */
    /* 0x18 */ u64 regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftSurfRgbaq rgbaq0;
    /* 0x38 */ EftSurfSt st0;
    /* 0x40 */ EftSurfXyzf xyz0;
    /* 0x48 */ EftSurfRgbaq rgbaq1;
    /* 0x50 */ EftSurfSt st1;
    /* 0x58 */ EftSurfXyzf xyz1;
    /* 0x60 */ EftSurfRgbaq rgbaq2;
    /* 0x68 */ EftSurfSt st2;
    /* 0x70 */ EftSurfXyzf xyz2;
    /* 0x78 */ u64 nop;
} EftSurfTriPkt; /* size 0x80 */

/* Queues one gouraud textured triangle in the ordering table at depth slot z (clamped to 0..0xFFF). Skipped
   when its three alphas are below 0.1. A negative layer means layer 0 without blending. */
static inline void EftSurf_QueueTri(EftScreenPos *v0, EftScreenPos *v1, EftScreenPos *v2, f32 *c0, f32 *c1, f32 *c2,
                                    Vec4 *uv0, Vec4 *uv1, Vec4 *uv2, s32 layer, s32 z, u64 tex0);

/* Clips a triangle against the five planes and queues the resulting fan in the ordering table, at the depth of
   the first vertex (mirrored when flipZ) less zBias. */
void EftSurf_DrawTriOtClipped(EftSurfVtx *tri, s32 layer, s32 unused, s32 flipZ, u64 tex0, s32 zBias);

/* Called once per frame before the views are drawn: builds the two palettes of the reflecting surface,
   alternating between two pairs of textures. */
void EftSurf_BuildPalettes(void) {
    EftSurfRt *rt;

    if (gEftSurf != NULL) {
        rt = &gEftSurf->rt;
        if (rt->flags & EFT_SURF_RT_ON) {
            if (!(rt->flags & EFT_SURF_RT_BUILT)) {
                rt->flip = (rt->flip + 1) & 1;
                EftSurf_RenderPalettes();
                rt->flags |= EFT_SURF_RT_BUILT;
            }
        }
    }
}

/* Once per update: light direction in the surface's frame, and the normal map animation advances by
   animSpeed / animCount of a frame. */
void EftSurf_StepAnim(void);

/* Lights the 256 palette entries of the current normal map frame: one palette from the light direction, one
   from the view (identity with a fixed tilt in split-screen), and gives them to the two result textures. */
void EftSurf_RenderPalettes(void);
