#include "common.h"
#include "battle/eft_k.h"

/*
 * Effect scene, layer 1 (technique effects), 0x157398..0x15C728 (the former eft_l.c, 0x15B550..0x15C728, is
 * appended as the second part: EftRushShot_UpdateAttached only matches with EftRushShot_UpdateModels defined
 * earlier in its file). The first part, 0x157398..0x15B550, is four pieces, in address order:
 *
 *   0x157398..0x158438  second half of the "shots" technique module EftShotTech (effect type 2; the first half,
 *                       0x156450.., is in eft_j.c). Classes gEftShotTechMgrClass / gEftShotTechClass.
 *   0x158438..0x159130  technique events EftTechEvt: per fighter and per frame, a word of event bits that every
 *                       technique module reads through EftShot_TestBits(objId, mask), and the two timers of a
 *                       technique. Classes gEftTechEvtClass (a sub-task of layer 1) / gEftTechEvtTaskClass.
 *   0x159130..0x15AB38  the "thrown object" technique module EftObjTech (effect type 8). Classes
 *                       gEftObjTechMgrClass / gEftObjTechClass.
 *   0x15AB38..0x15B550  first three helpers of the "rush shot" module EftRushShot (effect type 9, second part).
 *
 * A technique module is two task classes: a manager (one per shot slot, created by EftShot_CreateSlotTask from the
 * class table at 0x2C3700, row = definition effect type + 1) whose work holds the emitter set, and items (a child
 * list of two) created by EftShot_Start when the fighter starts the technique. An item's init receives the shot
 * slot (EftKSrc). Callback order in a class: update, init, term, post-update, reset, draw.
 *
 * The float pool of the first part is 0x2FC7D4..0x2FC828 (21 constants, all checked against the original bits); the
 * second part's follows (to 0x2FC838), and the whole is contiguous with the pool of eft_j.c.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);
extern f32 sqrtf(f32 x);
extern f32 sinf(f32 x);
extern f32 atan2f(f32 y, f32 x);
extern f32 Mathf_Asin(f32 x);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *src);
extern void Mtx_AxisZToEuler(Vec4 *angles, Mtx44 *m);
extern void Mtx_Translate(Mtx44 *dst, Mtx44 *src, Vec4 *pos);
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateZXY(Mtx44 *dst, Mtx44 *src, Vec4 *angles);
extern void Mtx_RotateXYZ(Mtx44 *dst, Mtx44 *src, Vec4 *angles);
extern void Mtx_ScaleDiagUniform(Mtx44 *dst, Mtx44 *src, f32 scale);
extern void Vec3_Copy(Vec4 *dst, Vec4 *src);
extern void Vec3_Clamp(Vec4 *dst, Vec4 *src, f32 a, f32 b);
extern void Vec3_ScaleAdd(Vec4 *dst, Vec4 *dir, f32 len, Vec4 *from);

extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 BtlScene_GetCharCount(void);
extern s32 BtlScene_IsCharStopped(s32 objId);
extern s32 BtlScene_IsEffectHidden(s32 objId, s32 kind);
extern s32 *BtlScene_GetPackEntry(s32 *base, s32 idx);
extern s32 *BtlScene_GetCharPackEntry(s32 side, s32 idx);
extern f32 BtlScene_GetCharScale(s32 chr);
extern void *BtlTask_CreateChildList(EftKTask *task, s32 count, s32 workSize);
extern void *BtlTaskList_AddTail(void *list, void *cls, void *arg);

extern s32 BtlCharApi_GetAuraType(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern void BtlCharApi_GetNodeMtx(s32 objId, s32 node, Mtx44 *out);
extern s32 BtlCharApi_IsInTechnique(s32 objId);
extern s32 BtlCharApi_IsRushConnected(s32 objId);
extern s32 BtlCharApi_IsInRushSequence(s32 objId);
extern s32 BtlCharApi_IsInSkill(s32 objId);
extern s32 BtlCharApi_IsSkillApplied(s32 objId);
extern s32 BtlCharApi_TestAnimFlag10(s32 objId);
extern s32 BtlCharApi_ObjTestAttr(s32 objId, u64 mask);
extern void BtlCharApi_SetHeldFlagA7(s32 objId);

extern EftKTask *BtlTask_GetParent(EftKTask *task);
extern void BtlTask_SetDead(EftKTask *task);
extern void BtlTask_SetOwnerTag(EftKTask *task, s32 flags);
extern void EftTexSet_Keep32(void *tex, s32 a1, s32 a2);
extern void EftTexSet_Load32(void *tex, s32 *entry);
extern s32 EftShot_TestBits(s32 objId, s32 bits);
extern void EftShot_SetHeldFlagA8(s32 objId);
extern void EftShot_Nop(s32 size);
extern void EftEmit_LoadSet(EftKSrc *src, void *set, s32 a2, s32 *pack, s32 t0, s32 t1);
extern void EftEmit_FreeSet(void *set);
extern void EftEmit_BeginFrame(void *set);
extern u8 EftEmit_GetHead21(void *set);
extern u8 EftEmit_GetHead26(void *set);
extern u8 EftEmit_GetHead22(void *set);
extern f32 EftEmit_GetHead28(void *set);
extern u8 EftEmit_GetEndFrames(void *set);
extern void EftEmit_InitState(void *set, void *emit);
extern void EftEmit_TermState(void *set, void *emit);
extern s32 EftEmit_GetFlagsFromReq(EftKSet *set, void *emit, s32 objId, s32 group, s32 part, s32 f1, s32 f8);
extern void EftEmit_SpawnOwn(EftKSet *set, void *emit, Vec4 *nodes, Vec4 *pos, void *work, s32 group, s32 part,
                          s32 res, f32 scale);
extern void EftEmit_MarkKind6(void *set, void *emit);
extern void EftEmit_KillAll(void *set, void *emit);
extern s32 EftEmit_UpdateAlive(void *set, void *emit);
extern void EftEmit_UpdateNodesReq(EftKSrc *src, Vec4 *nodes);
extern void EftEmit_UpdateTrailWidth(void *set, void *emit);
extern f32 EftEmit_GetTrailWidth(void *emit);
extern s32 EftEmit_HasWidth2(void *set);
extern void EftEmit_UpdateWidth2(void *set, void *emit);
extern f32 EftEmit_GetWidth2(void *emit);
extern void EftShotTech_InitModel(EftKTask *task);
extern void EftShotTech_SetModelPose(EftKTask *task, Vec4 *pos, Vec4 *angles);
extern void EftShotTech_FreeModel(EftKTask *task);
extern void EftShotTech_CalcDir(EftKTask *task, Vec4 *dir);
extern s32 EftShotTech_ReapShots(EftKTask *task);
extern s32 EftShotTech_UpdateShots(s32 objId, EftKTask *task);
extern void EftShotTech_UpdateParts(s32 objId, EftKTask *task, void *set);
extern void EftShotTech_Start(EftKTask *task, s32 evt);
extern void EftShotTech_UpdateFlash(EftKTask *task);
extern void EftShotTech_UpdateNodeFx(EftKTask *task);
extern void EftShotTech_UpdateBlur(EftKTask *task);
extern void EftShotTech_UpdateSubs(EftKTask *task);
extern EftKHitRec *EftHit_GetNew(void);
extern void EftHit_Add(EftKHitRec *rec);
extern void *EftHitArena_AllocSphere(void);
extern void *EftHitArena_AllocBox(void);
extern void EftHit_SetShapeSpheres(EftKHitRec *rec, void *a, void *b);
extern void EftHit_SetShapeBoxes(EftKHitRec *rec, void *a, void *b);
extern void EftCam_Start(EftKCamArg *arg);
extern void EftCam_Stop(void);
extern f32 EftMath_WrapAngle(f32 angle);
extern void EftAim_GetDir(Vec4 *dir, Vec4 *from, s32 objId);
extern void EftAim_GetDirKeep(EftKSrc *src, Vec4 *dir, Vec4 *from, s32 objId);
extern void EftAim_Home(Vec4 *out, Vec4 *from, Vec4 *dir, s32 objId, f32 speed, f32 homing);
extern void EftGlow_Request(s32 objId, s32 a1);
extern void EftStreak_Stop(void *sub);
extern void EftGndDust_SpawnLandingScaled(s32 objId, Vec4 *pos, Vec4 *dir, f32 a, f32 b);
extern void *EftOrbTail_Create(s32 objId, s32 auraType);
extern void EftOrbTail_Burst(void *fx);
extern void EftOrbTail_Kill(void *fx);
extern void EftOrbTail_SetPos(void *fx, Vec4 *pos);
extern void EftMesh_Init(void *ring, s32 *model);
extern void EftMesh_SetTex(void *ring, void *tex);
extern void EftMesh_SetMtx(void *ring, Mtx44 *m);
extern void EftMesh_Copy(void *ring, void *proto);
extern void EftMesh_SetLayer(void *ring, s32 a1);
extern void EftMesh_SetTexBase(void *ring, s32 a1);
extern void EftMesh_SetOwner(void *ring, s32 objId, s32 a2);
extern void EftMesh_Draw(void *ring);
extern s32 EftObj_Create(void *arg, s32 *pack);
extern void EftObj_Destroy(s32 objId);
extern void EftObj_SetMtx(s32 objId, Mtx44 *m);
extern void EftObj_SetVisible(s32 objId, s32 on);
extern void EftObj_Nop(s32 objId, s32 a1);
extern void ColSphere_Set(void *sphere, Vec4 *pos, f32 radius);
extern void ColCapsule_Set(void *box, Vec4 *a, Vec4 *pos, f32 size);

extern const EftKVec D_002ECB60; /* {0, -1, 0, 1}: a local initialiser of EftShotTech_UpdateTargetBurst */
extern s32 gEftTechEvtTaskClass[6];        /* class of the timeline task */

/* ---- "shots" technique module, second half ---- */

/* Events 0x100 / 0x200 of the fighter create / destroy an aura-coloured effect held between nodes 10 and 14. */
void EftShotTech_UpdateAuraBall(EftKTask *task);

/* With definition flag 0x400: when the opponent gets event 4, starts an upward effect at the opponent's node 3. */
void EftShotTech_UpdateTargetBurst(EftKTask *task);

/* On event 0x20, records the direction and position of node 0x36 for shots fired from it. */
void EftShotTech_UpdateMuzzle(EftKTask *task);

/* Once the rush has connected (flag 0x800): starts the effect scene's camera cut for this technique.
   The argument is built in one block and copied to a second one that is passed: the original passed the 12-byte
   struct by value (this ABI passes the address of a copy). */
void EftShotTech_StartCam(EftKTask *task);

/* Aim kind 0: the target point flies on with the velocity (or sits on the opponent's node 3) until the
   opponent's event 0x40. */
void EftShotTech_MoveStraight(EftKTask *task, s32 toTarget);

/* Aim kind 1: flies with the velocity, then (event 0x10) sits at a fixed distance in front of the opponent on the
   line to the fighter; event 0x20 makes it grow to twice the size; the opponent's event 0x40 ends it. */
void EftShotTech_MoveFromTarget(EftKTask *task, s32 wait);

/* Aim kind 2: the target point is 30 past the opponent's node 3 on the line from the launch node; after event
   0x10 it is 30 (18 for effect 0x2B4) along the line to the fighter's own node 0x1F. Stores the direction. */
void EftShotTech_MoveAimed(EftKTask *task);

/* After the rush connected: runs the per-frame effect helpers and, between events 0x10 and 0x20, keeps the model
   object at node 0x36 pointing against the direction. */
void EftShotTech_UpdateConnected(EftKTask *task);

/* Item init: clears the 0x900-byte work, reads speed and scale from the definition and the aim kind from the
   emitter set's header, creates the model when the manager loaded one. */
void EftShotTech_Init(EftKTask *task, EftKSrc *src);

/* Item term: destroys the model, the eight sub-effects and the aura effect, frees the emitter state and sets the
   fighter's held flag 0xA8. */
void EftShotTech_Term(EftKTask *task);

/* Item update: the state machine driven by the fighter's technique events (2 start, 4 fire, 8 end, 0x400 abort). */
void EftShotTech_Update(EftKTask *task);

/* Item post-update: steps the emitters and the shots unless time is stopped for the fighter. */
void EftShotTech_PostUpdate(EftKTask *task);

/* Item reset: the task dies. */
void EftShotTech_Reset(EftKTask *task);

/* Item draw: nothing. */
void EftShotTech_Draw(EftKTask *task);

/* Manager init: loads the emitter set from the effect's pack, creates the list of two items, and looks up the
   three camera packs of the character's pack 8 and the model. */
void EftShotTechMgr_Init(EftKTask *task, EftKSrc *src);

/* Manager term: frees the emitter set. */
void EftShotTechMgr_Term(EftKTask *task);

/* Manager update: per-frame start of the emitter set. */
void EftShotTechMgr_Update(EftKTask *task);

/* Manager reset: nothing. */
void EftShotTechMgr_Reset(EftKTask *task);

/* ---- technique events ---- */

/* Event bits of a fighter this frame (0 when the layer does not exist). */
s32 EftTechEvt_GetEvents(s32 objId);

/* Starts the timeline of a technique: one task that turns the fighter's animation into event bits. */
void *EftTechEvt_Start(EftKSrc *src, s32 flagTime, s32 endTime);

/* The fighter's timers stop for good (the projectile hit); a pending END event is withdrawn. */
void EftTechEvt_RequestStop(s32 objId);

/* Restarts the fighter's end timer, unless the END event is already out. */
void EftTechEvt_RequestRestart(s32 objId);

/* Makes the fighter's end timer run out, unless the END event is already out. */
void EftTechEvt_RequestExpire(s32 objId);

/* Layer init: allocates the state and one entry per fighter, creates the list of timeline tasks. */
void EftTechEvt_Init(EftKTask *task);

/* Layer term. */
void EftTechEvt_Term(void);

/* Layer update (before its timeline tasks): clears every fighter's event bits. */
void EftTechEvt_Update(void);

/* Timeline init: keeps the argument; a kind-0 definition with any frame number uses the frame table. */
void EftTechEvtTask_Init(EftKTask *task, EftTechEvtArg *arg);

/* Timeline term: nothing. */
void EftTechEvtTask_Term(EftKTask *task);

/* Timeline update: produces this frame's events unless time is stopped for the fighter.
   Declared with a result it never sets: the original calls the two updaters with jal and falls into the epilogue,
   which this compiler only does in a non-void function (a void one gets two tail calls). */
s32 EftTechEvtTask_Update(EftKTask *task) {
    EftTechEvtTask *w = task->work;
    EftKSrc *src = w->arg.src;

    w->flags &= ~0x10;
    if (!BtlScene_IsCharStopped(src->objId)) {
        if (EftTechEvt_IsRushTech(src)) {
            EftTechEvtTask_UpdateRush(task);
        } else {
            EftTechEvtTask_UpdateNormal(task);
        }
    }
}

/* Timeline reset: the task dies. */
void EftTechEvtTask_Reset(EftKTask *task);

/* Timeline draw callback, first view of the frame only: applies the requests and steps the two timers. When the
   flag timer runs out the fighter's held flag 0xA7 is set. */
void EftTechEvtTask_Draw(EftKTask *task);

/* Events of an ordinary technique or skill: its own animation attributes (or frame table), and ABORT when the
   fighter is interrupted or leaves the technique / skill. The task dies on END or ABORT. */
void EftTechEvtTask_UpdateNormal(EftKTask *task);

/* Events of a rush technique: the animation attributes of EVERY fighter become that fighter's events (the victim
   plays its own animation). ABORT when the attacker leaves the technique or the rush sequence. */
void EftTechEvtTask_UpdateRush(EftKTask *task);

/* 1 for a rush technique: kind not 0 and either sub-kind 5 or the fighter is in the rush sequence. */
s32 EftTechEvt_IsRushTech(EftKSrc *src);

/* This frame's raw events of the fighter, as animation attribute bits. */
u64 EftTechEvtTask_CollectEvents(EftTechEvtTask *w);

/* The fighter's animation has flag 0x10 (BtlCharApi_TestAnimFlag10). */
s32 EftTechEvt_IsInterrupted(s32 objId);

/* The fighter is in a skill action. */
s32 EftTechEvt_IsInSkill(s32 objId);

/* The fighter is in a technique action. */
s32 EftTechEvt_IsInTechnique(s32 objId);

/* ---- "thrown object" technique module ---- */

/* Adds this frame's hit record: the body (or, on the target, the held block) with two spheres or two boxes
   scaled by the emitter's width. */
void EftObjTech_AddHitRecord(EftKTask *task);

/* Creates the model object from the manager's model pack, hidden. */
void EftObjTech_CreateModel(EftKTask *task);

/* Places the model: scale, Euler rotation, translation. */
void EftObjTech_SetModelPose(EftKTask *task, Vec4 *pos, Vec4 *angles);

/* Destroys the model object. */
void EftObjTech_DestroyModel(EftKTask *task);

/* Sets up the rings from the manager's prototype and gives each its roll, its offset (step apart) and its
   scale (1, growing by grow). */
void EftObjTech_InitRings(EftKTask *task, f32 roll, f32 step, f32 grow);

/* The same parameters without touching the ring objects. */
void EftObjTech_SetRingParams(EftKTask *task, f32 roll, f32 step, f32 grow);

/* Builds each ring's matrix: scaled (width on x and z, length on y), rotated by the angles with the ring's roll
   in x, placed at pos + direction * offset. */
void EftObjTech_PlaceRings(EftKTask *task, Vec4 *pos, Vec4 *angles, f32 width, f32 length);

/* Draws the rings. */
void EftObjTech_DrawRings(EftKTask *task);

/* Nothing to free for the rings. */
void EftObjTech_TermRings(EftKTask *task);

/* Runs the 19 emitter groups of the set: asks for each part what to do this frame (flag 1 = the object is ending,
   flag 8 = it was cut short) and starts or stops it at the body's head. Once the object has hit (0x400) the parts
   move to the position on the target, and a part with a life (unk18 > 0) is left to run out.
   endOnTarget, onTarget, objId and a loop pointer live on the stack in the original: the function uses all nine
   saved registers. */
void EftObjTech_UpdateEmitters(s32 objId, EftKTask *task, EftKSet *set);

/* Moves the object and its model according to the mode and the fighter's technique events. */
void EftObjTech_UpdateMotion(EftKTask *task);

/* Shows the model while it is in use (hidden when the effect scene hides effects of this fighter). */
void EftObjTech_UpdateModelVisible(EftKTask *task);

/* Item init: clears the 0x800-byte work, reads speed and scale from the definition, picks the mode from the
   effect id, creates the model and the rings. */
void EftObjTech_Init(EftKTask *task, EftKSrc *src);

/* Item term: destroys the model, frees the emitter state; a technique (kind not 0) sets held flag 0xA8. */
void EftObjTech_Term(EftKTask *task);

/* Item update: the state machine driven by the fighter's technique events (2 start, 4 fire, 8 end, 0x400 abort);
   while flying it homes, moves and adds a hit record every frame. */
void EftObjTech_Update(EftKTask *task);

/* Item post-update: applies what the hit pass wrote into the task (moved head, hit, end). A hit on a fighter
   stops the fighter's technique timers and pins the object on the target. */
void EftObjTech_PostUpdate(EftKTask *task);

/* Item reset: kills the emitters once, the task dies. */
void EftObjTech_Reset(EftKTask *task);

/* Item draw: the rings, once they are in use. */
void EftObjTech_Draw(EftKTask *task);

/* Manager init: loads the emitter set, creates the list of two items, looks up the model and the ring model. */
void EftObjTechMgr_Init(EftKTask *task, EftKSrc *src);

/* Manager term: frees the emitter set. */
void EftObjTechMgr_Term(EftKTask *task);

/* Manager update: per-frame start of the emitter set; animates the ring texture while it has items. */
void EftObjTechMgr_Update(EftKTask *task);

/* Manager reset: nothing. */
void EftObjTechMgr_Reset(EftKTask *task);

/* ---- "rush shot" module, first helpers ---- */

/* Adds this frame's hit record for the shot body. */
void EftRushShot_AddHitRecord(EftKTask *task);

/* Creates the swarm's model objects from the manager's model pack, hidden. */
void EftRushShot_CreateModels(EftKTask *task);

/* Places the swarm's models every frame. Mode 1: each model hovers around the centre (bobbing, spinning, sinking),
   and once the shot is released (flag 0x40000) follows it after its own delay; other modes: all models sit on the
   shot's head, turned along its direction. Appearance only, but it draws from libc rand(). */
void EftRushShot_UpdateModels(EftKTask *task);

/* ------------------------------------------------------------------------------------------------------------
 * Second part (formerly eft_l.c), with its own header and view types. Functions already declared above with
 * the first part's types are reached through cast macros.
 * ------------------------------------------------------------------------------------------------------------ */
#include "battle/eft_l.h"

/*
 * Technique effect type 9, the "rush shot", 0x15B550..0x15C728: everything of the module except its first three
 * helpers (EftRushShot_AddHitRecord, _CreateModels, _UpdateModels at 0x15AB38..0x15B550, the end of eft_k.c).
 * Classes: manager gEftRushShotMgrClass, task gEftRushShotClass (gEftShotClass row 10).
 *
 * What it is: the projectile of a rush technique. Technique events of the OWNER (EftShot_TestBits: 2 / 4 start,
 * 4 fire, 8 end, 0x400 abort) fire it from the set's start node towards the owner's aim; it flies at the
 * definition's speed (homing when the definition says so) and adds one hit record per frame. When the rush
 * connects (BtlCharApi_IsRushConnected) it stops flying and sits on the victim (node 3, or the owner's node
 * 0x36), starts the technique's camera cut, tints the stage, and from then on follows the technique events of
 * the VICTIM: stage blur (0x10 / 0x20), stage effects (0x80 / 0x100), screen flash and node sparks (0x40).
 *
 * Translation unit: EftRushShot_UpdateAttached only matches when EftRushShot_UpdateModels (0x15AD78) is defined
 * above it in the same file (a "beqz" becomes "beqzl" otherwise), so this file is the continuation of eft_k.c's
 * object. Checked by compiling eft_k.c with this file appended: all 18 functions match there.
 */

extern void *memset(void *dst, s32 c, u32 n);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 scale);
extern void Vec3_Copy(Vec4 *dst, Vec4 *src);

extern s32 BtlScene_IsCharStopped(s32 objId);
extern s32 *BtlScene_GetPackEntry(s32 *base, s32 idx);
extern s32 *BtlScene_GetCharPackEntry(s32 side, s32 idx);
#define BtlTask_CreateChildList ((void (*)(EftTask *task, s32 count, s32 workSize))BtlTask_CreateChildList)

extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern s32 BtlCharApi_IsRushConnected(s32 objId);

/* Argument of EftCam_Start. */
typedef struct EftRushShotMsg {
    s32 unk0;
    s32 objId;
    s32 id;
} EftRushShotMsg;

/* Argument of EftFlash_Start (screen flash). */
typedef struct EftFlashArg {
    /* 0x00 */ EftVec color;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 objId;
    /* 0x20 */ s32 unk20;
} EftFlashArg; /* size 0x30: the vector makes it 16-byte aligned */

/* Argument of EftDelaySe_Start: five (kind, node) pairs. */
typedef struct EftSparkTbl {
    s32 v[10];
} EftSparkTbl;

#define EftCam_Start ((void (*)(EftRushShotMsg *msg))EftCam_Start)
extern void EftCam_Stop(void);
extern f32 EftMath_WrapAngle(f32 angle);
#define EftAim_GetDir ((void (*)(void *dst, void *src, s32 objId))EftAim_GetDir)
#define EftAim_GetDirKeep ((void (*)(EftTechArg *arg, Vec4 *dir, Vec4 *pos, s32 objId))EftAim_GetDirKeep)
extern void EftAim_Home(Vec4 *dir, Vec4 *pos, Vec4 *dir2, s32 objId, f32 speed, f32 turn);
extern s32 EftShot_TestBits(s32 objId, s32 mask);
extern void EftShot_SetHeldFlagA8(s32 objId);
extern void EftShot_Nop(s32 size);
#define EftEmit_LoadSet ((void (*)(EftTechArg *arg, void *model, s32 a2, s32 *pack, s32 a4, s32 a5))EftEmit_LoadSet)
extern void EftEmit_FreeSet(void *model);
extern void EftEmit_BeginFrame(void *model);
#define EftEmit_GetEndFrames ((s32 (*)(EftModel *model))EftEmit_GetEndFrames)
#define EftEmit_InitState ((void (*)(void *model, EftModelInst *inst))EftEmit_InitState)
#define EftEmit_TermState ((void (*)(EftModel *model, EftModelInst *inst))EftEmit_TermState)
#define EftEmit_GetFlagsFromReq ((s32 (*)(EftModel *model, EftModelInst *inst, s32 objId, s32 part, s32 sub, s32 end, s32 fast))EftEmit_GetFlagsFromReq)
#define EftEmit_SpawnOwn ((void (*)(EftModel *model, EftModelInst *inst, void *nodes, Vec4 *pos, void *w, s32 part, s32 sub, s32 flags, f32 size))EftEmit_SpawnOwn)
#define EftEmit_MarkKind6 ((void (*)(EftModel *model, EftModelInst *inst))EftEmit_MarkKind6)
#define EftEmit_KillAll ((void (*)(EftModel *model, EftModelInst *inst))EftEmit_KillAll)
#define EftEmit_UpdateAlive ((s32 (*)(EftModel *model, EftModelInst *inst))EftEmit_UpdateAlive)
#define EftEmit_UpdateNodesReq ((void (*)(EftTechArg *arg, void *nodes))EftEmit_UpdateNodesReq)
#define EftEmit_UpdateTrailWidth ((void (*)(EftModel *model, EftModelInst *inst))EftEmit_UpdateTrailWidth)
#define EftEmit_HasWidth2 ((s32 (*)(EftModel *model))EftEmit_HasWidth2)
#define EftEmit_UpdateWidth2 ((void (*)(EftModel *model, EftModelInst *inst))EftEmit_UpdateWidth2)
#define EftEmit_GetWidth2 ((f32 (*)(EftModelInst *inst))EftEmit_GetWidth2)
extern void EftTechEvt_RequestStop(s32 objId);
#define EftRushShot_AddHitRecord ((void (*)(EftTask *task))EftRushShot_AddHitRecord)
#define EftRushShot_CreateModels ((void (*)(EftTask *task))EftRushShot_CreateModels)
#define EftRushShot_UpdateModels ((void (*)(EftTask *task))EftRushShot_UpdateModels)
extern void EftFlash_Start(EftFlashArg *arg);
extern s32 EftStreak_Start(s32 objId, s32 kind, s32 arg2, f32 angle);
#define EftStreak_Stop ((void (*)(s32 handle))EftStreak_Stop)
extern void EftDelaySe_Start(s32 objId, EftSparkTbl *tbl, s32 count);
extern void EftObj_Destroy(s32 handle);
#define BtlTask_SetDead ((void (*)(EftTask *task))BtlTask_SetDead)
#define BtlTask_SetOwnerTag ((void (*)(EftTask *task, s32 flag))BtlTask_SetOwnerTag)
#define BtlTask_GetParent ((EftTask *(*)(EftTask *task))BtlTask_GetParent)
extern void StgTint_Start(s32 a0, s32 a1, f32 time);
extern void StgBlur_SetCenter(s32 a0, Vec4 *pos, s32 a2);
extern void StgBlur_SetColor0Rgba(s32 a0, s32 r, s32 g, s32 b, s32 a);
extern void StgBlur_SetColor1Rgba(s32 a0, s32 r, s32 g, s32 b, s32 a);
extern void StgBlur_SetColor2Rgba(s32 a0, s32 r, s32 g, s32 b, s32 a);
extern void StgBlur_SetColor3Rgba(s32 a0, s32 r, s32 g, s32 b, s32 a);

extern const EftSparkTbl gEftRushShotSparkTbl;

/* Frees the swarm model objects EftRushShot_CreateModels made. */
void EftRushShot_FreeModels(EftTask *task);

/* Once the rush has connected, starts the technique's camera cut (EftCam_Start: animation, owner, effect id). */
void EftRushShot_StartCam(EftTask *task);

/* Definition flag 0x200: the stage blur. The victim's event 0x10 starts a fade-in (0.1 per frame) and takes the
 * owner's aim from node 0x11 as the blur centre argument; event 0x20 switches it off. */
void EftRushShot_UpdateFade(EftTask *task);

/* Victim's bit 0x80 starts the next stage effect of the definition (0x180760), bit 0x100 stops it. */
void EftRushShot_UpdateStageFx(EftTask *task);

/* Victim's bit 0x40 (unless definition flag 0x400000): white screen flash (0x172480). */
void EftRushShot_UpdateFlash(EftTask *task);

/* Victim's bit 0x40: sparks at five of the owner's nodes (0x19B7F8 with the table gEftRushShotSparkTbl). */
void EftRushShot_UpdateSparks(EftTask *task);

/* Steps every emitter of the model (19 groups) and spawns its particles at the projectile. */
void EftRushShot_Draw(s32 objId, EftTask *task, EftModel *model);

/* Swarm models, the node the shot sits on while attached, and the four handlers of the victim's events.
 * Standalone this differs by one instruction (beqz / beqzl at +0x48); see the note at the top of the file. */
void EftRushShot_UpdateAttached(EftTask *task);

/* Init callback: clears the work, takes speed and size from the definition and creates the model instance. */
void EftRushShot_Init(EftTask *task, EftTechArg *arg);

/* Term callback: ends the stage tint, the sub-effects and the model instance. */
void EftRushShot_Term(EftTask *task);

/* Update callback. */
void EftRushShot_Update(EftTask *task);

/* Post-update callback: reads what the hit record did this frame (moved, hit, ended). */
void EftRushShot_PostUpdate(EftTask *task);

/* Reset callback: destroys the particles once and kills the task. */
void EftRushShot_Reset(EftTask *task);

/* Draw callback: nothing. */
void EftRushShot_Nop(void);

/* Manager init: loads the effect model from the technique's pack and makes room for two projectiles. */
void EftRushShotMgr_Init(EftTask *task, EftTechArg *arg);

/* Manager term: releases the model. */
void EftRushShotMgr_Term(EftTask *task);

/* Manager update: steps the model. */
void EftRushShotMgr_Update(EftTask *task);

/* Manager reset: nothing. */
void EftRushShotMgr_Reset(void);
