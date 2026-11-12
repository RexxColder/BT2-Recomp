#include "common.h"
#include "battle/eft_r.h"

/*
 * Effect modules 0x174A70..0x178AB0 (see include/battle/eft_r.h for the list and the layouts).
 *
 * Task classes are {update, init, term, post-update, reset, draw}. The per-character sub-managers (kinds 0..9 of
 * gEftCharKindClass, 0x2C3BE0, created by 0x171F10 for each character whose effect pack has the entry) register
 * their child list with EftChar_SetList(chr, kind, list); EftChar_GetList(objId, kind) returns it. Kinds here:
 * 0 charge aura, 1 and 2 ki blasts, 3 ki blast charge glow. A character with a type 2 ki blast gets the EftKiObj
 * manager for kind 1 instead, one with a type 3 ki blast the EftKiBomb manager for kind 2 and no kind 3 (read from
 * the disassembly of 0x171F10 / 0x172128).
 *
 * Random draws in this file:
 *   BtlChar_RandF (fighter generator)  two per deflection or reflection, inside BtlCharApi_GetDeflectDir
 *                                      (EftKiBlast_Turn, EftKiObj_Turn): the blast's new direction. SIMULATION.
 *   Rand_FloatRange (VU0 R register)   three per bomb in EftKiBomb_Launch: the throw direction. SIMULATION.
 *   libc rand()                        two per bomb / object at launch (spin rate and sense), one per bomb
 *                                      explosion (which of two sounds), one when a bomb comes to rest (its
 *                                      resting angle). Appearance and sound only.
 *
 * Emitted data: .lit4 0x2FCC0C..0x2FCC40 (19.35, 0.8, 0.7, 19.35, 0.2, -0.2, 2147483647, 0.3, pi, 1500, pi, 0.7,
 * 2147483647; bits checked against the original) and .rodata 0x2ECD40..0x2ECD5C (the two initialisers of
 * EftKiBomb_HandleHits: {0, -1, 0, 1} and {0, 90, 270}).
 */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sqrtf(f32 x);

extern void Vec4_Set(EftRVec *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(EftRVec *dst, EftRVec *src);
extern void Vec4_Sub(EftRVec *dst, EftRVec *a, EftRVec *b);
extern void Vec3_Add(EftRVec *dst, EftRVec *a, EftRVec *b);
extern void Vec3_Scale(EftRVec *dst, EftRVec *src, f32 scale);
extern void Vec3_Normalize(EftRVec *dst, EftRVec *src);
extern void Mtx_StoreIdentity(EftRMtx *m);
extern void Mtx_SetTrans(EftRMtx *m, EftRVec *pos);               /* sets the translation row */
extern void Mtx_Mul(EftRMtx *out, EftRMtx *a, EftRMtx *b);   /* matrix product */
extern void Mtx_RotateX(EftRMtx *out, EftRMtx *in, f32 angle);   /* rotation about one axis */
extern void Vec3_Copy(EftRVec *dst, EftRVec *src);             /* copies x, y, z */
extern void Vec3_Lerp(EftRVec *out, EftRVec *a, EftRVec *b, f32 t); /* a + (b - a) * t */
extern f32 Vec3_Dist(EftRVec *a, EftRVec *b);                  /* distance */
extern f32 Rand_FloatRange(f32 a, f32 b);

extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern void *BtlTask_CreateChildList(EftRTask *task, s32 count, s32 workSize);
extern EftRTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void BtlTask_SetDead(EftRTask *task);                 /* kills the task */
extern void BtlTask_SetOwnerTag(EftRTask *task, s32 bits);       /* 0x800 / 0x1000: task of character 0 / 1 */
extern EftRTask *BtlTask_GetParent(EftRTask *task);            /* the manager task */
extern s64 EftVram_AddImage(EftRTexAnim *tex, s32 a, s32 b);
extern s64 EftVram_AddClut(EftRTexAnim *tex);

extern u64 *Battle_GetWork(void);
extern void BtlScene_Reset(s32 mode);
extern s32 BtlScene_IsEffectStopped(s32 objId, s32 kind);
extern s32 BtlScene_IsEffectHidden(s32 objId, s32 kind);
extern s32 BtlScene_IsAnyCharStopped(void);
extern f32 BtlScene_GetCharScale(s32 chr);
extern s32 *BtlScene_GetCharPackEntry(s32 chr, s32 idx);
extern void *BtlScene_GetPackEntry(s32 *base, s32 idx);
extern f32 BtlStage_GetBottom(void);

extern void BtlCharApi_GetNodePos(s32 objId, s32 node, EftRVec *out);
extern void BtlCharApi_GetPos(s32 objId, EftRVec *out);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern s32 BtlCharApi_IsLockedOn(s32 objId);
extern s32 BtlCharApi_IsChargingKiBlast(s32 objId);
extern s32 BtlCharApi_IsInClashA(s32 objId);
extern f32 BtlCharApi_GetClashBias(void);
extern void BtlCharApi_GetDeflectDir(s32 objId, EftRVec *out);
extern void BtlCharApi_PlaySoundAt(EftRVec *pos, s32 kind, s32 id, f32 near, f32 far);

extern void EftTechEvt_RequestExpire(s32 objId);
extern s32 ScrWarp_Spawn(s32 view, EftRVec *pos, f32 seconds, f32 radius, f32 width, f32 speed, f32 jitter);
extern f32 EftMath_WrapAngle(f32 angle);
extern void EftAim_Home(EftRVec *out, EftRVec *pos, EftRVec *dir, f32 speed, f32 maxTurn, s32 objId);
extern EftRRec *EftHit_GetNew(void);
extern void EftHit_Add(EftRRec *rec);
extern EftRSphere *EftHitArena_AllocSphere(void);
extern void EftHit_SetShapeSpheres(EftRRec *rec, EftRSphere *a, EftRSphere *b);
extern void ColSphere_Set(EftRSphere *sphere, EftRVec *pos, f32 radius);

extern void EftEmit_LoadSet(void *arg, void *set, s32 a2, s32 *pack, s32 a4, s32 a5);
extern void EftEmit_FreeSet(void *set);
extern void EftEmit_BeginFrame(void *set);
extern s32 EftEmit_GetEndFrames(EftRSet *set);
extern void EftEmit_InitState(EftRSet *set, EftRState *state);
extern void EftEmit_TermState(EftRSet *set, EftRState *state);
extern s32 EftEmit_GetFlagsFromMask(EftRSet *set, EftRState *state, s32 objId, s32 part, s32 sub, s32 end, s32 fast,
                                    s32 mask);
extern s32 EftEmit_GetResetFlags(EftRSet *set, EftRState *state, s32 part, s32 sub);
extern void EftEmit_Spawn(EftRSet *set, EftRState *state, EftRNodes *nodes, EftRVec *pos, EftRVec *dir, s32 objId,
                          s32 node, s32 arg7, s32 part, s32 sub, s32 flags, f32 scale);
extern void EftEmit_KillAll(EftRSet *set, EftRState *state);
extern s32 EftEmit_UpdateAlive(EftRSet *set, EftRState *state);
extern void EftEmit_SetNode(EftRNodes *nodes, s32 slot, s32 node, EftRVec *pos);
extern void EftEmit_RefreshFixedNodes(s32 objId, EftRNodes *nodes);
extern f32 EftEmit_GetTrailWidth(EftRState *state);
extern s32 EftEmit_HasWidth2(EftRSet *set);
extern f32 EftEmit_GetWidth2(EftRState *state);

extern void EftChar_SetList(s32 chr, s32 kind, void *list);  /* registers a sub-manager's child list */
extern void *EftChar_GetList(s32 objId, s32 kind);           /* the child list of a sub-manager */
extern s32 EftImpact_SpawnBlast(EftRBlastFx arg, f32 scaleA, f32 scaleB); /* explosion effect */
extern void EftGndDust_SpawnImpact(s32 objId, EftRVec *pos, f32 scale); /* ground impact effect */
extern void EftCharSlot_Set0(s32 objId, EftRTask *task);      /* per-fighter task slots (0x19BA98..0x19BC58) */
extern void EftCharSlot_Clear0(s32 objId);
extern EftRTask *EftCharSlot_Get0(s32 objId);
extern void EftCharSlot_Set1(s32 objId, EftRTask *task);
extern void EftCharSlot_Clear1(s32 objId);
extern EftRTask *EftCharSlot_Get1(s32 objId);
extern EftRTask *EftCharSlot_Get3(s32 objId);
extern s32 EftObj_Create(void *buf, void *model);          /* creates a model instance; -1 when none is free */
extern void EftObj_Destroy(s32 handle);                     /* frees it */
extern void EftObj_SetMtx(s32 handle, EftRMtx *mtx);       /* sets its matrix */
extern void EftObj_SetVisible(s32 handle, s32 shown);
extern s32 EftKiObj_Step(EftRTask *task);                  /* motion of the type 2 object (next file) */

extern EftRClass gEftStruggleClass;
extern EftRClass gEftClashSparkClass;
extern EftRClass gEftChargeClass;
extern EftRClass gEftKiBlastClass;
extern EftRClass gEftBlastChargeClass;
extern EftRClass gEftKiBombClass;


#define EFT_TASK_IS_DEAD(task) ((u8)((task)->flags & 1))

/* Work of the task EftCharaFx_Stop ends (module 0x174348..0x174A70, not in this file). */
typedef struct EftCharaFxWork {
    /* 0x000 */ u8 unk0[0x830];
    /* 0x830 */ u32 flags;   /* 1 active, 2 ending */
} EftCharaFxWork;

/* Asks the fighter's "chara fx" task to end. Returns 1 when it was running. */
s32 EftCharaFx_Stop(s32 objId);

/* ---- beam struggle ------------------------------------------------------------------------------------------ */

/* Starts the struggle between two technique records that met head-on (called by the hit pass, 0x1B0910, after it
   set task flag 0x100 on both). The task gets copies of both records, object 0's first. Returns how far along the
   line between the two start points record 0 got. */
f32 EftStruggle_Start(EftRVec *pos, EftRRec *a, EftRRec *b);

/* Whether a struggle task exists. */
s32 EftStruggle_IsActive(void) {
    if (gEftStruggle == NULL) {
        return 0;
    }
    return gEftStruggle->list->first != NULL;
}

/* Ends the struggle (BtlClash_UpdateA). winner 0 / 1: the other fighter's technique timers are expired and its
   effect layer is reset (scene layer 2 + character), which kills its beam; -1: both. */
void EftStruggle_End(s32 winner);

/* Sets where the struggle point is between the two fighters, clamped to 0..1 (no caller: the task recomputes it
   from BtlCharApi_GetClashBias every frame). */
void EftStruggle_SetBias(f32 bias);

/* The struggle point's place between the fighters, 0 when there is none (no caller). */
f32 EftStruggle_GetBias(void);

/* Copies the struggle point (no caller). */
void EftStruggle_GetPos(EftRVec *out);

/* Moves the struggle point (no caller). */
void EftStruggle_SetPos(EftRVec *pos);

/* Camera distance of the struggle's orbit cut for a fighter (BtlClash_SetOrbitCut): mode 0 gives
   (20 + 5 * power) * body scale with the power at least 0.5; modes 1 and 2 give 0. */
f32 EftStruggle_GetCamDist(s32 objId, s32 mode);

/* Camera distance of the struggle's middle cut (BtlClash_SetMidCut): 40 + 20 * the larger power. */
f32 EftStruggle_GetMidDist(void);

/* Sets one side's power and object id (the index), and the larger of the two powers (no caller). */
void EftStruggle_SetPower(s32 side, f32 power);

/* One side's power (no caller). */
f32 EftStruggle_GetPower(s32 side);

/* Manager init: the globals and a child list of one task. */
void EftStruggleMgr_Init(EftRTask *task);

/* Manager term. */
void EftStruggleMgr_Term(void);

/* Manager update: nothing. */
void EftStruggleMgr_Update(void);

/* Task init: keeps the two records, publishes both sides' powers (technique definition +0x88), places the
   struggle point from the fighters' clash bias and starts the spark there. */
/* The comparison of the two radii decides nothing: both arms of the `if` hold the same code (each with its own
 * locals), the compiler merges them after register allocation and only the compare is left. The arms must hold the
 * whole block, down to maxPower, with block-local variables: that is what makes the sources and definitions
 * block-local values (v0 / a1 / v1 / a2). */
void EftStruggle_Init(EftRTask *task, EftStruggleArg *arg);

/* Task term: lets the spark end. */
void EftStruggle_Term(EftRTask *task);

/* Task update: steps unless the battle is paused (battle flag 0x100). */
void EftStruggle_Update(EftRTask *task);

/* Task reset: dies. */
void EftStruggle_Reset(EftRTask *task);

/* Task draw: nothing. */
void EftStruggle_Draw(void);

/* Radius of a record's current volume (sphere or box). */
f32 EftStruggle_GetRecRadius(EftRRec *rec);

/* One frame of the struggle: ends when either fighter left clash A; otherwise moves the struggle point to the
   clash bias and writes each beam's head (its task's hit position) at power * definition +0x30 * 13 from the point
   towards that beam's start. */
void EftStruggle_Step(EftRTask *task);

/* ---- clash spark -------------------------------------------------------------------------------------------- */

/* Steps the emitters of the set and spawns their particles at the spark. */
void EftClashSpark_SpawnParts(s32 objId, EftRTask *task, EftRSet *set);

/* The emitter set of a spark kind (there is one). */
EftRSet *EftClashSpark_GetSet(s32 kind);

/* Node slots a spark kind uses (bit per slot): slot 0. */
s32 EftClashSpark_GetNodeMask(s32 kind);

/* Task init. */
void EftClashSpark_Init(EftRTask *task, EftClashSparkArg *arg);

/* Task term. */
void EftClashSpark_Term(EftRTask *task);

/* Task update: spawns the particles; once asked to end, dies after the set's end frames. */
void EftClashSpark_Update(EftRTask *task);

/* Task post-update (from the second frame on): refreshes which particles are alive and clears the phase mask. */
void EftClashSpark_PostUpdate(EftRTask *task);

/* Task reset: destroys the particles once and dies. */
void EftClashSpark_Reset(EftRTask *task);

/* Task draw: nothing. */
void EftClashSpark_Draw(void);

/* Manager init: the set (common effect file 0x268) and a child list of three sparks. */
void EftClashSparkMgr_Init(EftRTask *task);

/* Manager term. */
void EftClashSparkMgr_Term(void);

/* Manager update: steps the set. */
void EftClashSparkMgr_Update(void);

/* Manager reset: nothing. */
void EftClashSparkMgr_Reset(void);

/* Creates a spark; NULL when the three tasks are in use. */
EftRTask *EftClashSpark_Create(EftClashSparkArg arg);

/* Asks a spark to end. Returns 1 when it was running. */
s32 EftClashSpark_Stop(EftRTask *task);

/* Moves a spark. */
s32 EftClashSpark_SetPos(EftRTask *task, EftRVec *pos);

/* Sets a spark's size. */
s32 EftClashSpark_SetScale(EftRTask *task, f32 scale);

/* ---- charge aura (fighter effect requests 7 and 8) ---------------------------------------------------------- */

/* Steps the emitters of the set and spawns their particles at the fighter's node 3, pointing up. */
void EftCharge_SpawnParts(s32 objId, EftRTask *task, EftRSet *set);

/* Task init. */
void EftCharge_Init(EftRTask *task, s32 *arg);

/* Task term: releases the emitter state and the fighter's task slot. */
void EftCharge_Term(EftRTask *task);

/* Task update: follows node 3; request 8 adds the burst emitters and one screen shock wave; once asked to end,
   dies after the set's end frames. */
void EftCharge_Update(EftRTask *task);

/* Task reset: destroys the particles once and dies. */
void EftCharge_Reset(EftRTask *task);

/* Task post-update (from the second frame on): notes whether a particle is alive, clears the phase mask. */
void EftCharge_PostUpdate(EftRTask *task);

/* Task draw: nothing. */
void EftCharge_Draw(void);

/* Manager init: loads the set from entry 2 of the character's effect pack, makes room for four tasks. */
void EftChargeMgr_Init(EftRTask *task, s32 *arg);

/* Manager term. */
void EftChargeMgr_Term(EftRTask *task);

/* Manager update: steps the set. */
void EftChargeMgr_Update(EftRTask *task);

/* Fighter effect request 7 is set and the fighter has no aura: starts one. Returns 1 when a task was created. */
s32 EftCharge_Start(s32 *arg);

/* Fighter effect request 8: the aura's burst. */
s32 EftCharge_Burst(s32 objId);

/* Request 7 ended: asks the aura to end. */
s32 EftCharge_Stop(s32 objId);

/* Whether the fighter has an aura task. */
s32 EftCharge_IsActive(s32 objId);

/* ---- ki blast ----------------------------------------------------------------------------------------------- */

/* Publishes this frame's hit record: two spheres at the current and the previous position, radius = the blast's
   radius x the emitter state's trail width. The ki blast never steps that animation (EftEmit_UpdateTrailWidth is
   not called), so the factor stays at the set header's first width. EftHit_Add then takes the owner, the kind's
   class, the speed and the clash level from the argument block (rec->atk). */
void EftKiBlast_AddHitRecord(EftRTask *task);

/* The fighter the blast reached knocked it away (task flag 0x40) or sent it back (0x80): the blast gets a new
   direction from that fighter (BtlCharApi_GetDeflectDir: two draws of the fighter generator) and that fighter
   becomes its owner. Deflected: homing off, and no later deflection or reflection is taken. Reflected: the
   lifetime starts again and homing (if it had it) now steers at the new owner's opponent. */
void EftKiBlast_Turn(EftRTask *task, EftKiBlast *w);

/* Steps the emitters of the set and spawns their particles at the blast; reset: the flags of an emitter restart. */
void EftKiBlast_SpawnParts(s32 objId, EftRTask *task, EftRSet *set, s32 reset);

/* Sets bit 0x80 in the state flags of every emitter of group 17 (the trail). */
void EftKiBlast_EndTrail(s32 objId, EftRTask *task, EftRSet *set);

/* Task init: the blast starts at the model node of the argument, flying along the argument's direction (not
   normalised here); the "previous" position starts at the owner's node 0x11, so the first swept volumes reach back
   to the body. It homes when its owner is locked on at this moment. If the set header has flag 4 the speed is
   replaced by the state's second width, which is still 0 at this point (the state is initialised after): such a
   blast would not move. */
void EftKiBlast_Init(EftRTask *task, EftRArg *arg);

/* Task term. */
void EftKiBlast_Term(EftRTask *task);

/* Task update, skipped while the owner's effects are stopped: homing turn (EftAim_Home, every frame from the
   first), one step of `speed` along the direction (not on the first frame, not once stopped or ending), the
   lifetime, the particles, and the hit record while the blast is neither ending nor ended. With a lifetime of n
   frames the blast publishes n - 1 records; then the end animation runs for the set's end frames + 2 and the task
   dies. */
void EftKiBlast_Update(EftRTask *task);

/* Task reset: destroys the particles once and dies. */
void EftKiBlast_Reset(EftRTask *task);

/* Task post-update: reacts to what the hit pass reported. Any end result (hit, guarded, stage, lost clash, left
   the stage, absorbed): the blast stops at the reported position and starts its end. Deflected / reflected (once
   deflected, never again): EftKiBlast_Turn, and it goes on from the reported position. */
void EftKiBlast_PostUpdate(EftRTask *task);

/* Task draw: only asks whether the owner's effects are hidden (the particles draw themselves). */
void EftKiBlast_Draw(EftRTask *task);

/* Manager init (sub-manager kinds 1 and 2): kind 1 loads entry 3 of the character's effect pack and makes room for
   20 blasts, kind 2 entry 4 and 10 blasts. */
void EftKiBlastMgr_Init(EftRTask *task, s32 *arg);

/* Manager term. */
void EftKiBlastMgr_Term(EftRTask *task);

/* Manager update: steps the set. */
void EftKiBlastMgr_Update(EftRTask *task);

/* Launches one ki blast (BtlFx_FireKiBlast, once per shot of the volley): a task in the owner's list of
   kind 1 (ki blast type 0) or 2 (any other type). Nothing happens when the list is full. */
void EftKiBlast_Fire(EftRArg arg);

/* Returns 1 (no caller). */
s32 EftKiBlast_Ret1A(void);

/* Returns 1 (no caller). */
s32 EftKiBlast_Ret1B(void);

/* ---- ki blast charge glow (fighter effect request 0x17) ----------------------------------------------------- */

/* Steps the emitters of the set and spawns their particles at the node. */
void EftBlastCharge_SpawnParts(s32 objId, EftRTask *task, EftRSet *set);

/* Task init. */
void EftBlastCharge_Init(EftRTask *task, EftBlastChargeArg *arg);

/* Task term: releases the emitter state and the fighter's task slot. */
void EftBlastCharge_Term(EftRTask *task);

/* Task update: follows the node while the fighter is charging a ki blast; afterwards one more particle step with
   the end flag, then dies. */
void EftBlastCharge_Update(EftRTask *task);

/* Task reset: dies. */
void EftBlastCharge_Reset(EftRTask *task);

/* Task post-update (from the second frame on): refreshes which particles are alive, clears the phase mask. */
void EftBlastCharge_PostUpdate(EftRTask *task);

/* Task draw: nothing. */
void EftBlastCharge_Draw(void);

/* Manager init (sub-manager kind 3): the set from entry 4 of the character's effect pack, ten tasks. */
void EftBlastChargeMgr_Init(EftRTask *task, s32 *arg);

/* Manager term. */
void EftBlastChargeMgr_Term(EftRTask *task);

/* Manager update: steps the set. */
void EftBlastChargeMgr_Update(EftRTask *task);

/* Fighter effect request 0x17 (BtlFx_SpawnHitSparkReq17): starts the glow. Returns 1 when a task was created. */
s32 EftBlastCharge_Start(EftBlastChargeArg *arg);

/* Asks the fighter's glow to end (no caller: the task ends by itself). */
s32 EftBlastCharge_Stop(s32 objId);

/* ---- ki bomb (ki blast type 3) ------------------------------------------------------------------------------ */

/* Publishes this frame's hit record: two spheres of the bomb's radius (5, or 28 while it explodes). */
void EftKiBomb_AddHitRecord(EftRTask *task);

/* Places the bomb at its node and throws it: the argument's direction with a jitter from the VU0 generator
   (x and z +-0.2, y up to 0.3 upwards), normalised, times the speed. The spin rate (27..37 degrees per frame,
   either sense) comes from libc rand(). Creates the model instance. */
void EftKiBomb_Launch(EftRTask *task);

/* Task init. */
void EftKiBomb_Init(EftRTask *task, EftRArg *arg);

/* Task term: frees the model instance. */
void EftKiBomb_Term(EftRTask *task);

/* Task update, unless any character is stopped: moves, publishes the hit record, dies when the blast is over. */
void EftKiBomb_Update(EftRTask *task);

/* Task reset: dies. */
void EftKiBomb_Reset(EftRTask *task);

/* Task post-update. */
void EftKiBomb_PostUpdate(EftRTask *task);

/* Task draw. */
void EftKiBomb_Draw(EftRTask *task);

/* Manager init (replaces sub-manager kind 2 for a character with a type 3 ki blast): the model from entry 1 of
   entry 4 of the character's effect pack, ten tasks. */
void EftKiBombMgr_Init(EftRTask *task, s32 *arg);

/* Manager term. */
void EftKiBombMgr_Term(EftRTask *task);

/* Manager update: nothing. */
void EftKiBombMgr_Update(void);

/* Launches a type 3 ki blast (BtlFx_FireKiBlast): TWO bombs per shot, in the owner's list of kind 2. */
void EftKiBomb_Fire(EftRArg arg);

/* Called by the hit pass through EftHit_NotifyBlastTask when a blast record hit the stage: keeps the contact
   (0x40 bytes of the record's collision result; the last vector is the surface normal) if the task is a bomb. */
void EftKiBomb_SetContact(EftRTask *task, EftRMtx *mtx);

/* out = v mirrored on the plane with the given normal, normalised. */
void EftKiBomb_Reflect(EftRVec *out, EftRVec *v, EftRVec *normal);

/* One frame of flight: position += velocity, velocity.y += gravity. The bomb explodes after 300 frames, below the
   stage bottom, within 28 of the opponent, or (once it lies on the ground) when the argument's lifetime has run
   out; the explosion is a 15-frame hit record of radius 28. Returns 1 on the frame the explosion ends. */
s32 EftKiBomb_Move(EftRTask *task);

/* Post-update: shows or hides the model, then reacts to the hit pass. Guarded: explodes next frame without a hit
   record. Hit a fighter: explodes next frame. Hit the stage or the stage boundary: bounces (mirrored on the
   contact normal, or on the direction to the stage axis at the boundary; speed and spin halved) up to three times,
   then lies where it landed, at one of three fixed angles picked with libc rand(). */
void EftKiBomb_HandleHits(EftRTask *task);

/* Draw: the model's matrix: scale 3.5 x size, the spin angle, 1.5 below the bomb's position (+y is down). */
void EftKiBomb_UpdateModel(EftRTask *task);

/* ---- thrown object (ki blast type 2), first half ------------------------------------------------------------ */

/* Publishes this frame's hit record: two spheres of radius 5 x the argument's radius. */
void EftKiObj_AddHitRecord(EftRTask *task);

/* Deflection / reflection of the object (called by the next file's post-update): as EftKiBlast_Turn; the new
   direction replaces the velocity. */
void EftKiObj_Turn(EftRTask *task, EftKiObj *w);

/* Places the object at its node and throws it along the argument's direction (no jitter); spin rate from libc
   rand(). Creates the model instance. */
void EftKiObj_Launch(EftRTask *task);

/* Builds the GS TEX0 value of a texture header once. */
void EftKiObj_StepTex(EftRTexAnim *tex);

/* Task init. */
void EftKiObj_Init(EftRTask *task, EftRArg *arg);

/* Task term: frees the model instance. */
void EftKiObj_Term(EftRTask *task);

/* Task update, unless any character is stopped: moves (next file), publishes the hit record, dies or readies the
   texture. */
void EftKiObj_Update(EftRTask *task);
