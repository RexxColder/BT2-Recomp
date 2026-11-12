#include "common.h"
#include "battle/eft_b.h"
#include "sys/gfx_ot.h"

/*
 * Effect code 0x132290..0x136760: see include/battle/eft_b.h for the four pieces and their layouts.
 *
 * Nothing here touches a fighter, a hit record or a battle flag: it is all drawing. What it reads from the
 * simulation: fighter speed, height, position, direction, node positions and "in water" through BtlCharApi_*,
 * the battle pause flag, BtlScene_IsTimeStopped and the stage's water height (0x140338).
 * The random numbers are all the C library rand(). Their NUMBER per frame depends on the camera: a view whose
 * camera is under water draws one rand() per frame plus five per bubble it spawns, and nothing in split-screen
 * (EftBubble_UpdateAmbient). rand() is shared with the rest of the game.
 *
 * Three functions are INCLUDE_ASM with the attempt in `#if 0` above them: EftPrim_DrawBillboard,
 * EftPrim_DrawTriangle, EftGeyser_DrawColumn.
 * With every attempt enabled the file's .lit4 (0x2FC368..0x2FC400) and .rodata (0x2EC620..0x2EC720) come out
 * identical to the original; as shipped, the C emits .lit4 0x2FC370..0x2FC3FC (EftBubble_EmitBody's ten constants
 * come first), the bone table at 0x2EC620 and the jump table at 0x2EC6C0.
 */

/* ---- local views of other modules ---- */

/* Battle block: only the flags (battle/battle.h). */
typedef struct EftBBattle {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags;
} EftBBattle;
#define EFTB_BATTLE_PAUSE 0x100

/* A camera view (battle/btl_cam.h: View / BtlCamView / BtlCam). */
typedef struct EftBView {
    /* 0x000 */ Mtx44 world2view;
    /* 0x040 */ Mtx44 world2view2;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 world2screen;
    /* 0x180 */ u8 unk180[0xA0];
    /* 0x220 */ Vec4 pos;
    /* 0x230 */ f32 aspect;
    /* 0x234 */ f32 screenDist;
    /* 0x238 */ u8 unk238[0x28];
    /* 0x260 */ Vec4 camPos;
    /* 0x270 */ u8 unk270[0x20];
} EftBView; /* size 0x290 */

typedef struct EftBCam {
    /* 0x000 */ u8 layouts[0x720];
    /* 0x720 */ EftBView views[2];
} EftBCam;

/* gCommonRes: only the stage model file (battle/battle_work.h BattleRes.stage). */
typedef struct EftBCommonRes {
    /* 0x00 */ u8 unk0[0x24];
    /* 0x24 */ u8 *stage;
} EftBCommonRes;

/* The stage manager: only its flag word. */
typedef struct EftBStage {
    /* 0x00 */ u8 unk0[8];
    /* 0x08 */ s32 flags;
} EftBStage;

/* gBtlCam seen from view i, for the one loop whose induction variable is i * 0x290 with the field offset kept
   in the load (EftBubble_UpdateAmbient). */
typedef struct EftBCamAt {
    /* 0x000 */ u8 layouts[0x720];
    /* 0x720 */ EftBView view;
} EftBCamAt;
#define EFTB_CAM_AT(i) ((EftBCamAt *)((u8 *)gBtlCam + (i) * sizeof(EftBView)))

extern EftBView *gBtlCamView;
extern EftBCam *gBtlCam;
extern EftBCommonRes *gCommonRes;
extern EftBStage *gBtlStage;

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);
extern f32 Mathf_SinFast(f32 angle);
extern f32 Mathf_CosFast(f32 angle);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Length(Vec4 *v);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *src);
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b); /* matrix product */
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);          /* matrix copy */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);          /* inverse of a rotation + translation matrix */
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotate about Z */
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotate about Y */
extern void Vu0Cur_Push(void);                            /* VU0 matrix stack: push */
extern void Vu0Cur_Pop(void);                            /* VU0 matrix stack: pop */
extern void Vu0Cur_LoadMtx(Mtx44 *m);                        /* VU0 current matrix = m */
extern s32 Vu0Cur_ProjectPoint(EftBIVec *out, Vec4 *pos);         /* project one point with the current view; returns a value */
extern s32 Vu0Cur_ProjectPoints(EftBIVec *out, Vec4 *pos, s32 count); /* project count points; 0 when clipped */
extern void ClipVtx_Set(void *out, Vec4 *pos, Vec4 *uv, Vec4 *color); /* fills one EftBVert */
extern void Vec4_Mul(Vec4 *dst, Vec4 *a, Vec4 *b);     /* per-component product */
extern void Vec4_ToInt(EftBIVec *dst, Vec4 *src);        /* float to fixed vector */
extern void Mtx_ProjectPoint(EftBIVec *out, Mtx44 *m, Vec4 *pos); /* project with a matrix */
extern void Vec3_ScaleAdd(Vec4 *dst, Vec4 *dir, Vec4 *base, f32 s); /* dst = base + dir * s */
extern f32 EftMath_WrapAngle(f32 angle);                        /* wraps an angle into -pi..pi */
extern void EftGfx_UpdateClipPlanes(void);
extern void EftGfx_DrawPolyFixedZ(void *verts, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u64 tex0, s32 z);
extern s32 EftStage_IsDrawOn(void);
extern f32 EftStage_GetTintScale(void);
extern void EftSteam_Stop(void *emitter);
extern void EftSteam_SetPaused(void *emitter, s32 on);
extern void EftSteam_SetPos(void *emitter, EftGeyser *work);
extern s32 EftWater_GetSurfaceY(f32 *outY);                        /* water surface height; 0 when the stage has none */
extern void EftSmoke_Stop(void *emitter);
extern void EftSmoke_SetPos(void *emitter, EftGeyser *work);
extern void EftGeyser_StartSmoke(EftBTask *task);
extern void EftGeyser_StartSteam(EftBTask *task);
extern void Tex_Upload(EftBTexImg *img, s32 tbp, s32 cbp);
extern void EftMesh_Init(void *model, void *data);
extern void EftMesh_SetTex(void *model, EftBTexSet *tex);
extern void EftMesh_SetMtx(void *model, Mtx44 *m);
extern void EftMesh_SetClip(void *model, s32 on);
extern void EftMesh_SetRepeat(void *model, s32 on);
extern void EftMesh_SetUvOfs(void *model, f32 x, f32 y);
extern void EftMesh_SetUvScale(void *model, f32 size);
extern void EftMesh_DrawNow(void *model, s32 on);
extern void BtlTask_SetDead(void *task);                      /* marks a task as dying */
extern u64 EftVram_AddTex(EftBTex *tex, s32 a, s32 b);       /* TEX0 of a texture with two mode bits */
extern void EftTexSet_Load32(EftBTexSet *set, void *pack);     /* builds a texture set from a pack */

extern EftBBattle *Battle_GetWork(void);
extern s32 Battle_IsSplitScreen(void);
extern s32 BtlStage_IsReady(void);
extern s32 BtlStage_GetFxResA(void);
extern EftGeyserRec *BtlStage_GetFxResA2(void);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 *BtlScene_GetStageData(void);
extern s32 *BtlScene_GetPackEntry(s32 *base, s32 idx);
extern s32 BtlScene_GetPackEntrySize(s32 *base, s32 idx);
extern s32 BtlScene_IsSecondView(void);
extern s32 BtlScene_IsTimeStopped(void);
extern void *BtlTask_CreateChildList(void *task, s32 count, s32 workSize);
extern void *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern u64 *Dma_BeginDirect(void);
extern void Dma_EndDirect(u64 *end);

extern f32 BtlCharApi_GetHeight(s32 objId);
extern void BtlCharApi_GetPos(s32 objId, Vec4 *out);
extern void BtlCharApi_GetDir(s32 objId, Vec4 *out);
extern f32 BtlCharApi_GetSpeed(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern s32 BtlCharApi_IsInWater(s32 objId);

extern Vec4 gEftBubbleZeroVel;
extern void *gEftGeyserClass[6];

#define EFTB_RAND01() ((f32)rand() / 2147483647.0f)

/* Reads an int from a byte pointer that need not be aligned, and steps over it. */
#define EFTB_READ_INT(v, p) (__builtin_memcpy((u8 *)&(v), (p), 4), (p) += 4)

void EftBubble_EmitBody(s32 objId, s32 chance, s32 view);
void EftBubble_EmitBurst(s32 objId, s32 count);
void EftBubble_EmitCamera(s32 view);
void EftBubble_UpdateChrs(void);
void EftBubble_UpdateTrail(EftBubbleChr *chr);
void EftBubble_UpdateBurst(EftBubbleChr *chr);
void EftBubble_UpdateAmbient(void);
EftBubble *EftBubble_AllocSlot(void);
void EftBubble_UpdateList(EftBubble **head, EftBubble **tail);
s32 EftBubble_Step(EftBubble *b);
void EftBubble_DrawList(EftBubble *b);
s32 EftBubble_IsOnScreen(EftBIVec v);
void EftBubble_RandDir(EftBVec v);
void EftBubble_DrawOne(EftBVec pos, EftBMtx m, f32 size, f32 rot, u8 r, u8 g, u8 b, u8 a, EftBTex *tex, u8 layer);
void EftBubble_SetTexMode(s32 a, s32 b);
void EftStageScroll_PlaceTextures(s32 tcc, s32 tfx);
void EftStageScroll_Load(void);
void EftGeyser_Update(EftBTask *task);
void EftGeyser_Restart(EftBTask *task, EftGeyser *w);
void EftGeyser_DrawColumn(EftBTask *task);

/* GS vertex register with fog (XYZF2), and the packets this file queues in the ordering table. */
typedef struct EftBXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftBXyzf;

typedef struct EftBRgbaq {
    u8 r, g, b, a;
    f32 q;
} EftBRgbaq;

typedef struct EftBSt {
    f32 s, t;
} EftBSt;

/* DMA tag + REGLIST GIF tag (12 registers): PRIM, TEX0, RGBAQ, four (ST, XYZF2), NOP: one flat textured strip. */
typedef struct EftBQuadPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000007: NEXT, 7 quadwords */
    /* 0x04 */ struct EftBQuadPkt *next;
    /* 0x08 */ u32 vif0;         /* 0x10000000 */
    /* 0x0C */ u32 vif1;         /* 0x50000007: DIRECT, 7 quadwords */
    /* 0x10 */ u64 gifTag;       /* 0xC400000000008001: NLOOP 1, EOP, REGLIST, 12 registers */
    /* 0x18 */ u64 regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftBRgbaq rgbaq;
    /* 0x38 */ EftBSt st0;
    /* 0x40 */ EftBXyzf xyz0;
    /* 0x48 */ EftBSt st1;
    /* 0x50 */ EftBXyzf xyz1;
    /* 0x58 */ EftBSt st2;
    /* 0x60 */ EftBXyzf xyz2;
    /* 0x68 */ EftBSt st3;
    /* 0x70 */ EftBXyzf xyz3;
    /* 0x78 */ u64 nop;
} EftBQuadPkt; /* size 0x80 */

/* DMA tag + REGLIST GIF tag (12 registers): PRIM, TEX0, three (RGBAQ, ST, XYZF2), NOP: one gouraud triangle. */
typedef struct EftBTriPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000007 */
    /* 0x04 */ struct EftBTriPkt *next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;         /* 0x50000007 */
    /* 0x10 */ u64 gifTag;       /* 0xC400000000008001 */
    /* 0x18 */ u64 regs;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftBRgbaq rgbaq0;
    /* 0x38 */ EftBSt st0;
    /* 0x40 */ EftBXyzf xyz0;
    /* 0x48 */ EftBRgbaq rgbaq1;
    /* 0x50 */ EftBSt st1;
    /* 0x58 */ EftBXyzf xyz1;
    /* 0x60 */ EftBRgbaq rgbaq2;
    /* 0x68 */ EftBSt st2;
    /* 0x70 */ EftBXyzf xyz2;
    /* 0x78 */ u64 nop;
} EftBTriPkt; /* size 0x80 */

/* DMA tag + A+D GIF tag: CLAMP_1 = 0 and CLAMP_2 = 0 (repeat), queued in front of a strip that scrolls its texture. */
typedef struct EftBClampPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000003 */
    /* 0x04 */ struct EftBClampPkt *next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;         /* 0x50000003 */
    /* 0x10 */ u64 gifTag;       /* 0x1000000000008002: NLOOP 2, EOP, PACKED, 1 register */
    /* 0x18 */ u64 regs;         /* 0xE: A+D */
    /* 0x20 */ u64 clamp1;
    /* 0x28 */ u64 clamp1Reg;    /* 8 */
    /* 0x30 */ u64 clamp2;
    /* 0x38 */ u64 clamp2Reg;    /* 9 */
} EftBClampPkt; /* size 0x40 */

/* DMA tag + REGLIST GIF tag (14 registers): PRIM, TEX0, four (RGBAQ, ST, XYZF2): one gouraud textured strip. */
typedef struct EftBStripPkt {
    /* 0x00 */ u32 dmaTag;       /* 0x20000008 */
    /* 0x04 */ struct EftBStripPkt *next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;         /* 0x50000008 */
    /* 0x10 */ u64 gifTag;       /* 0xE400000000008001 */
    /* 0x18 */ u64 regs;         /* 0x42142142142160 */
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftBRgbaq rgbaq0;
    /* 0x38 */ EftBSt st0;
    /* 0x40 */ EftBXyzf xyz0;
    /* 0x48 */ EftBRgbaq rgbaq1;
    /* 0x50 */ EftBSt st1;
    /* 0x58 */ EftBXyzf xyz1;
    /* 0x60 */ EftBRgbaq rgbaq2;
    /* 0x68 */ EftBSt st2;
    /* 0x70 */ EftBXyzf xyz2;
    /* 0x78 */ EftBRgbaq rgbaq3;
    /* 0x80 */ EftBSt st3;
    /* 0x88 */ EftBXyzf xyz3;
} EftBStripPkt; /* size 0x90 */

/* Queues a screen-aligned textured quad centred on the projection of `pos`: w x h are half sizes in world units
   (scaled by the perspective of pos), rot turns it about the view axis, zScale scales its depth slot. Dropped when
   smaller than 2 pixels or when any corner leaves the GS drawing area. Sets pos->w to 1. */
void EftPrim_DrawBillboard(Vec4 *pos, Vec4 *color, s32 layer, s32 noDepth, u64 tex0, f32 w, f32 h, f32 u0, f32 v0,
                           f32 u1, f32 v1, f32 rot, f32 zScale);

/* One vertex as ClipVtx_Set builds it for EftGfx_DrawPolyFixedZ: position, texture coordinates and colour. */
typedef struct EftBVert {
    /* 0x00 */ Vec4 pos;
    /* 0x10 */ Vec4 uv;
    /* 0x20 */ Vec4 color;
} EftBVert; /* size 0x30 */

/* Draws a w x h quad (half sizes) at `pos`, facing the camera and rotated by `rot` about the view axis, as two
   triangles through the clipping triangle routine 0x131478. Its depth slot is that of `pos`. */
void EftPrim_DrawQuadDepth(Vec4 *pos, Vec4 *color, s32 arg2, s32 arg3, u64 tex0, f32 w, f32 h, f32 u0, f32 v0, f32 u1,
                           f32 v1, f32 rot);

/* Same as EftPrim_DrawQuadDepth with the depth slot multiplied by zScale.
   The float parameters are declared BEFORE arg2 / arg3 / tex0 (integer and float arguments use separate
   registers, so callers are not affected): only with that order are the incoming float registers copied before
   the integer ones, which decides whether u0 or v1 gets $f29. The callers' local prototypes list the integers
   first; both forms pass every argument in the same register. */
void EftPrim_DrawQuadDepthScaled(Vec4 *pos, Vec4 *color, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 rot,
                                 s32 arg2, s32 arg3, u64 tex0, f32 zScale);

/* Queues one gouraud textured triangle from projected vertices, float colours (0..255) and (s, t, q) texture
   coordinates. Skipped when all three alphas are 0.01 or less. A negative layer means layer 0 without blending;
   layers 2 and 3 are layers 0 and 1 drawn with GS context 2. */
void EftPrim_DrawTriangle(EftBIVec *v0, EftBIVec *v1, EftBIVec *v2, Vec4 *c0, Vec4 *c1, Vec4 *c2, Vec4 *uv0, Vec4 *uv1,
                          Vec4 *uv2, s32 unk1, s32 unk2, s32 layer, s32 z, u64 tex0);

/* 1 when a projected point cannot be drawn: behind the camera or outside the GS drawing area. */
s32 EftPrim_IsOffScreen(s32 x, s32 y, s32 z);

/* Starts the burst of bubbles of a fighter that just went under water: 5 per unit of speed, 40 to 60. */
s32 EftBubble_StartBurst(s32 objId);

/* Per blast record hook of BtlScene_UpdateRecords: does nothing. */
void EftBubble_OnBlastRecord(void *rec);

/* Task init: allocates the state and the pool, loads the textures; kills the task when the stage has fewer than 6. */
void EftBubble_Init(EftBTask *task);

/* Task term: frees the pool, the per-fighter state and the state. */
void EftBubble_Term(void);

/* Task update: emits from the fighters and the cameras, then moves every bubble. */
void EftBubble_Update(void);

/* Task post-update: refreshes the TEX0 of textures 5..8. */
void EftBubble_PostUpdate(void);

/* Task draw: takes the rotation of the current view and draws the list. */
void EftBubble_Draw(void);

/* A pair of model nodes: a segment from the first to the second, or one point when the second is -1. */
typedef struct EftBubbleBone {
    /* 0x0 */ s32 from;
    /* 0x4 */ s32 to;
} EftBubbleBone;

/* Emits small bubbles along the body of a fighter: each point of 20 bone segments has a 1 in `chance` chance.
   The table is an array of pairs (structs): as a flat `s32 bones[40]` indexed with i * 2 the compiler walks a
   pointer through it, which the original does not (it recomputes i * 8 for each access). */
void EftBubble_EmitBody(s32 objId, s32 chance, s32 view);

/* Emits `count` big bubbles around a fighter (the burst after it dives in). */
void EftBubble_EmitBurst(s32 objId, s32 count);

/* Emits one bubble in front of a view's camera, at a random place of the screen. */
void EftBubble_EmitCamera(s32 view);

/* Runs the two per-fighter emitters, unless the battle is paused. */
void EftBubble_UpdateChrs(void);

/* Continuous emission from the body (its flag is never set). */
void EftBubble_UpdateTrail(EftBubbleChr *chr);

/* One frame of a burst: emits `burst` bubbles and takes 8 off, until none are left. */
void EftBubble_UpdateBurst(EftBubbleChr *chr);

/* Bubbles in front of each camera that is under water, and from the body of a fighter in water. */
void EftBubble_UpdateAmbient(void);

/* Returns a cleared free bubble, or NULL when all 100 are in use. */
EftBubble *EftBubble_AllocSlot(void);

/* Adds a bubble at the tail of the list. life > 0 fades it out over that many seconds. */
void EftBubble_Add(EftBVec pos, EftBVec vel, f32 drag, f32 size, f32 alpha, f32 rot, f32 rise, f32 riseGrow, f32 phase,
                   f32 amp, u8 r, u8 g, u8 b, s32 objId, s32 view, u8 tex, f32 phaseStep, f32 life, u8 layer);

/* Moves every bubble and unlinks the ones that ended. Does nothing while the battle is paused. */
void EftBubble_UpdateList(EftBubble **head, EftBubble **tail);

/* One frame of a bubble. Returns 1 when it faded out, reached the surface, or its camera left the water. */
s32 EftBubble_Step(EftBubble *b);

/* Draws the bubbles that belong to the view being drawn. */
void EftBubble_DrawList(EftBubble *b);

/* 1 when a projected corner is in front of the camera and inside the visible part of the GS area. */
s32 EftBubble_IsOnScreen(EftBIVec v);

/* Builds a random direction. The vector is taken by value, so the caller never sees the result. */
void EftBubble_RandDir(EftBVec v);

/* Draws one bubble: a camera-facing quad of `size`, rotated by `rot` degrees, as one textured strip. Nothing is
   drawn unless all four corners are on screen. */
void EftBubble_DrawOne(EftBVec pos, EftBMtx m, f32 size, f32 rot, u8 r, u8 g, u8 b, u8 a, EftBTex *tex, u8 layer);

/* Refreshes the TEX0 of textures 5..8 with the given mode bits, when any bubble exists. */
void EftBubble_SetTexMode(s32 a, s32 b);

/* Task init: allocates the state and loads the sheet. */
void EftStageScroll_Init(void);

/* Task term. */
void EftStageScroll_Term(void);

/* Task update: advances the scroll offset and wraps it into -size..size. Stops while paused or loading. */
void EftStageScroll_Update(void);

/* Task reset: reloads the sheet (a new stage file after a stage change). */
void EftStageScroll_Reset(void);

/* Task draw: nothing (the sheet is drawn by the stage). */
void EftStageScroll_DrawStub(void);

/* Draws the sheet: called by the stage draw, once per view. */
void EftStageScroll_Draw(void);

/* Uploads the sheet's textures one after the other from VRAM block 0x2A20 (palettes from 0x2A00) and rewrites
   the TBP0, TCC, TFX and CBP fields of each TEX0 to match. */
void EftStageScroll_PlaceTextures(s32 tcc, s32 tfx);

/* Reads the sheet from the stage file: size, speed, direction (random when negative), textures and model. */
void EftStageScroll_Load(void);

/* Creates one column task from its parameters. */
void *EftGeyser_Create(EftGeyserParam *param) {
    if (gEftGeyserMgr == NULL) {
        return NULL;
    }
    return BtlTaskList_AddTail(gEftGeyserMgr->list, gEftGeyserClass, param);
}

/* The work of a live column task, NULL for anything else. */
EftGeyser *EftGeyser_GetWork(EftBTask *task);

/* Kills a live column task. */
void EftGeyser_Kill(EftBTask *task);

/* Manager init: loads the textures and creates a column for every record of the stage. */
void EftGeyser_MgrInit(EftBTask *task);

/* Manager term. */
void EftGeyser_MgrTerm(void);

/* Manager update: refreshes the TEX0 of texture 1 while any column exists. */
void EftGeyser_MgrUpdate(void);

/* Column init: keeps the parameters twice, picks the first delay and creates the two emitters. */
void EftGeyser_Init(EftBTask *task, EftGeyserParam *param);

/* Column term: frees the two emitters. */
void EftGeyser_Term(EftBTask *task);

/* Column reset: nothing. */
void EftGeyser_ResetStub(void);

/* Column update: wait, rise and fade in, hold, sink and fade out, wait again; scrolls the texture throughout. */
void EftGeyser_Update(EftBTask *task);

/* Column draw: with the stage visible, draws the column under the world-to-screen matrix of the view. */
void EftGeyser_Draw(EftBTask *task);

/* Starts a new eruption: current parameters = initial ones, alpha 0, emitters repositioned. */
void EftGeyser_Restart(EftBTask *task, EftGeyser *w);

/* Draws the column as a ribbon of three camera-facing segments between four points spaced a quarter of the
   height apart, upwards from the base. The texture runs once along the ribbon and scrolls by texV; the colour is
   the current colour scaled by 0x137F60(), and the top edge has alpha 0. */
#if 0
/* NON-MATCHING: not matched (register allocation throughout; 631 instructions). Written from the
   disassembly: same calls in the same order, same packets. */
void EftGeyser_DrawColumn(EftBTask *task);
#else
RODATA_ALIGN16();


#endif
