#include "common.h"
#include "battle/eft_h.h"

/*
 * Technique effects, second part: 0x14B108..0x14F230. See include/battle/eft_h.h for the layouts.
 * Everything called outside the file is declared here with this file's own view types.
 *
 * Two functions (EftShot_BuildParam, EftEmit_SpawnType0) are INCLUDE_ASM with the C attempt in `#if 0` above them and a note on what differs; turning
 * every `#if 0` into `#if 1` and dropping the INCLUDE_ASM lines gives a file that fdiff can compile.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 atan2f(f32 y, f32 x);
extern f32 Mathf_Asin(f32 x);

extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);          /* rotate about X */
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);          /* rotate about Y */
extern void Vec3_Clamp(Vec4 *dst, Vec4 *src, f32 lo, f32 hi);       /* clamp x, y, z */
extern void Vec3_ScaleAdd(Vec4 *dst, Vec4 *dir, Vec4 *pos, f32 scale); /* dst = pos + dir * scale */
extern f32 EftMath_WrapAngle(f32 angle);                                   /* wrap to -pi..pi */
extern void EftAim_GetDir(Vec4 *out, Vec4 *target, s32 objId);
extern void EftAim_GetDirKeep(EftHSlot *slot, Vec4 *out, Vec4 *target, s32 objId);

extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 BtlPool_GetCurrent(void);

extern void BtlScene_Reset(s32 mode);
extern s32 BtlScene_IsCharStopped(s32 objId);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern s32 *BtlScene_GetPackEntry(s32 *base, s32 idx);

extern void *BtlTask_CreateChildList(EftHTask *task, s32 count, s32 dataSize);
extern EftHTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void BtlTask_Kill(EftHTask *task);
extern void BtlTask_SetDead(EftHTask *task);          /* task->kill |= 1 */
extern void BtlTask_SetOwnerTag(void *task, s32 flags);   /* task->flags |= flags */
extern EftHTask *BtlTask_GetParent(EftHTask *task);     /* the task that owns the list this task is in */

extern s32 BtlCharApi_GetPlayerObjUnk9C(s32 player, u32 n);
extern void *BtlCharApi_GetPlayerSuperData(s32 player);
extern void *BtlCharApi_GetPlayerSkillData(s32 player);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern s32 BtlCharApi_ObjQuery24D610(s32 objId, s32 arg1, s32 arg2);

/* eft_g.c */
extern s32 EftShot_TestBits(s32 objId, s32 mask);
extern void EftShot_SetHeldFlagA8(s32 objId);
extern void EftShot_Nop(s32 size);
extern void EftShot_SetCurSlot(s32 chr, s32 slot);
extern void EftShot_SetCharPool(s32 chr);

/* eft_i.c */
extern void EftEmit_SpawnOwn(EftSet *set, EftSetState *st, EftVolleyPose *pose, Vec4 *a, Vec4 *dir, s32 type, s32 idx,
                             s32 flags, f32 scale);
extern void EftEmit_KillAll(EftSet *set, EftSetState *st);
extern s32 EftEmit_UpdateAlive(EftSet *set, EftSetState *st);
extern void EftEmit_UpdateNodesReq(EftHSlot *slot, EftVolleyPose *pose);
extern void EftEmit_UpdateTrailWidth(EftSet *set, EftSetState *st);

/* 0x158438.. (effect requests of a fighter, state gp 0x2FE9FC) */
extern void EftTechEvt_Start(EftHSlot *slot, s32 lead, s32 life);
extern void EftTechEvt_RequestRestart(s32 objId);

/* 0x16A400 module: the shot tasks */
extern void *EftBlastObj_Create(EftVolleyShotArg *arg);
extern void *EftBlastObj_CreateWithModel(EftVolleyShotArg *arg, s32 *extra);
extern void EftBlastObj_Stop(void *shot);
extern s32 EftBlastObj_IsAlive(void *shot);
extern void EftBlastObj_SetSel(void *shot, s32 a, s32 b, s32 c);
extern void EftBlastObj_SetTarget(void *shot, s32 a, EftVolleyShot *pos);
extern void EftBlastObj_SetFrozen(void *shot, s32 a);
extern void EftBlastObj_SetNoHit(void *shot, s32 a);
extern void EftBlastObj_SetModelAnim(void *shot, s32 a);
extern void EftBlastObj_MarkLast(void *shot);

extern void EftTexSet_Load32(u8 *res, s32 *entry);
extern void EftTexSet_Load4(u8 *res, s32 *entry);
extern void EftTexSet_Load8(u8 *res, s32 *entry);
extern void EftTexSet_Load16(u8 *res, s32 *entry);
extern s32 EftVolleyAim_GetNodeSide(s32 node);
extern void EftVolleyAim_InitShot(s32 objId, EftVolleyShot *shot, s32 aimKind, s32 arg3, s32 index, s32 count, f32 a, f32 b);
extern void EftVolleyAim_Spread(s32 objId, Vec4 *dir, s32 a, s32 b, s32 c, s32 index, s32 count);
extern void EftVolleyAim_Update(s32 objId, EftVolleyShot *shot, Vec4 *out, s32 flag, f32 time, f32 a, f32 b);

extern EftHMgr *gEftShot;
extern EftHTaskClass gEftShotCharClass;
extern EftShotClassRow gEftShotClass[11];

EftHSlot *EftShot_GetSlot(s32 chr, s32 slot);
f32 EftShot_GetLeadTime(EftHSlot *slot);
EftVolleyShot *EftVolley_AllocShot(EftVolleyWork *w);
void EftVolley_Fire(s32 objId, EftHTask *task, s32 phase, s32 sub);
s32 EftVolley_PruneShots(EftHTask *task);
s32 EftVolley_UpdateShots(s32 objId, EftHTask *task);
void EftVolley_Aim(s32 objId, EftHTask *task, Vec4 *target, s32 bySlot);
void EftVolley_UpdateParts(s32 objId, EftHTask *task, EftSet *set, s32 reset);
s32 EftEmit_TypeToResKind(s32 type);
void EftEmit_LoadSet(void *owner, EftSet *set, EftSetHead *head, s32 *base, s32 common, s32 idx);
void EftEmit_FreeSet(EftSet *set);
void EftEmit_BeginFrame(EftSet *set);
s32 EftEmit_GetAimKind(EftSet *set);
s32 EftEmit_GetEndFrames(EftSet *set);
s32 EftEmit_GetPhaseMask(EftSet *set);
s32 EftEmit_IsPartDeferred(EftSet *set, s32 type, s32 idx);
void EftEmit_InitState(EftSet *set, EftSetState *st);
void EftEmit_TermState(EftSet *set, EftSetState *st);
s32 EftEmit_GetFlagsFromReq(EftSet *set, EftSetState *st, s32 objId, s32 type, s32 idx, s32 ending, s32 kill);
s32 EftEmit_GetFlags(EftSet *set, EftSetState *st, s32 objId, s32 type, s32 idx, s32 ending, s32 kill, s32 req);
s32 EftEmit_GetResetFlags(EftSet *set, EftSetState *st, s32 type, s32 idx);
void EftEmit_TagTask(void *task, s32 chr, s32 type);

/* Row of gEftShotClass for an effect type. */
static inline s32 EftShot_TypeRow(s32 type);
#define TYPE_ROW(t) EftShot_TypeRow(t)

/* Fills the parameter block of technique slot `slot` of character `chr`: defaults when `blank`, otherwise a
   flat copy of the fields the effects use out of the character's skill (slots 0, 1) or technique data. */
#if 0 /* not matched (499 instructions against 502). The defaults branch is identical except for the order of six stores; the skill and technique branches read the same fields into the same places, but the original keeps a copy of the slot index (move t8,t9 / addiu t8,t9,-2) and shares the address arithmetic of the structure-of-arrays fields differently (it spills 34 intermediate addresses to the stack, this C 30). Behaviour verified: both versions were run in an interpreter for every slot 0..4, blank 0 / 1 and 40 random source tables; the parameter block and the memory around it come out byte-identical (build/scratch_cleanup_eft/emu_buildparam.py; a deliberately wrong field is caught). Cleanup X2: making the slot index ONE function-scope variable set in both branches (`n = slot;` / `n = slot - 2;`, in front of or behind the data call), or reusing `i` for it, does not give the original's `move t8,t9` and is worse (355 to 384 instructions differ after alignment, against 317 for this form). Not tried: the element-alignment lesson (the original computes `d + n` once per access and spills each copy, the pattern that f32 [16][4] solved in EftOrbTail_DrawStreaks); the views of EftSkillSrc / EftSuperSrc are the place to look. */
void EftShot_BuildParam(s32 chr, s32 slot, EftShotParam *p, s32 blank);
#endif


/* The slot record of one technique of one character. */
EftHSlot *EftShot_GetSlot(s32 chr, s32 slot);

/* Adds the group task of a slot (the class its effect type names) to the character's task list. */
void EftShot_CreateSlotTask(s32 chr, s32 slot);

/* Starts the effect of a technique: stores the request in the slot, overrides the life and shot parameters
   with the request's and adds an instance task under the slot's group task. */
void EftShot_Start(EftHStartArg *arg);

/* Kills the character task of the layer, after resetting the scene tasks that belong to the character. */
void EftShot_DestroyChar(s32 chr);

/* Creates the character task of the layer unless it exists. */
void EftShot_CreateChar(s32 chr);

/* Frames between the start of a technique's effect and its first shot, by kind of technique: 0.85 s; a technique
   (kind 1) with unk5 == 5: 0.8 s; an ultimate (kind 2): 0.8 s with unk5 == 5, else 1.3 s, 0.7 s for technique
   0x268 and none for 0x290. (Two `return t;` statements: with a single return at the end the value sits in $f0
   from the start; the early return keeps it in $f1 and copies it at the exit.) */
f32 EftShot_GetLeadTime(EftHSlot *slot);

/* The effect pack of a technique slot, from the fighter object. */
s32 EftShot_GetCharPack(s32 chr, s32 slot);

/* ---- effect type -1: nothing ------------------------------------------------------------------------------ */

/* Group task init: a list for two instances of 8 bytes. */
void EftShotNullGroup_Init(EftHTask *task);

/* Group task term: nothing. */
void EftShotNullGroup_Term(EftHTask *task);

/* Group task update: nothing. */
void EftShotNullGroup_Update(EftHTask *task);

/* Instance init: remembers the slot. */
void EftShotNull_Init(EftHTask *task, EftHSlot *slot) {
    EftShotNullWork *w = task->data;

    memset(w, 0, sizeof(EftShotNullWork));
    w->slot = slot;
}

/* Instance term: nothing. */
void EftShotNull_Term(EftHTask *task);

/* Instance reset: kills the instance. */
void EftShotNull_Reset(EftHTask *task);

/* Instance update: kills the instance at once, whatever the slot holds. */
void EftShotNull_Update(EftHTask *task);

/* Instance post-update: nothing. */
void EftShotNull_PostUpdate(EftHTask *task);

/* Instance draw: nothing. */
void EftShotNull_Draw(EftHTask *task);

/* ---- effect type 1: volley of shots ------------------------------------------------------------------------ */

/* Returns a zeroed free shot entry (the last free one of the 30), NULL when all are in use. */
EftVolleyShot *EftVolley_AllocShot(EftVolleyWork *w);

/* Fires: creates one shot task (EftShotParam.volley of them in phase 1) at the fighter's firing node. */
void EftVolley_Fire(s32 objId, EftHTask *task, s32 phase, s32 sub);

/* Forgets the shots whose task has ended; returns 1 while any is alive. */
s32 EftVolley_PruneShots(EftHTask *task);

/* Fires on this frame's fighter event when the set has parts for that phase, then steers the live shots. */
s32 EftVolley_UpdateShots(s32 objId, EftHTask *task);

static const Vec4A sAimForward = { 0.0f, 0.0f, 1.0f, 1.0f };

/* Sets the aim (unit vector from the fighter towards `target`) and the direction the parts use: the aim, or
   straight up (aim kind 7), or the aim lifted by 45 degrees (aim kind 8). */
void EftVolley_Aim(s32 objId, EftHTask *task, Vec4 *target, s32 bySlot);

/* Gives every emitter of the set its flags of the frame (or the reset flags) and spawns with them. Emitters of
   a later phase are skipped, and so are the phase 5 ones of techniques 0x26E / 0x26F. */
void EftVolley_UpdateParts(s32 objId, EftHTask *task, EftSet *set, s32 reset);

/* Instance init: clears the work, takes the shot parameters of the slot and the group's emitter set. */
/* The slot is a local copy of the argument (`EftHSlot *slot = arg;`, declared behind a local that is initialised
   by a call): the callback's argument was presumably untyped in the original. With the parameter used directly
   6 instructions differ: gcse's PRE then merges the load of slot->param for the id test with the one for the
   flag test (the original reloads it), the same thing as in EftBlast_Init (eft_j.c). Only the LAST use (the
   owner tag) has to go through the copy; a copy declared in front of the first call is folded away again. Found
   by decomp-permuter. */
void EftVolley_Init(EftHTask *task, EftHSlot *arg);

/* Instance term: releases the emitter state and, for a technique, sets the fighter's held flag 0xA8. */
void EftVolley_Term(EftHTask *task);

/* Instance update: follows the fighter's effect requests through the steps aim / fire / end. */
void EftVolley_Update(EftHTask *task);

/* Instance post-update: drops dead emitters and shots; a task flagged 4 starts ending. */
void EftVolley_PostUpdate(EftHTask *task);

/* Instance reset: kills the emitters once and the task. */
void EftVolley_Reset(EftHTask *task);

/* Instance draw: nothing (the shots and the emitters draw themselves). */
void EftVolley_Draw(EftHTask *task);

/* Group init: loads the technique's emitter set, makes room for two instances, and keeps pack entry 1 when the
   technique has flag 0x20000. */
void EftVolleyGroup_Init(EftHTask *task, EftHSlot *slot);

/* Group term: frees the set's resources. */
void EftVolleyGroup_Term(EftHTask *task);

/* Group update: per-frame clear of the set's resources. */
void EftVolleyGroup_Update(EftHTask *task);

/* Group reset: nothing. */
void EftVolleyGroup_Reset(EftHTask *task);

/* ---- emitter set library ----------------------------------------------------------------------------------- */

/* Which of the four resource arrays the groups of a type keep their resources in. */
s32 EftEmit_TypeToResKind(s32 type);

/* Parses an emitter set: header, group table, emitters. `head` given: only the tables are set up. Otherwise the
   header is entry `idx` of the pack `base` (or common entry `idx` when `common` is 1), and the entries after it
   are the resources of the groups in order, which are loaded into arrays from the current pool. */
void EftEmit_LoadSet(void *owner, EftSet *set, EftSetHead *given, s32 *base, s32 common, s32 idx);

/* Frees the resource arrays of a set and forgets its tables. */
void EftEmit_FreeSet(EftSet *set);

/* Clears the last word of every resource object of the set (its per-frame state). */
void EftEmit_BeginFrame(EftSet *set);

/* Header byte 0x21. */
s32 EftEmit_GetHead21(EftSet *set);

/* Header byte 0x26. */
s32 EftEmit_GetHead26(EftSet *set);

/* Header byte 6: how EftVolley_Aim bends the direction. */
s32 EftEmit_GetAimKind(EftSet *set);

/* Header byte 0x22. */
s32 EftEmit_GetHead22(EftSet *set);

/* Header byte 0x25. */
s32 EftEmit_GetHead25(EftSet *set);

/* Header float 0x28. */
f32 EftEmit_GetHead28(EftSet *set);

/* Header byte 0x20: frames an instance lives on after its end was asked. */
s32 EftEmit_GetEndFrames(EftSet *set);

/* Header byte 0x27: bit per phase the set has emitters for. */
s32 EftEmit_GetPhaseMask(EftSet *set);

/* Flags byte of emitter `idx` of group `type`. */
s32 EftEmit_GetPartFlags(EftSet *set, s32 type, s32 idx);

/* 1 when the emitter's phase is one the set handles through shots and its unkA matches that phase (or is 5):
   such an emitter is not driven by the owner task. */
s32 EftEmit_IsPartDeferred(EftSet *set, s32 type, s32 idx);

/* Resets the per-instance state of a set's emitters. */
void EftEmit_InitState(EftSet *set, EftSetState *st);

/* Counterpart of EftEmit_InitState: nothing to release. */
void EftEmit_TermState(EftSet *set, EftSetState *st);

/* Flags for one emitter from the fighter's effect requests of this frame. */
s32 EftEmit_GetFlagsFromReq(EftSet *set, EftSetState *st, s32 objId, s32 type, s32 idx, s32 ending, s32 kill);

/* Flags for one emitter from a mask of phases 0..5 (bit n = phase n happens now). */
s32 EftEmit_GetFlagsFromMask(EftSet *set, EftSetState *st, s32 objId, s32 type, s32 idx, s32 ending, s32 kill,
                             s32 mask);

/* The flags (EFT_CMD_*) EftEmit_Spawn should get for emitter `idx` of group `type` this frame. `req` holds the
   request bits 2, 4, 0x10, 0x20, 0x40 (phases 0, 1, 3, 4, 5 begin), `ending` that the instance is ending and
   `kill` that it must stop at once. */
s32 EftEmit_GetFlags(EftSet *set, EftSetState *st, s32 objId, s32 type, s32 idx, s32 ending, s32 kill, s32 req);

/* Flags for a reset: move and warp a started, not yet stopped emitter (type 17 always, others when they aim
   along the direction). */
s32 EftEmit_GetResetFlags(EftSet *set, EftSetState *st, s32 type, s32 idx);

/* Marks the task of a spawned object as belonging to character `chr` (so BtlScene_Reset(2 + chr) reaches it),
   except for the group types 2 and 5. */
void EftEmit_TagTask(void *task, s32 chr, s32 type);

/* ---- per-type spawners ------------------------------------------------------------------------------------ */
/* Called by EftEmit_Spawn (0x14FF90) through its jump table. Common arguments: the set, the handle table of the
   instance (one task per emitter), the EFT_CMD_* flags, the group type, the character, the emitter's index in
   its group, the node position and the direction. `size` is the emitter's current size, `scale` what its
   offsets are multiplied by, `rate` goes to the module unchanged. Each one creates the module's object on
   EFT_CMD_START when the handle is free, then forwards move / size / direction / stop / kill. */

#define H(n) (handles->h[n])
#define ZERO_VEC { 0.0f, 0.0f, 0.0f, 0.0f }

extern void *EftRay_Create(EftEmitLightArg *arg);
extern void *EftRay_CreateByValue(EftEmitLightArg *arg);
extern void EftRay_SetPos(void *obj, Vec4 *pos);
extern void EftRay_Kill(void *obj);
extern void EftRay_SetType(void *obj, s32 type);

/* Type 0: a light of kind EftSetDef.unk4 (0 or 1) at the node. */
#if 0 /* not matched: 218 instructions in the original, 219 here; 50 differ after alignment (the form stored before: 223
instructions, 67). What is known (cleanup X2, allocation dumps):
- The original shares `jal EftRay_SetType` and the whole EftEmit_TagTask call between the two cases (case 0 ends
  in a jump into case 1). The form with both calls written out in both cases is NOT merged by the compiler: after
  the first jump pass a `(use (const_int 0))` insn follows the last call of case 1 (a call directly in front of a
  label), so the cross-jump pass finds no common tail. It also gives chr / type five references each and puts
  them in s5 / s6, in front of flags / handles.
- The original's registers (flags s5, handles s6, chr s7, type fp) need chr and type to have FOUR references:
  EftRay_SetType written in both cases, EftEmit_TagTask written once; and handles must not be referenced by the
  shared call, so the address of the handle slot is one value set in both cases (`h` below). With that the four
  saved arguments, the frame and the shared tail come out right.
- Still different: `n` and the address of case 1's block exchange s3 / s4 (the original gives `n` the higher
  priority); 0xC0 / 0x70 exchange v0 / v1 in case 0 and the alpha store comes first there; EftRay_SetType's jal is
  not shared (here the store through `h` is scheduled in front of it in both cases, in the original only in
  case 0); `scale` is copied to f20 in front of the switch instead of behind it. The goto is a stand-in for
  whatever structured form shares the tag call; a `created` flag is not threaded (li v1,1 / beqz v1 remains),
  an if / else chain on `kind` merges the two argument blocks into one frame slot (frame 304 instead of 416).
  The values built and the calls made are the same as in the form stored before. */
void EftEmit_SpawnType0(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 idx, Vec4 *pos,
                        f32 size, f32 scale, f32 rate);
#endif


extern void *EftRays_Create(EftEmitArg2 *arg);
extern void EftRays_Stop(void *obj);
extern void EftRays_Kill(void *obj);
extern void EftRays_SetPos(void *obj, Vec4 *pos);
extern void EftRays_SetDelay(void *obj, f32 v);
extern void EftRays_SetHold(void *obj, f32 v);
extern void EftRays_SetFade(void *obj, f32 v);
extern void EftRays_SetSize(void *obj, f32 size);

/* Type 2. */
void EftEmit_SpawnType2(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 idx, Vec4 *pos,
                        Vec4 *dir, f32 size, f32 scale, f32 rate);

extern void *EftBill_Create(EftEmitArgA *arg);
extern s32 EftBill_Stop(void *obj);
extern s32 EftBill_Kill(void *obj);
extern s32 EftBill_SetPos(void *obj, Vec4 *pos);
extern s32 EftBill_SetDir(void *obj, Vec4 *dir);
extern s32 EftBill_SetSize(void *obj, f32 size);
extern s32 EftBill_SetDelay(void *obj, f32 v);
extern s32 EftBill_SetEndDelay(void *obj, f32 v);
extern s32 EftBill_SetFront(void *obj);
extern s32 EftBill_SetType(void *obj, s32 type);

/* Type 16. */
/* Matching note (EftEmit_SpawnType16): the resource pointer is built in two statements with texA read in between
   (index first, then texA, `res += ...`, texB). The single-expression form of EftEmit_SpawnType17 / 18 gives the
   same instructions with texA / texB in s1 / s2 exchanged: res, texA and texB are block-local values allocated in
   order of refs / life, and the original's texB lives one instruction less than texA, which needs the first
   scheduling pass to emit "load texA, res add, load texB". That happens only when the add has one dying operand
   (`res += x`, not `res = base + x`), stands behind texA in the source, and g->catFirst is read before
   g->firstPair. */
void EftEmit_SpawnType16(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 idx, Vec4 *pos,
                         Vec4 *dir, f32 size, f32 scale, f32 rate);

extern void *EftRibbon_Create(EftEmitArg17 *arg);
extern s32 EftRibbon_Stop(void *obj);
extern s32 EftRibbon_Kill(void *obj);
extern s32 EftRibbon_SetPos(void *obj, Vec4 *pos);
extern s32 EftRibbon_SetEnd(void *obj, Vec4 *pos2, s32 warp);
extern s32 EftRibbon_SetSize(void *obj, f32 size);
extern s32 EftRibbon_SetMaxNodes(void *obj, s32 v);
extern s32 EftRibbon_SetDelay(void *obj, f32 v);
extern s32 EftRibbon_SetFadeDelay(void *obj, f32 v);
extern s32 EftRibbon_SetFadeTime(void *obj, f32 v);
extern s32 EftRibbon_SetUnkD8(void *obj, s32 v);

/* Type 17: an object between two points, the node position pushed along the direction by EftSetDef.unk10 and
   pos2 pushed by EftSetDef.unk14. EFT_CMD_RESTART destroys the object and creates it again. */
void EftEmit_SpawnType17(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 arg5, s32 idx,
                         Vec4 *pos, Vec4 *pos2, Vec4 *dir, f32 size, f32 scale, f32 rate);

extern void *EftChain_Create(EftEmitArgA *arg);
extern s32 EftChain_Stop(void *obj);
extern s32 EftChain_Kill(void *obj);
extern s32 EftChain_SetPos(void *obj, Vec4 *pos);
extern s32 EftChain_Warp(void *obj, Vec4 *pos);
extern s32 EftChain_SetDir(void *obj, Vec4 *dir);
extern s32 EftChain_SetSize(void *obj, f32 size);
extern s32 EftChain_SetParam3(void *obj, s32 v);
extern s32 EftChain_SetParam5(void *obj, f32 v);
extern s32 EftChain_SetParam6(void *obj, f32 v);
extern s32 EftChain_SetViewOnly(void *obj);
extern s32 EftChain_SetType(void *obj, s32 type);

/* Type 18. */
void EftEmit_SpawnType18(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 arg5, s32 idx,
                         Vec4 *pos, Vec4 *dir, f32 size, f32 scale, f32 rate);

extern void *EftAnimPart_Create(EftEmitArg14 *arg);
extern s32 EftAnimPart_Stop(void *obj);
extern s32 EftAnimPart_Kill(void *obj);
extern s32 EftAnimPart_SetType(void *obj, s32 type);
extern s32 EftAnimPart_SetPos(void *obj, Vec4 *pos);
extern s32 EftAnimPart_SetSize(void *obj, f32 size);
extern s32 EftAnimPart_SetDir(void *obj, Vec4 *dir);
extern s32 EftAnimPart_SetDelay(void *obj, f32 v);
extern s32 EftAnimPart_SetHold(void *obj, f32 v);
extern s32 EftAnimPart_SetFade(void *obj, f32 v);

/* Type 14. */
/* Matching note: the resource pointer is built in two statements (`res = base; res += index * size;`), as in
   EftEmit_SpawnType16. Written as one expression the sum and the product exchange v1 / a2 (16 instructions). */
void EftEmit_SpawnType14(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 idx, Vec4 *pos,
                         Vec4 *dir, f32 size, f32 scale, f32 rate);

extern void *EftPtcl_Create(EftEmitArgA *arg);
extern s32 EftPtcl_Stop(void *obj);
extern s32 EftPtcl_Kill(void *obj);
extern s32 EftPtcl_SetPos(void *obj, Vec4 *pos);
extern s32 EftPtcl_Warp(void *obj, Vec4 *pos);
extern s32 EftPtcl_SetDir(void *obj, Vec4 *dir);
extern s32 EftPtcl_SetSize(void *obj, f32 size);
extern s32 EftPtcl_SetStartDelay(void *obj, f32 v);
extern s32 EftPtcl_SetStopDelay(void *obj, f32 v);
extern s32 EftPtcl_SetLinger(void *obj, f32 v);
extern s32 EftPtcl_SetFront(void *obj);
extern s32 EftPtcl_SetFlag40(void *obj, s32 v);
extern s32 EftPtcl_SetType(void *obj, s32 type);

/* Type 5. */
/* Matching note: see EftEmit_SpawnType16 (same two-step resource pointer). */
void EftEmit_SpawnType5(EftSet *set, EftSetHandles *handles, s32 flags, s32 type, s32 chr, s32 idx, Vec4 *pos,
                        Vec4 *dir, f32 size, f32 scale, f32 rate);
