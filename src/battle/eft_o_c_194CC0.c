#include "common.h"
#include "battle/eft_o.h"

/*
 * Effect tasks, 0x16AE78..0x16C2E0. Two modules:
 *
 * 1. 0x16AE78..0x16B4E0  EftBodyFx: fighter effect request 0x1A (BtlFx_UpdateReq1A in btl_char_fx.c calls
 *    EftBodyFx_Start when the request appears and EftBodyFx_Stop when it ends). One task per fighter (class
 *    0x2C3B08, manager class 0x2C3AF0) that runs effect pack 0x23F of the common effect file on the fighter's
 *    body: position = node 3, direction = unit vector from node 3 to node 0x2E, size = the fighter's body
 *    scale (at least 0.5). VISUAL ONLY: no hit record, no fighter or battle state is written. No random draw
 *    here (the pack's part modules may draw their own). The task is skipped while BtlScene_IsEffectStopped
 *    (objId, 4).
 *
 * 2. 0x16B4E0..0x16C2E0  EftDisc, first part: the manager callbacks and the disc's init and update (the rest
 *    of the module is in eft_p.c: term, post-update, reset, draw, the hit record, homing and the creators).
 *    SIMULATION: the update moves the disc and, while it flies, publishes a hit record every frame
 *    (EftDisc_AddHit). What the update does, in order (verified by the matching code where the function
 *    matches, read from the disassembly otherwise; see the report):
 *      - a ki blast disc (kinds 0, 1, 3) is skipped while BtlScene_IsEffectStopped(owner, 0); it dies when
 *        the owner is changing form (BtlCharApi_IsChanging); a held kind 0 disc dies (flags DEAD | LOST)
 *        when the owner is no longer charging a ki blast (BtlCharApi_IsChargingKiBlast);
 *      - a technique piece (kinds 2, 4) is skipped while BtlScene_IsEffectStopped(owner, 1) or while the
 *        technique definition has flag 2;
 *      - held (flag HELD, kinds 0..2): it grows over growTime frames (size and alpha), and sits in front
 *        of the hand: pos = hand node B + unit(B - A) * size * 3, with A / B = nodes 0x14 / 0x15 or 0x22 /
 *        0x23, plus a vertical bob of cos(timer * 0.04 * pi). A kind 1 disc (AUTO) is released as soon as
 *        it is grown;
 *      - flying (flag FLYING): EftDisc_Home turns the direction toward the opponent, pos += dir * speed,
 *        the previous position is kept for the hit shape; kinds 3 and 4 fade in over growTime; every kind
 *        fades out over the last fadeTime frames of its life (or at once when END is set); age >= life
 *        kills it;
 *      - the model matrix is built (spin, bank, roll: appearance only);
 *      - END with the model no longer visible -> DEAD; a technique piece drives its pack parts and steps
 *        the pack's trail width; a flying disc that is neither ending nor dead adds its hit record; DEAD
 *        kills the task.
 *    Random draws: EftDisc_Init draws libc rand() once for kinds 0, 1 and 2: the spin rate (0.1 .. 0.11) *
 *    pi radians per frame. It only enters the model's rotation angle (rotY), not the position, direction
 *    or hit record.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 atan2f(f32 y, f32 x);
extern f32 cosf(f32 x);
extern f32 Mathf_Asin(f32 x);

extern void Vec4_Copy(void *dst, void *src);
extern void Vec4_Set(void *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec3_Add(void *dst, void *a, void *b);
extern void Vec3_Sub(void *dst, void *a, void *b);
extern void Vec3_Scale(void *dst, void *src, f32 scale);
extern void Vec3_Normalize(void *dst, void *src);
extern f32 Vec3_Dot(void *a, void *b);
extern f32 EftMath_WrapAngle(f32 angle);
extern void Vu0Cur_LoadIdentity(void);        /* VU0 matrix stack: current = identity */
extern void Vu0Cur_Push(void);        /* push */
extern void Vu0Cur_Pop(void);        /* pop */
extern void Vu0Cur_StoreMtx(Mtx44 *m);    /* store the current matrix */
extern void Vu0Cur_Translate(void *pos);   /* translate */
extern void Vu0Cur_RotateZ(f32 angle);   /* rotate about Z */
extern void Vu0Cur_RotateX(f32 angle);   /* rotate about X */
extern void Vu0Cur_RotateY(f32 angle);   /* rotate about Y */
extern void Vu0Cur_ScaleDiagUniform(f32 scale);   /* scale */

extern void *BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(void *pool, s32 size);
extern void BtlPool_Free(void *pool, void *p);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern f32 BtlScene_GetCharScale(s32 chr);
extern s32 BtlScene_IsEffectStopped(s32 objId, s32 kind);
extern void *BtlTask_CreateChildList(EftOTask *task, s32 count, s32 workSize);
extern EftOTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void BtlTask_SetDead(EftOTask *task);            /* kill a task */
extern void BtlTask_SetOwnerTag(EftOTask *task, s32 flags); /* or into the task's class flags */
extern void EftTexSet_Load32(void *set, s32 *pack);      /* binds a texture set to a pack */

extern void BtlCharApi_GetNodePos(s32 objId, s32 node, void *out);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern s32 BtlCharApi_IsLockedOn(s32 objId);
extern s32 BtlCharApi_IsChargingKiBlast(s32 objId);
extern s32 BtlCharApi_IsChanging(s32 objId);

extern void EftEmit_LoadSet(void *owner, EftOSet *set, void *head, s32 *base, s32 common, s32 idx);
extern void EftEmit_FreeSet(EftOSet *set);
extern void EftEmit_BeginFrame(EftOSet *set);
extern s32 EftEmit_GetEndFrames(EftOSet *set);
extern void EftEmit_InitState(EftOSet *set, void *state);
extern void EftEmit_TermState(EftOSet *set, void *state);
extern s32 EftEmit_GetFlagsFromMask(EftOSet *set, void *state, s32 objId, s32 type, s32 idx, s32 ending, s32 kill,
                                    s32 mask);
extern void EftEmit_Spawn(EftOSet *set, void *state, EftOEmitNodes *nodes, void *pos, void *dir, s32 objId,
                          s32 node, s32 arg7, s32 type, s32 idx, s32 flags, f32 scale);
extern void EftEmit_KillAll(EftOSet *set, void *state);
extern s32 EftEmit_UpdateAlive(EftOSet *set, void *state);
extern void EftEmit_SetNode(EftOEmitNodes *nodes, s32 slot, s32 node, void *pos);
extern void EftEmit_RefreshFixedNodes(s32 objId, EftOEmitNodes *nodes);
extern void EftEmit_UpdateTrailWidth(EftOSet *set, void *state);

extern void EftMesh_Init(void *model, s32 *data);    /* model template from pack data */
extern void EftMesh_SetTex(void *model, void *tex);    /* its texture set */
extern void EftMesh_SetMtx(void *model, Mtx44 *m);     /* its matrix */
extern void EftMesh_Copy(void *model, void *proto);  /* instance of a template */
extern void EftMesh_SetTexBase(void *model, s32 a1);
extern void EftMesh_SetOwner(void *model, s32 objId, s32 a2);

extern void EftDisc_SpawnParts(EftOTask *task, s32 mode);
extern void EftDisc_AddHit(EftOTask *task);
extern void EftDisc_SetTex(EftODisc *w, void *tex, s32 a, s32 b);
extern void EftDisc_Home(f32 speed, f32 maxTurn, f32 bank, void *out, void *pos, void *dir, s32 objId);
extern void EftDisc_StepTex(EftODisc *w);
extern s32 EftDiscMgr_PushHeld(EftOTask *task, s32 objId, s32 kind);

extern void *gEftBodyFxClass[6];

/* ---- fighter effect request 0x1A: effect pack 0x23F on the body ------------------------------------------- */

/* Drives every part of the pack with the phase mask of this frame. */
void EftBodyFx_UpdateParts(s32 objId, EftOTask *task, EftOSet *set);

/* Init callback. */
void EftBodyFx_Init(EftOTask *task, EftBodyFxArg *arg);

/* Term callback. */
void EftBodyFx_Term(EftOTask *task);

/* Update callback: follows the fighter; after the stop it lives for the pack's end frames. */
void EftBodyFx_Update(EftOTask *task);

/* Reset callback: the parts and the task die at once. */
void EftBodyFx_Reset(EftOTask *task);

/* Post-update callback: from the second frame on, drops finished parts and clears the phase mask. */
void EftBodyFx_PostUpdate(EftOTask *task);

/* Draw callback: nothing. */
void EftBodyFx_Draw(EftOTask *task);

/* Init callback of the manager: loads the effect packs (one: number 0x23F of the common effect file); 3 tasks. */
void EftBodyFxMgr_Init(EftOTask *task);

/* Term callback of the manager. */
void EftBodyFxMgr_Term(void);

/* Update callback of the manager. */
void EftBodyFxMgr_Update(void);

/* Starts the effect on a fighter; fails when it is already running. */
s32 EftBodyFx_Start(EftBodyFxArg arg);

/* Asks the fighter's effect to end. */
s32 EftBodyFx_Stop(s32 objId);

/* ---- disc: manager, init and update ------------------------------------------------------------------------ */

/* Init callback of the manager: two texture sets, two model templates, a list of 20 discs. */
void EftDiscMgr_Init(EftOTask *task);

/* Update callback of the manager: the texture sets have not been advanced this frame. */
void EftDiscMgr_Update(void);

/* Reset callback of the manager: nothing. */
void EftDiscMgr_Reset(void);

/* Term callback of the manager. */
void EftDiscMgr_Term(void) {
    BtlPool_Free(BtlPool_GetCurrent(), gEftDisc->res);
    BtlPool_Free(BtlPool_GetCurrent(), gEftDisc);
    gEftDisc = NULL;
}

/* Init callback of a disc. */
void EftDisc_Init(EftOTask *task, EftODiscArg *arg);

/* The roll decay block needs its own zero / clamp variable `k` (not the function-wide `t`) and the clamp written
   as an `if` around a ?: so that rollLeft is allocated before the clamp result (f2 / f3). */
#define EFT_O_CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((hi) < (x) ? (hi) : (x)))

/* Update callback of a disc: see the notes at the top of the file. */
void EftDisc_Update(EftOTask *task);
