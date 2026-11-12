#include "common.h"
#include "battle/eft_e.h"
#include "sys/gfx_ot.h"

/*
 * Effect code 0x13F430..0x147050. See include/battle/eft_e.h and eft_f.h for the modules and their layouts.
 * As linked: the former head of this file (0x13EA00..0x13F430, the transition task) moved to the end of
 * eft_d_b.c, and the former eft_f.c (0x142CA0..0x147050) is appended below as the second part:
 * EftWaterRing_Update only matches with EftWater_GetSurfaceY defined earlier in its file.
 *
 *   0x13F430..0x140338  EftSteam_*: particle emitters of the stage (layer 0, sub-task 5).
 *   0x140338..0x142CA0  EftWater_*: water splashes, technique spray trails and fighter wakes (layer 0, sub-task
 *                       7).
 *   0x142CA0..0x147050  the particle pools they fill (second part).
 *
 * Other modules are declared locally with this file's own view types (the integrator was linking while this was
 * written). Names of the task system (BtlTask*), EftCam_*, EftStage_*, EftHit_*, EftUtil_*, EftRec_*, BtlStage_*
 * and the EftWater* pool functions are the ones recorded in config/symbols by their owners.
 *
 * Random numbers: everything here draws from the C library rand() (EFT_RANDF) except EftSteam_Emit, which uses
 * the VU0 generator through Rand_FloatRange. No draw reaches a fighter, a hit record or a battle object.
 */

extern void *Heap_Alloc(s32 size, u32 align, s32 fromTail, s32 heap);
extern void Heap_Free(void *ptr);
extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sinf(f32 x);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern void *BtlTask_CreateChildList(void *task, s32 capacity, s32 workSize);
extern void *BtlTaskList_AddTail(void *list, BtlTaskClass *cls, void *arg);
extern void BtlTask_SetDead(void *task);
extern void EftCam_Start(s32 *arg);
extern void EftCam_SetHold(s32 arg);
extern void EftCam_Stop(void);
extern void Gfx_AddDefaultEnv(void);
extern void EftBurst_DrawModel(void *model, s32 arg);
extern void EftBurst_SetTexture(void *tex, s32 x, s32 y);
extern void EftBurst_RelocateModel(void *model);
extern void Res_RelocateOffsets(void *dst, void *base, void *table);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);

extern s32 BtlStage_GetFxResC(void);
extern s32 BtlStage_GetFxResA(void);
extern EftStageMarker *BtlStage_GetFxResC2(void);
extern void EftTexSet_Load8(EftSteamTex *tex, s32 *data);
extern u64 EftVram_AddTex(u64 *tex0, s32 a1, s32 a2);
extern s32 EftStage_IsDrawOn(void);
extern void Vu0Cur_Push(void);
extern void Vu0Cur_LoadMtx(Mtx44 *mtx);
extern void Vu0Cur_Pop(void);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Length(Vec4 *v);
extern f32 Rand_FloatRange(f32 a, f32 b);

/* The stage state (gp 0x2FEBE0); only the flag word. */
typedef struct EftStageState {
    s32 unk0[2];
    s32 flags; /* bit 0: not drawable (BtlStage_IsReady tests it too) */
} EftStageState;
extern EftStageState *gBtlStage;

/* The view being drawn (btl_cam.h); only the matrices and position used here. */
typedef struct EftView {
    /* 0x000 */ Mtx44 world2view;
    /* 0x040 */ Mtx44 world2view2;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 world2screen;
    /* 0x180 */ u8 unk180[0xA0];
    /* 0x220 */ Vec4 pos;
} EftView;
extern EftView *gBtlCamView;

extern f32 sqrtf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern s32 BtlStage_GetWaterLevel(f32 *y);
extern s32 BtlStage_GetId(void);
extern s32 Battle_IsSplitScreen(void);
extern s32 BtlStage_IsReady(void);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern f32 BtlCharApi_GetGroundY(s32 objId);
extern void BtlCharApi_GetPos(s32 objId, Vec4 *out);
extern void BtlCharApi_GetDir(s32 objId, Vec4 *out);
extern f32 BtlCharApi_GetSpeed(s32 objId);
extern s32 BtlCharApi_IsInTechnique(s32 objId);
extern void BtlCharApi_PlaySoundAt(Vec4 *pos, s32 kind, s32 id, f32 near, f32 far);
extern f32 EftHit_GetRadiusA(EftWaterBlast *rec);
extern void EftUtil_ClipSegToWater(EftEVec *out, Vec4 *a, Vec4 *b);
extern s32 EftRec_GetDefClass(EftWaterBlast *rec);
extern void EftTexSet_Load32(u8 *tex, s32 *data);
extern void EftWater_UpdateTextures(s32 a0, s32 a1);
/* The pool functions below are defined in the second part of this file (formerly eft_f.c) with that part's own
 * types; this part calls them through aliased declarations with its view types (same symbol, same code). */
extern void EftWaterSplash_UpdateList_e(EftWaterSplash **head, EftWaterSplash **tail) __asm__("EftWaterSplash_UpdateList");
#define EftWaterSplash_UpdateList EftWaterSplash_UpdateList_e
extern void EftWaterSplash_DrawList_e(void *head) __asm__("EftWaterSplash_DrawList");
#define EftWaterSplash_DrawList EftWaterSplash_DrawList_e
extern void EftWaterTrail_Spawn_e(void **head, void **tail, s32 objId, EftWaterBlast *rec) __asm__("EftWaterTrail_Spawn");
#define EftWaterTrail_Spawn EftWaterTrail_Spawn_e
extern void EftWaterTrail_UpdateList_e(void **head, void **tail) __asm__("EftWaterTrail_UpdateList");
#define EftWaterTrail_UpdateList EftWaterTrail_UpdateList_e
extern void EftWaterTrail_DrawList_e(void *head) __asm__("EftWaterTrail_DrawList");
#define EftWaterTrail_DrawList EftWaterTrail_DrawList_e
extern void EftWaterDrop_UpdateList_e(void **head, void **tail) __asm__("EftWaterDrop_UpdateList");
#define EftWaterDrop_UpdateList EftWaterDrop_UpdateList_e
extern void EftWaterDrop_DrawList_e(void *head, EftEVec origin) __asm__("EftWaterDrop_DrawList");
#define EftWaterDrop_DrawList EftWaterDrop_DrawList_e
extern void EftWaterRing_UpdateList_e(void **head, void **tail) __asm__("EftWaterRing_UpdateList");
#define EftWaterRing_UpdateList EftWaterRing_UpdateList_e
extern void EftWaterRing_DrawList_e(void *head) __asm__("EftWaterRing_DrawList");
#define EftWaterRing_DrawList EftWaterRing_DrawList_e
extern void EftWaterSpray_UpdateList_e(void **head, void **tail) __asm__("EftWaterSpray_UpdateList");
#define EftWaterSpray_UpdateList EftWaterSpray_UpdateList_e
extern void EftWaterSpray_DrawList_e(void *head, EftEVec origin) __asm__("EftWaterSpray_DrawList");
#define EftWaterSpray_DrawList EftWaterSpray_DrawList_e
extern void EftWaterMist_UpdateList_e(void **head, void **tail) __asm__("EftWaterMist_UpdateList");
#define EftWaterMist_UpdateList EftWaterMist_UpdateList_e
extern void EftWaterMist_DrawList_e(void *head) __asm__("EftWaterMist_DrawList");
#define EftWaterMist_DrawList EftWaterMist_DrawList_e

/* Billboard: yaw / pitch / speed of its flight, rot, size and its growth, gravity, life, start delay. */
extern void EftWaterDrop_Spawn_e(void **head, void **tail, EftEVec pos, f32 yaw, f32 pitch, f32 speed, f32 rot, f32 rotVel,
                          f32 size, f32 sizeVel, f32 sizeDamp, f32 gravity, f32 life, f32 delay, u8 r, u8 g, u8 b,
                          u8 tex, u8 layer, s32 flags) __asm__("EftWaterDrop_Spawn");
#define EftWaterDrop_Spawn EftWaterDrop_Spawn_e
/* Ring lying on the surface. */
extern void EftWaterRing_Spawn_e(void **head, void **tail, EftEVec pos, f32 rot, f32 size, f32 sizeVel, f32 sizeDamp,
                          f32 alphaMax, f32 time, f32 delay, u8 r, u8 g, u8 b, u8 tex, u8 layer, s32 flags) __asm__("EftWaterRing_Spawn");
#define EftWaterRing_Spawn EftWaterRing_Spawn_e
/* Streak thrown out along a direction. */
extern void EftWaterSpray_Spawn_e(void **head, void **tail, EftEVec pos, f32 dist, f32 height, f32 yaw, f32 pitch, f32 roll,
                          f32 tilt, f32 tiltEnd, f32 speed, f32 size, f32 sizeVel, f32 sizeDamp, f32 gravity,
                          f32 nearScale, f32 widthScale, f32 life, f32 delay, u8 r, u8 g, u8 b, u8 tex, u8 layer,
                          s32 flags) __asm__("EftWaterSpray_Spawn");
#define EftWaterSpray_Spawn EftWaterSpray_Spawn_e
/* Streak that orbits. */
extern void EftWaterMist_Spawn_e(void **head, void **tail, EftEVec pos, f32 radius, f32 height, f32 yaw, f32 yawVel,
                          f32 yawDamp, f32 pitch, f32 roll, f32 tilt, f32 tiltEnd, f32 speed, f32 size, f32 sizeVel,
                          f32 sizeDamp, f32 gravity, f32 nearScale, f32 widthScale, f32 life, f32 delay, u8 r, u8 g,
                          u8 b, u8 tex, u8 layer) __asm__("EftWaterMist_Spawn");
#define EftWaterMist_Spawn EftWaterMist_Spawn_e

#define EFT_RANDF() ((f32)rand() / 2147483647.0f)
#define EFT_UNIT(objId) (BtlCharApi_GetHeight(objId) * 0.05f)
#define EFT_SCALE(objId, scale) (BtlCharApi_GetHeight(objId) * 0.05f * (scale))
#define EFT_PAUSED() (Battle_GetWork()->flags & 0x100)

/* The battle work (battle.h); only the flag word. */
typedef struct EftBattleWork {
    u8 unk0[0x19F0];
    u64 flags; /* 0x100: pause */
} EftBattleWork;
extern EftBattleWork *Battle_GetWork(void);

extern EftEVec D_002C3630; /* (0, 0, 0, 1) */

extern EftTransPart *EftBurst_AllocPtcl(void);
extern void EftBurst_InitSpark(EftTransPart *part, s32 idx);
extern void EftBurst_InitStreak(EftTransPart *part);
extern void EftBurst_InitFlash(EftTransPart *part);
extern void EftBurst_InitRing(EftTransPart *part);
extern void EftBurst_InitGlow(EftTransPart *part);
extern void EftBurst_InitDebris(EftTransPart *part);
extern s32 Snd_PlaySeEx(u32 mask, s32 id, s32 volume, s32 pan, s32 pitch);

extern f32 EftStage_GetTintScale(void);
extern void EftMath_MtxFromDir(Mtx44 *out, Vec4 *dir, f32 angle);
extern void Mtx_MulVec4(Vec4 *out, Mtx44 *mtx, Vec4 *v);

/* A projected point as Vu0Cur_ProjectPoints writes it: GS x, y in 12.4 fixed point, z, and a fourth word. */
typedef struct EftSteamScr {
    /* 0x00 */ s32 x;
    /* 0x04 */ s32 y;
    /* 0x08 */ s32 z;
    /* 0x0C */ s32 unkC;
} EftSteamScr; /* size 0x10 */
extern void Vu0Cur_ProjectPoints(EftSteamScr *out, Vec4 *in, s32 count);

/* GS XYZF2 register value. */
typedef struct EftSteamXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftSteamXyzf;

/* The packet of one particle quad: REGLIST of PRIM, TEX0_1, RGBAQ and four (ST, XYZF2). */
typedef struct EftSteamPkt {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 gif0;
    /* 0x18 */ u64 gif1;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u8 rgba[4];
    /* 0x34 */ f32 q;
    /* 0x38 */ struct {
        /* 0x00 */ f32 s;
        /* 0x04 */ f32 t;
        /* 0x08 */ EftSteamXyzf xyz;
    } v[4];
    /* 0x78 */ u64 pad;
} EftSteamPkt; /* size 0x80 */


typedef struct EftCommonRes {
    u8 unk0[0x34];
    s32 *transition;
} EftCommonRes;
extern EftCommonRes *gCommonRes;

/* Creates an emitter from a 0x60-byte description; NULL when the stage has no emitter manager. */
void *EftSteam_Create(EftSteamArg *arg);

/* Lets an emitter die: no new particles, and the task ends when the last one is gone. */
void EftSteam_Stop(EftSteamTask *task);

/* Pauses or resumes the creation of particles. */
void EftSteam_SetPaused(EftSteamTask *task, s32 paused);

/* The work of an emitter task, NULL when the task is not a live emitter. */
EftSteamWork *EftSteam_GetWork(EftSteamTask *task);

/* Moves an emitter. */
void EftSteam_SetPos(EftSteamTask *task, Vec4 *pos);

/* Emitter manager init (layer 0, sub-task 5): the list, the texture, and one emitter per stage marker. */
void EftSteamMgr_Init(void *task);

/* Emitter manager term. */
void EftSteamMgr_Term(void);

/* Emitter manager update: renews the TEX0 of the texture while any emitter exists. */
void EftSteamMgr_Update(void);

/* Emitter init: copies the description into the work. */
void EftSteam_Init(EftSteamTask *task, EftSteamArg *arg);

/* Emitter term: nothing. */
void EftSteam_Term(void);

/* Emitter reset: nothing. */
void EftSteam_Reset(void);

/* Emitter update: one new particle per frame after the first, then moves them; ends when stopped and empty. */
void EftSteam_Update(EftSteamTask *task);

/* Emitter draw. */
void EftSteam_Draw(EftSteamTask *task);

/* First free particle of an emitter. */
EftSteamPart *EftSteam_FindFreePart(EftSteamPart *part);

/* Creates one particle: start, direction, speed, size and life are the emitter values plus a random spread. */
void EftSteam_Emit(EftSteamWork *work);

/* Moves the particles of an emitter (not while time is stopped) and frees the ones whose life ran out. */
void EftSteam_MoveParts(EftSteamWork *work) {
    s32 i;
    EftSteamPart *part = work->part;

    if (!BtlScene_IsTimeStopped()) {
        for (i = 0; i < EFT_STEAM_PART_COUNT; i++, part++) {
            if (part->life != 0) {
                Vec3_Add((Vec4 *)&part->pos, (Vec4 *)&part->pos, (Vec4 *)&part->vel);
                part->vel.y += part->accel;
                part->life--;
                if (part->life < 0) {
                    part->life = 0;
                    work->count--;
                }
            }
        }
    }
}

/* Draws the particles of an emitter. */
void EftSteam_DrawParts(EftSteamWork *work, u64 tex0) {
    s32 i;
    EftSteamPart *part = work->part;

    for (i = 0; i < EFT_STEAM_PART_COUNT; i++, part++) {
        if (part->life != 0) {
            EftSteam_DrawQuad(&part->color, &part->pos, 32.0f, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1, tex0, part->size,
                             part->angle);
        }
    }
}

/* Links a packet into the chain of a depth slot (clamped to 0..0xFFF); layers 2 and 3 fold onto 0 and 1. */
static inline void EftSteam_OtAdd(OtPrim *p, s32 z, s32 layer);

/* 1 when a projected point is behind the camera or outside the GS coordinate range. */
static inline s32 EftSteam_IsClipped(s32 x, s32 y, s32 z);

/* Queues one camera-facing textured quad (a 4-vertex strip) in the ordering table: w x h scaled by size / 16
   around pos, rolled by angle, colour scaled by the stage tint. Dropped when any corner is off the GS range. */
void EftSteam_DrawQuad(EftEVec *color, EftEVec *pos, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, s32 prio, u64 tex0,
                      f32 size, f32 angle);

/* The stage's water level; always reports success. */
s32 EftWater_GetSurfaceY(f32 *y);

/* Starts (off == 0) or stops (off == 1) the wake behind a fighter. Does nothing in split-screen. */
s32 EftWater_SetWake(s32 objId, u8 off);

/* Spray along a technique's hit record that travels just above the water. Does nothing in split-screen. */
s32 EftWater_AddBlastTrail(s32 objId, EftWaterBlast *rec);

/* A splash at a point of the surface, sized by sqrt(speed) * 0.33. kind EFT_WATER_SPLASH_CHAR: a fighter entering
   or leaving the water (also scaled by height * 0.05), _BLAST: a ki blast (* 0.8, fewer particles), _TECH: a
   technique (height * 0.05 * 1.2). Returns 0 and does nothing in split-screen or without the water task.
   The square root is assigned to the parameter itself (`speed`, which is why it lives in $f12, the register the
   parameter arrived in) and the scaled value to a second variable. */
s32 EftWater_AddSplashFor(s32 objId, EftEVec pos, u8 kind, f32 speed);

/* A full-size splash at a point (called by the stage code, 0x241DB4). Does nothing in split-screen. */
s32 EftWater_AddSplashAt(EftEVec pos, f32 scale);

/* A burst around a fighter standing in the water: count swirls spread evenly around a random angle, a ring and
   two pairs of billboards, all sized by the fighter's height and delayed by delay frames. Does nothing in
   split-screen or when the fighter's ground point is above the water. No caller. */
s32 EftWater_AddBurst(s32 objId, s32 count, f32 delay);

/* Called by BtlScene_UpdateRecords for every hit record of the frame: the splash where a record crosses the
   water surface, and the spray trail of a technique that skims it. Writes EFT task flag 0x400 only. */
void EftWater_UpdateBlast(EftWaterBlast *rec);

/* Water task init (layer 0, sub-task 7): allocates the state and the particle pools, loads the textures. The task
   ends at once on a stage whose pack has no entry 0x12. */
void EftWater_Init(void *task);

/* Water task term: frees the pools and the state. */
void EftWater_Term(void);

/* Water task update: the wakes, then every particle list. */
void EftWater_Update(void);

/* Water task post-update: EftWater_UpdateTextures(1, 0). */
void EftWater_PostUpdate(void);

/* Water task reset: stops both wakes. */
void EftWater_Reset(void);

/* Water task draw. */
void EftWater_Draw(void);

/* The wake behind each fighter whose wake is on: every frame a streak (two on even frames), on even frames two
   billboards, every third frame a ring. Sizes follow the fighter's speed and height. Skipped while paused. */
void EftWater_UpdateWakes(void);

/* A free splash record, zeroed; NULL when all ten are in use. */
EftWaterSplash *EftWater_AllocSplash(void);

/* 1 when every particle of a splash has died. */
s32 EftWaterSplash_IsEmpty(EftWaterSplash *splash);

/* Creates a splash at pos: sprayA + sprayB streaks, dropA + dropB billboards and four surface rings, all scaled by
   scale. The streak and billboard directions are spread evenly around a random start angle. */
void EftWater_AddSplash(EftWaterSplash **head, EftWaterSplash **tail, EftEVec pos, s32 sprayA, s32 sprayB, s32 dropA,
                        s32 dropB, f32 scale);

/* ------------------------------------------------------------------------------------------------------------
 * Second part (formerly eft_f.c), with its own header and view types. Names the first part already declared with
 * other types are reached through cast macros (the generated code is the same).
 * ------------------------------------------------------------------------------------------------------------ */
/* The first part reaches these through aliases with its own types; from here on they are the real functions. */
#undef EftWaterSplash_UpdateList
#undef EftWaterSplash_DrawList
#undef EftWaterTrail_Spawn
#undef EftWaterTrail_UpdateList
#undef EftWaterTrail_DrawList
#undef EftWaterDrop_Spawn
#undef EftWaterDrop_UpdateList
#undef EftWaterDrop_DrawList
#undef EftWaterRing_Spawn
#undef EftWaterRing_UpdateList
#undef EftWaterRing_DrawList
#undef EftWaterSpray_Spawn
#undef EftWaterSpray_UpdateList
#undef EftWaterSpray_DrawList
#undef EftWaterMist_Spawn
#undef EftWaterMist_UpdateList
#undef EftWaterMist_DrawList
/* eft_f.h declares the module state with its own view type: hide that declaration and cast. */
#define gEftDust gEftDust_fDecl
#include "battle/eft_f.h"
#undef gEftDust
#define gEftDust ((EftWaterView *)gEftDust)
#include "sys/gfx_ot.h"

/* Water-surface effects, 0x142CA0..0x147050: the particle half of the water module that starts in eft_e.c.
   Purely visual: it reads a blast hit record's position, the fighter height and the water surface height, and
   writes only its own pools and draw packets. See include/battle/eft_f.h. */

/* Local views of what the module uses from elsewhere. */
typedef struct EftWaterBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 = paused */
} EftWaterBattleWork;

typedef struct EftWaterCamView {
    /* 0x000 */ u8 unk0[0x140];
    /* 0x140 */ EftWaterMtx world2screen;
} EftWaterCamView;

#define Battle_GetWork ((EftWaterBattleWork *(*)(void))Battle_GetWork)
#define gBtlCamView ((EftWaterCamView *)gBtlCamView)
#define D_002C3630 (*(EftWaterVec *)&D_002C3630) /* (0, 0, 0, 1) */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 atan2f(f32 y, f32 x);
extern f32 sqrtf(f32 x);

#define Vec4_Set ((void (*)(EftWaterVec *dst, f32 x, f32 y, f32 z, f32 w))Vec4_Set)
#define Vec4_Copy ((void (*)(EftWaterVec *dst, EftWaterVec *src))Vec4_Copy)
#define Vec4_Add ((void (*)(EftWaterVec *dst, EftWaterVec *a, EftWaterVec *b))Vec4_Add)
#define Vec4_Sub ((void (*)(EftWaterVec *dst, EftWaterVec *a, EftWaterVec *b))Vec4_Sub)
extern void Vec4_Scale(EftWaterVec *dst, EftWaterVec *src, f32 scale);
#define Vec3_Length ((f32 (*)(EftWaterVec *v))Vec3_Length)
#define Vec3_Normalize ((void (*)(EftWaterVec *dst, EftWaterVec *src))Vec3_Normalize)
extern f32 Mathf_SinFast(f32 angle);
extern f32 Mathf_CosFast(f32 angle);
extern f32 BtlCharApi_GetHeight(s32 objId);

extern s32 EftWater_GetSurfaceY(f32 *outY); /* eft_e.c: height of the water surface; 0 when there is none */
#define EftWaterSplash_IsEmpty ((s32 (*)(EftWaterSplashView *src))EftWaterSplash_IsEmpty) /* eft_e.c: 1 when the splash has nothing left */
extern f32 EftMath_WrapAngle(f32 angle);        /* wraps an angle into -pi..pi */
extern void Mtx_Copy(EftWaterMtx *dst, EftWaterMtx *src); /* matrix copy */

extern void Vec3_Lerp(EftWaterVec *out, EftWaterVec *up, EftWaterVec *dir, f32 angle); /* orientation from an up vector, a direction and a tilt */
extern void EftUtil_MakeFacingMtx(EftWaterMtx *out, EftWaterVec *rot, EftWaterVec *pos);            /* matrix from that orientation and a position */

/* libc rand() scaled to 0..1 (appearance only) */
#define EFT_WATER_RANDF() ((f32)rand() / 2147483647.0f)
/* every size and speed of a trail is scaled by the fighter's height and the hit record's speed */
#define EFT_WATER_SCALE(objId, scale) (BtlCharApi_GetHeight(objId) * 0.05f * (scale))
extern void Mtx_StoreIdentity(EftWaterMtx *m);
#define Mtx_MulVec4 ((void (*)(EftWaterVec *dst, EftWaterMtx *m, EftWaterVec *src))Mtx_MulVec4)
extern void Mtx_Mul(EftWaterMtx *dst, EftWaterMtx *a, EftWaterMtx *b);  /* matrix product */
extern void Mtx_RotateZ(EftWaterMtx *dst, EftWaterMtx *src, f32 angle);    /* rotate about Z */
extern void Mtx_RotateY(EftWaterMtx *dst, EftWaterMtx *src, f32 angle);    /* rotate about Y */
extern s32 Mtx_ProjectPoint(EftWaterIVec *out, EftWaterMtx *m, EftWaterVec *v);  /* projects a point to GS coordinates */
extern void Mtx_ProjectPointsStq(EftWaterIVec *xyz, EftWaterVec *stq, EftWaterMtx *m, EftWaterVec *pos, EftWaterVec *uv,
                          s32 n);                                           /* projects n points, perspective STQ */
extern void ClipVtx_SetArray(EftWaterClipVtx *out, EftWaterVec *pos, EftWaterVec *uv, EftWaterVec *color, s32 n);
extern s32 ClipPoly_ClipPlane(EftWaterClipVtx *poly, EftWaterVec *plane, s32 n);  /* clips a polygon, returns its size */
extern void ClipPoly_ProjectCur(EftWaterIVec *xyz, EftWaterVec *stq, EftWaterClipVtx *poly, s32 n); /* projects it */
extern EftWaterVec *EftGfx_GetClipPlanes(void);                                    /* the 5 clip planes of the view */
extern s32 EftUtil_IsCamUnderWater(void); /* eft_g.c: camera height against the water level; picks the depth bias */
#define EftVram_AddTex ((u64 (*)(void *entry, s32 a1, s32 a2))EftVram_AddTex)                     /* advances a texture, returns TEX0 */

/* GS XYZF2 register value. */
typedef struct EftWaterXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftWaterXyzf;

typedef struct EftWaterGsVtx {
    /* 0x00 */ u8 rgba[4];
    /* 0x04 */ f32 q;
    /* 0x08 */ f32 s;
    /* 0x0C */ f32 t;
    /* 0x10 */ EftWaterXyzf xyz;
} EftWaterGsVtx; /* 0x18: RGBAQ, ST, XYZF2 */

typedef struct EftWaterPktHead {
    /* 0x00 */ u32 tag;
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 gif0;
    /* 0x18 */ u64 gif1;
} EftWaterPktHead;

/* A+D packet that sets one register (TEST_1 here). 0x30 bytes. */
typedef struct EftWaterRegPkt {
    /* 0x00 */ EftWaterPktHead h;
    /* 0x20 */ u64 data;
    /* 0x28 */ u64 reg;
} EftWaterRegPkt;

/* Triangle strip of one RGBAQ and four ST + XYZF2 (EftWater_DrawBillboard). 0x80 bytes. */
typedef struct EftWaterSpritePkt {
    /* 0x00 */ EftWaterPktHead h;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ u8 rgba[4];
    /* 0x34 */ f32 q;
    /* 0x38 */ struct {
        /* 0x00 */ f32 s;
        /* 0x04 */ f32 t;
        /* 0x08 */ EftWaterXyzf xyz;
    } v[4];
    /* 0x78 */ u64 pad;
} EftWaterSpritePkt;

/* Triangle strip of four full vertices (EftWater_DrawSprayQuad). 0x90 bytes. */
typedef struct EftWaterQuadPkt {
    /* 0x00 */ EftWaterPktHead h;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftWaterGsVtx v[4];
} EftWaterQuadPkt;

/* One triangle (EftWater_DrawClippedFan). 0x80 bytes. */
typedef struct EftWaterTriPkt {
    /* 0x00 */ EftWaterPktHead h;
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftWaterGsVtx v[3];
    /* 0x78 */ u64 pad;
} EftWaterTriPkt;

/* Links a packet into the chain of a depth slot (clamped to 0..0xFFF). */
static inline void EftWaterOt_Add(OtPrim *p, s32 z, s32 layer);

/* Queues a packet that sets GS TEST_1 at depth z; leaves the calling function when the packet memory is used up. */
#define EFT_WATER_QUEUE_TEST(test, z, layer)                                                                         \
    {                                                                                                               \
        EftWaterRegPkt *q = (EftWaterRegPkt *)gOtCur;                                                                 \
        u64 *d;                                                                                                     \
                                                                                                                    \
        gOtCur = (u32 *)(q + 1);                                                                                    \
        d = &q->h.gif0;                                                                                             \
        if (q == NULL) {                                                                                            \
            return;                                                                                                 \
        }                                                                                                           \
        q->h.tag = 0x20000002;                                                                                      \
        q->h.vif0 = 0x10000000;                                                                                     \
        q->h.vif1 = 0x50000002;                                                                                     \
        q->h.next = 0;                                                                                              \
        *d = 0x1000000000008001;                                                                                    \
        q->h.gif1 = 0xE;                                                                                            \
        q->data = (test);                                                                                           \
        q->reg = 0x47;                                                                                              \
        EftWaterOt_Add((OtPrim *)q, z, layer);                                                                       \
    }

#define EFT_WATER_PAUSED() (Battle_GetWork()->flags & 0x100)

/* Updates every source of a list and unlinks the ones that are finished. */
void EftWaterSplash_UpdateList(EftWaterSplashView **head, EftWaterSplashView **tail);

/* Updates a source's three particle lists; returns 1 when it has nothing left. */
s32 EftWaterSplash_Update(EftWaterSplashView *src);

/* Draws every source of a list. */
void EftWaterSplash_DrawList(EftWaterSplashView *src);

/* Starts the final fade of everything a source owns (once). */
void EftWaterSplash_FadeOut(EftWaterSplashView *src);

/* Takes a free trail from the pool of 15, zeroed; NULL when all are in use. */
EftWaterTrail *EftWaterTrail_Alloc(void);

/* 1 when all three particle lists of a trail are empty. */
s32 EftWaterTrail_IsEmpty(EftWaterTrail *trail);

/* Starts a trail where a blast hit record is: two sprays to the sides of its direction of travel, two drops along
   it and a ground ring, all scaled by the fighter's height and by the record's horizontal speed. */
void EftWaterTrail_Spawn(EftWaterTrail **head, EftWaterTrail **tail, s32 objId, EftWaterHitRec *hit);

/* Updates every trail of a list, unlinks the finished ones and fades the oldest so at most 5 stay at full strength. */
void EftWaterTrail_UpdateList(EftWaterTrail **head, EftWaterTrail **tail);

/* Updates a trail's three particle lists; returns 1 when it has nothing left. */
s32 EftWaterTrail_Update(EftWaterTrail *trail);

/* Draws every trail of a list (its particles hold world positions, so the origin is zero). */
void EftWaterTrail_DrawList(EftWaterTrail *trail);

/* Starts the final fade of everything a trail owns (once). */
void EftWaterTrail_FadeOut(EftWaterTrail *trail);

/* Takes a free drop from the pool of 60, zeroed; NULL when all are in use. */
EftWaterDrop *EftWaterDrop_Alloc(void);

/* Adds a drop to a list: launched from pos along yaw / pitch (degrees) at `speed`, fading over `life` seconds. */
void EftWaterDrop_Spawn(EftWaterDrop **head, EftWaterDrop **tail, EftWaterVec pos, f32 yaw, f32 pitch, f32 speed, f32 rot, f32 rotVel, f32 size, f32 sizeVel, f32 sizeDamp,
                       f32 gravity, f32 life, f32 delay, u8 r, u8 g, u8 b, u8 tex,
                       u8 layer, s32 flags);

/* Updates every drop of a list and unlinks the dead ones. */
void EftWaterDrop_UpdateList(EftWaterDrop **head, EftWaterDrop **tail);

/* One frame of a drop: delay, ballistic motion, growth and fades. Returns 1 when it is dead. */
s32 EftWaterDrop_Update(EftWaterDrop *drop);

/* Draws the live drops of a list as camera-facing quads at origin + pos. */
void EftWaterDrop_DrawList(EftWaterDrop *drop, EftWaterVec origin);

/* Makes every drop of a list finish within 0.1 s. */
void EftWaterDrop_FadeOutList(EftWaterDrop *drop);

/* Takes a free ring from the pool of 30, zeroed; NULL when all are in use. */
EftWaterRing *EftWaterRing_Alloc(void);

/* Adds a ground ring to a list. With FADE_IN it rises to alphaMax over 30% of `time` and falls over the rest. */
void EftWaterRing_Spawn(EftWaterRing **head, EftWaterRing **tail, EftWaterVec pos, f32 rot, f32 size, f32 sizeVel, f32 sizeDamp, f32 alphaMax, f32 time, f32 delay, u8 r, u8 g, u8 b, u8 tex,
                       u8 layer, s32 flags);

/* Updates every ring of a list and unlinks the dead ones. */
void EftWaterRing_UpdateList(EftWaterRing **head, EftWaterRing **tail);

/* One frame of a ring: delay, follow the surface, grow, fade in then out. Returns 1 when it is dead. */
s32 EftWaterRing_Update(EftWaterRing *ring);

/* Draws the live rings of a list as quads lying on the ground. */
void EftWaterRing_DrawList(EftWaterRing *ring);

/* Makes every ring of a list fade out within 0.1 s. */
void EftWaterRing_FadeOutList(EftWaterRing *ring);

/* Takes a free spray from the pool of 30, zeroed; NULL when all are in use. */
EftWaterSpray *EftWaterSpray_Alloc(void);

/* Adds a spray to a list: starts `dist` out from pos along yaw, `height` up, and flies along yaw / pitch. */
void EftWaterSpray_Spawn(EftWaterSpray **head, EftWaterSpray **tail, EftWaterVec pos, f32 dist, f32 height, f32 yaw, f32 pitch, f32 roll, f32 tilt, f32 tiltEnd,
                         f32 speed, f32 size, f32 sizeVel, f32 sizeDamp, f32 gravity, f32 nearScale,
                         f32 widthScale, f32 life, f32 delay, u8 r, u8 g, u8 b, u8 tex,
                         u8 layer, s32 flags);

/* Updates every spray of a list and unlinks the dead ones. */
void EftWaterSpray_UpdateList(EftWaterSpray **head, EftWaterSpray **tail);

/* One frame of a spray: delay, ballistic motion, growth, tilt and dissolve. Returns 1 when it is dead. */
s32 EftWaterSpray_Update(EftWaterSpray *spray);

/* Draws the live sprays of a list: a quad turned to its flight direction and tilt, at origin + pos. */
void EftWaterSpray_DrawList(EftWaterSpray *spray, EftWaterVec origin);

/* Makes every spray of a list finish dissolving within 0.1 s. */
void EftWaterSpray_FadeOutList(EftWaterSpray *spray);

/* Takes a free mist from the pool of 30, zeroed; NULL when all are in use. */
EftWaterMist *EftWaterMist_Alloc(void);

/* Adds a mist to a list: it circles pos at `radius`, its yaw turning by yawVel each frame. */
void EftWaterMist_Spawn(EftWaterMist **head, EftWaterMist **tail, EftWaterVec pos, f32 radius, f32 height, f32 yaw, f32 yawVel, f32 yawDamp, f32 pitch, f32 roll,
                        f32 tilt, f32 tiltEnd, f32 speed, f32 size, f32 sizeVel, f32 sizeDamp, f32 gravity,
                        f32 nearScale, f32 widthScale, f32 life, f32 delay, u8 r, u8 g, u8 b,
                        u8 tex, u8 layer);

/* Updates every mist of a list and unlinks the finished ones. */
void EftWaterMist_UpdateList(EftWaterMist **head, EftWaterMist **tail);

/* One frame of a mist: delay, turn the direction, move out along it, grow, dissolve. Returns 1 when finished. */
s32 EftWaterMist_Update(EftWaterMist *mist);

/* Draws the live mists of a list. */
void EftWaterMist_DrawList(EftWaterMist *mist);

/* 1 when a projected vertex (GS coordinates, 12.4 fixed, centre 2048) is in front of the camera and within a
   box around the screen centre: margin 0 = the 512 x 448 screen, 1..3 = wider boxes, else the whole GS range. */
s32 EftWater_IsOnScreen(EftWaterIVec v, s32 margin);

/* Queues a camera-facing textured quad of side `size` at pos, turned by `rot` degrees. Skipped when a corner is
   outside the wide screen box. A non-zero alphaRef wraps it in alpha-test register packets. */
void EftWater_DrawBillboard(EftWaterVec *pos, EftWaterMtx *world2screen, f32 size, f32 rot, u8 r, u8 g, u8 b, u8 a,
                           u8 alphaRef, u64 *tex, u8 layer);

/* Queues a textured quad of side `size` lying in the ground plane at pos, turned by `rot` degrees about the
   vertical, as two triangles through the clipper. */
void EftWater_DrawGroundQuad(EftWaterVec *pos, EftWaterMtx *world2screen, f32 size, f32 rot, u8 r, u8 g, u8 b, u8 a,
                            u64 *tex, u8 layer);

/* Queues a textured quad that lies along `orient`'s z axis from size * near to size * far, size * width wide,
   rolled about its middle by `roll` degrees. The alpha test reference makes it dissolve. */
void EftWater_DrawSprayQuad(EftWaterVec *pos, EftWaterMtx *orient, EftWaterMtx *world2screen, f32 roll, f32 size,
                            f32 near, f32 far, f32 width, u8 r, u8 g, u8 b, u8 a, u8 alphaRef, u64 *tex,
                            u8 layer);

/* Refreshes the TEX0 of the module's five textures (only while particles exist). */
void EftWater_UpdateTextures(s32 a0, s32 a1);

/* Clips a triangle (three EftWaterClipVtx) against the five planes of the view, projects what is left and queues
   it as a fan of textured triangles. A triangle whose three corners are all unusable is dropped. */
#if 0 /* NON-MATCHING: 429 instructions against 426 */
/* A register-masked structural diff (build/scratch_cleanup3_V/sdiff.py) leaves 23 lines (142 before round 4). */
/* Round 4 (scratch build/scratch_cleanup4_W2/cf*.c). The function is the water twin of EftMesh_DrawTriClip +
   EftMesh_QueueTri (eft_ad_b.c, matched): rewritten after them it has the original's blocks, frame (0x1B0), stack
   slots (poly / layer / tex0 at sp+288 / 292 / 296, the three sq / lq saves around EftUtil_IsCamUnderWater) and
   every instruction of the depth, cap, clip-test and packet code. What made the difference:
   - the triangle writer is a `static inline` taking the nine corner pointers (EftWater_QueueTri), header stores
     in the order prim, tag, vif0, vif1, gif0, gif1, next, pad;
   - scr is an array of 4-ALIGNED structs indexed at every use (`scr[i - 1].z`): that gives the original's
     `sll s2,s5,4 / addiu a0,sp,8 / addiu v1,s2,-16 / addu s0,a0,v1 / addu s1,a0,s2` exactly (the 8-aligned
     EftWaterIVec and the `zp` pointer form of the mesh twin both give walking pointers here);
   - the screen test is `clipped = 1; if (z > 0 && x <= 0xFFEF && x > 0) { if (y <= 0xFFEF) clipped = y <= 0; }`
     through a POINTER parameter (movz on the two y tests; the by-value form of EftMesh_IsOffScreen copies the
     16 bytes here and costs 26 instructions).
   What still differs (all one cause, the loop pass's choice of induction pointers):
   - the original does not strength-reduce &scr[i - 1]: it recomputes it where it is used
     (`addu v1,sp,s2 / addiu v1,v1,-16` for the clip test, `addiu t4,t2,-16` for the writer) and keeps only
     &stq[i - 1] (t6, +16) and &poly[i] (s6, +48) as walking pointers; here &scr[i - 1] becomes a third walking
     pointer (s8). With one saved register gone, n lands in t6 (saved / restored with sq / lq around
     ClipPoly_ProjectCur) instead of s8, and the XYZF2 mask 0xFF000000FFFFFFFF is rebuilt in the loop instead of
     being hoisted into t7. `&scr[i] - 1` and `scr + i - 1` compile to the same thing.
   - to try next: the giv is "not worth while" for the loop pass when lifetime * threshold * benefit < the loop's
     insn count (-dL, `giv at N combined with ...`): look for a form in which the clip test's and the writer's
     uses of &scr[i - 1] do not combine into one giv (in the original the two addresses are computed in
     different blocks from sp + (i << 4)). */
typedef struct EftWaterScr4 {
    s32 x, y, z, w;
} EftWaterScr4;

/* 1 when a projected vertex cannot be drawn (behind the camera or outside the GS coordinate range). */
static inline s32 EftWater_IsClipped(EftWaterScr4 *v);

static inline void EftWater_QueueTri(EftWaterScr4 *p0, EftWaterScr4 *p1, EftWaterScr4 *p2, EftWaterVec *c0,
                                     EftWaterVec *c1, EftWaterVec *c2, EftWaterVec *t0, EftWaterVec *t1,
                                     EftWaterVec *t2, s32 layer, s32 z, u64 tex0);

void EftWater_DrawClippedFan(EftWaterClipVtx *poly, s32 layer, u64 tex0);
#endif

