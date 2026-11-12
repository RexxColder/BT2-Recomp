#include "common.h"
#include "battle/eft_o.h"

/*
 * Effect tasks, 0x167E68..0x1699D0. Two modules, both VISUAL ONLY (no hit record, no fighter or battle state is
 * written; fighters are read through BtlCharApi getters):
 *
 * 1. 0x167E68..0x168600  the body lightning task and its manager, the second half of the EftBolt module of
 *    eft_n.c (class tables 0x2C3A78 task / 0x2C3A60 manager). One task per fighter while the fighter's parameter
 *    flags have bit 4 or 8 (EftAura_UpdateLightning calls EftBolt_Enable / EftBolt_Disable). The update does
 *    nothing but texture stepping while the battle is paused (battle flag 0x100).
 *
 * 2. 0x168600..0x1699D0  effect pack part kind 2, "rays" (class tables 0x2C3AA8 task / 0x2C3A90 manager): up
 *    to 10 camera-facing quads fanned around a point. EftEmit_SpawnType2 (eft_h.c) creates, places, stops and
 *    kills a part through the entry points at 0x168600..0x168808; EftEmit_KillAll / EftEmit_UpdateAlive
 *    (eft_i.c) call EftRays_Kill / EftRays_IsAlive. libc rand(): two per ray at creation and two per ray each
 *    time its length flicker turns round (appearance only).
 */

typedef struct EftOBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 = paused */
} EftOBattleWork;

/* The view being drawn (gBtlCamView). */
typedef struct EftOView {
    /* 0x000 */ u8 unk0[0x40];
    /* 0x040 */ Mtx44 camMtx;
    /* 0x080 */ u8 unk80[0xC0];
    /* 0x140 */ Mtx44 screenMtx;
} EftOView;

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);

extern void Vec4_Copy(void *dst, void *src);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Add(void *dst, void *a, void *b);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(void *dst, Mtx44 *m, void *src);
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b); /* matrix product */
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);         /* inverse of a rotation + translation matrix */
extern void Mtx_RotateZ(Mtx44 *dst, Mtx44 *src, f32 angle); /* rotate about Z */
extern void Mtx_ScaleDiag(Mtx44 *dst, Mtx44 *src, void *scale); /* scale by a vector */
extern void Vu0Cur_Push(void);                            /* VU0 matrix stack: push */
extern void Vu0Cur_Pop(void);                            /* VU0 matrix stack: pop */
extern void Vu0Cur_LoadMtx(Mtx44 *m);                        /* VU0 current matrix = m */
extern s32 Vu0Cur_ProjectPoints(void *out, void *pos, s32 count);  /* project to screen */
extern void ClipVtx_Set(void *vtx, void *pos, void *uv, void *col); /* fills one polygon vertex */
extern f32 EftMath_WrapAngle(f32 angle);
extern void EftGfx_DrawPolyAvgZFront(void *verts, s32 arg1, s32 arg2, s32 arg3, s32 front, s32 flip, u64 tex,
                                     s32 zOfs);

extern void *BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(void *pool, s32 size);
extern void BtlPool_Free(void *pool, void *p);
extern EftOBattleWork *Battle_GetWork(void);
extern s32 BtlScene_GetCharCount(void);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern s32 BtlScene_IsCharInView(s32 objId);
extern s32 BtlScene_IsEffectStopped(s32 objId, s32 kind);
extern s32 BtlScene_IsEffectHidden(s32 objId, s32 kind);
extern void *BtlTask_CreateChildList(EftOTask *task, s32 count, s32 workSize);
extern EftOTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void BtlTask_SetDead(EftOTask *task);                  /* kill a task */
extern u64 EftVram_AddTex(void *entry, s32 a, s32 b);        /* advances a texture, returns TEX0 */
extern u64 EftVram_AddImage(void *set, s32 a, s32 b);
extern u64 EftVram_AddClut(void *entry);
extern void EftTexSet_Load32(void *set, s32 *pack);            /* binds a texture set to a pack */

extern s32 BtlCharApi_ObjGetParamFlags0(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_IsHidden(s32 objId);
extern s32 BtlCharApi_IsModelNew(s32 objId);
extern s32 BtlCharApi_ObjTestFlagBit21(s32 objId);

extern void EftBolt_FreeSegs(EftOBolt *bolt);
extern void EftBolt_UpdateAll(EftOBoltWork *work, s32 objId);
extern void EftBolt_DrawAll(EftOBoltWork *work, f32 alpha);
extern void EftBolt_UpdateFlashes(EftOBoltWork *work, s32 objId);
extern void EftBolt_DrawFlashes(EftOBoltWork *work, f32 alpha);
extern void EftBolt_Spawn(EftOBoltWork *work, s32 objId);

extern EftOView *gBtlCamView;
extern void *gEftBoltTaskClass[6];
extern void *gEftRaysClass[6];

/* ---- body lightning: task and manager -------------------------------------------------------------------- */

/* Advances the two shared textures once per frame and gives the work block this frame's TEX0. */
/* (`one` is needed: with the literal 1 in both stores the first branch is scheduled differently.) */
void EftBolt_UpdateTex(EftOBoltWork *w);

/* Reads what the task needs from the fighter: parameter flags and body scale. */
void EftBolt_ReadChar(EftOBoltWork *w, s32 objId);

/* Init callback of the per-fighter task. */
void EftBoltTask_Init(EftOTask *task, s32 *arg);

/* Term callback: frees the first bolt's joints and clears the fighter's entry. */
void EftBoltTask_Term(EftOTask *task);

/* Update callback: bolts and flashes unless paused; once stopped, dies when the last bolt and flash are gone. */
void EftBoltTask_Update(EftOTask *task);

/* Post-update callback: nothing. */
void EftBoltTask_PostUpdate(EftOTask *task);

/* Reset callback: the task dies. */
void EftBoltTask_Reset(EftOTask *task);

/* Draw callback: bolts and flashes, at 0.3 alpha when the camera is inside the fighter's view and its flag 21. */
void EftBoltTask_Draw(EftOTask *task);

/* Init callback of the manager: the joint pool (100 per fighter), the task table and the two texture sets. */
void EftBoltMgr_Init(EftOTask *task);

/* Term callback of the manager. */
void EftBoltMgr_Term(void) {
    BtlPool_Free(BtlPool_GetCurrent(), gEftBoltPool->tasks);
    BtlPool_Free(BtlPool_GetCurrent(), gEftBoltPool->pool);
    BtlPool_Free(BtlPool_GetCurrent(), gEftBoltPool);
    gEftBoltPool = NULL;
}

/* Update callback of the manager: the textures have not been advanced this frame. */
void EftBoltMgr_Update(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        gEftBoltPool->tex[i].ready = 0;
    }
}

/* Reset callback of the manager: nothing. */
void EftBoltMgr_Reset(void);

/* Creates the fighter's lightning task unless it has one. */
s32 EftBolt_Enable(s32 objId);

/* Asks the fighter's lightning task to stop: no new bolts, and it dies when the live ones are gone. */
s32 EftBolt_Disable(s32 objId);

/* ---- effect pack part kind 2: rays ------------------------------------------------------------------------ */

/* Creates a part. */
void *EftRays_Create(EftRaysArg *arg);

/* Starts the part's end: hold, then fade. */
void EftRays_Stop(EftOTask *task);

/* The part dies on its next update. */
void EftRays_Kill(EftOTask *task);

/* Places the part. */
void EftRays_SetPos(EftOTask *task, Vec4 *pos);

/* Frames before the part starts to animate. */
void EftRays_SetDelay(EftOTask *task, f32 frames);

/* Frames between the stop and the start of the fade. */
void EftRays_SetHold(EftOTask *task, f32 frames);

/* Length of the fade in frames. */
void EftRays_SetFade(EftOTask *task, f32 frames);

/* The part has not finished fading. */
s32 EftRays_IsAlive(EftOTask *task);

/* Size factor of the part. */
void EftRays_SetSize(EftOTask *task, f32 size);

/* Init callback of the manager: 20 rays on the free list, 3 part tasks. */
void EftRaysMgr_Init(EftOTask *task);

/* Term callback of the manager. */
void EftRaysMgr_Term(void);

/* Update callback of the manager: nothing. */
void EftRaysMgr_Update(void);

/* Init callback of a part: one ray per entry of the part data, each with two random lengths. */
void EftRays_Init(EftOTask *task, EftRaysArg *arg);

/* Term callback of a part: gives its rays back. */
void EftRays_Term(EftOTask *task);

/* Update callback of a part: delay, life, hold and fade; the rays are stepped until the fade is over. */
void EftRays_Update(EftOTask *task);

/* Reset callback of a part: the task dies. */
void EftRays_Reset(EftOTask *task);

/* Draw callback of a part. */
void EftRays_Draw(EftOTask *task);

#define EFT_RAYS_CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((hi) < (x) ? (hi) : (x)))

/* Draws one ray: a quad in the camera plane, scaled, turned by the ray's angle and placed at the part's
   position; its colour is the key colour times the pulse factors, alpha times the part's fade.
   (`grow = 0.0f` has to stand directly in front of the loop: set earlier, the 0.0f stores in between use its
   register and the frame and the callee-saved float registers change.) */
void EftRays_DrawRay(EftRays *w, EftRay *ray);

/* Steps every ray of a part. */
/* (The re-roll block is written out in both arms: the compiler merges them, but the four uses of 2147483647.0f
   decide which callee-saved register it gets.) */
void EftRays_Step(EftRays *w);

/* Takes a ray from the pool and appends it to a part's list. */
EftRay *EftRays_AllocRay(List *list);

/* Gives a ray back to the pool; returns the one after it. */
EftRay *EftRays_FreeRay(List *list, EftRay *ray);

/* TEX0 of texture n of a part resource; the texture is advanced the first time it is asked for in a frame. */
u64 EftRays_GetTex(EftRaysTex *res, s32 n);

/* Starts a ray's key animation and gives it the colour and size of one key. */
void EftRays_SetKey(EftRay *ray, EftRaysDef *def, s32 key);

/* Advances a ray's key animation: key 0 to 1 over the first part, 1 to 2 over the rest. */
/* (One int temporary `di` reused for the three colour differences, as `d` is for the two sizes: with the
   subtraction written inside each expression, or one temporary per channel, the registers come out differently.) */
void EftRays_LerpKey(EftRay *ray, EftRaysDef *def);

/* The handle is a live task of this class. */
s32 EftRays_IsTask(EftOTask *task);
