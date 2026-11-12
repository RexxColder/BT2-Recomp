#include "common.h"
#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/btl_pool.h"
#include "battle/btl_scene.h"
#include "sys/common.h"
#include "sys/heap.h"

/*
 * Battle effect scene, 0x12C9F0..0x12DD80: the task tree the fighter-attached effects run in and the services
 * they share. What it manages and the order of its entry points are described in include/battle/btl_scene.h.
 *
 * Everything this file calls outside itself is another module that is not decompiled. The names used for
 * the task system (BtlTask*), BtlChar_FindByObjId and BtlStage_IsReady are guesses recorded in
 * config/symbols/btl_scene.txt; Battle_GetStage, Battle_IsTimeLimitOff, Battle_GetTimeLimit and
 * Battle_GetRuleUnk10 come from battle/battle_setup.h.
 * The callees still called func_XXXXXXXX, from a first read of their code:
 *
 *   next module (blast records, gp 0x2FE9A8; 0x12DD80..0x12EEA0)
 *     EftHit_Init init / EftHit_Term term: 0x6410 bytes from the pool
 *     EftHit_BeginFrame   empties the list unless BtlScene_IsTimeStopped(); EftHit_Clear empties it always
 *     EftHit_GetList   returns the list; EftHit_GetTaskFlags(i) returns record i's definition flags (+0x60 -> +4)
 *     EftHit_SpawnImpacts, EftHit_ClampToStage, EftHit_UpdateResults   per-frame passes over the records
 *     EftHit_HasDefFlag200000(rec)   1 when rec+0x68 is 0 and rec+0x64 points at a task without flag 0x200000
 *   0x1C-byte block at gp 0x2FE9B0: EftCam_Init init / EftCam_Term term / EftCam_Clear clear /
 *     EftCam_Update per-frame / EftCam_IsActive returns its word +0xC
 *   EftVram_Init init / EftVram_Term term: 0x80C-byte block at gp 0x2FEAF4
 *   EftSprAnim_InitPool init / EftSprAnim_TermPool term: 0xC200-byte block at gp 0x2FEAE8
 *   EftSurf_BuildPalettes, EftVram_UploadAll, EftVram_Reset, EftGfx_UpdateClipPlanes   draw work shared by all tasks
 *   EftChar_Kill / EftChar_Create, EftShot_DestroyChar / EftShot_CreateChar   free / create a character's task in
 *     layer 2 and in layer 1
 *   EftWater_UpdateBlast, EftBubble_OnBlastRecord   per-record update
 *   fighter queries, 0x204EA0..0x2080E0 (they take an object id and look the fighter up):
 *     BtlCharApi_GetHeight(i)   BtlObj_Get(i)->0xFF4 as float, 10.0 when there is no object
 *     BtlCharApi_IsFighter(id)  1 when a fighter has this object id
 *     BtlCharApi_GetOpponentObjId(id)  object id of that fighter's opponent
 *     BtlCharApi_GetPlayerObjUnk58(i)   pack pointer of fighter i (0x1DC280 -> +0x58)
 *     BtlCharApi_IsHidden(id)  bit 1 of object +0xA40, inverted
 *     BtlCharApi_IsFrozen(id)  the fighter is in hit-stop (+0x1320 > 0); BtlCharApi_AnyFrozen() any fighter is
 *     BtlCharApi_IsInRushSequence(id)  action id in 0x12D..0x12F or 0x139..0x13B
 *     BtlCharApi_IsChanging(id)  action id in 0xEC..0xF8 or 0x103..0x104
 *     BtlCharApi_SetHeldFlagAB(id)  sets held flag 0xAB on the fighter
 *     BtlCharApi_IsTargetBelowHalfHp(a, b)  both alive and b's HP below half of its maximum
 *     BtlCharApi_CanTechniqueFinish(a, b)  a second test on a's current technique (0x80000 bit of 0x210D80)
 *     BtlCharApi_IsCamShown(id)  split-screen visibility test; BtlCharApi_AnyCamPriority() any fighter with flag 0xD3
 *   BtlStage_RequestChange     BtlLoad_RequestStageChange(BtlStage_GetChangeTarget()): asks for the changed stage
 *   StgTint_GetWork     returns the block at 0x31C4A0
 *   BtlGame_IsFighting     tail call of BtlSeq_IsFighting
 *   BtlChars_IsTimeStopped     returns gBtlChars + 0x274
 */

extern void *memset(void *dst, s32 c, u32 n);

extern BtlTaskClass gBtlSceneRootClass; /* 0x2C3490: {BtlSceneRoot_Update, BtlSceneRoot_Init, BtlSceneRoot_Term} */
extern BtlTaskClass D_002C3550;         /* layer 0 */
extern BtlTaskClass D_002C35D0;         /* layer 4 */
extern BtlTaskClass D_002C36D0;         /* layer 1 */
extern BtlTaskClass gEftCharRootClass;         /* layer 2 */
extern BtlTaskClass gEftLayer3Class;         /* layer 3 */

/* task system, 0x1AD150..0x1ADB48 */
extern void BtlTaskList_Update(void *list);
extern void BtlTaskList_PostUpdate(void *list);
extern void BtlTaskList_Reset(void *list, s32 flag);
extern void BtlTaskList_Draw(void *list);
extern void *BtlTask_CreateChildList(void *task, s32 capacity, s32 workSize);
extern void *BtlTaskList_Create(void *parent, s32 capacity, s32 workSize);
extern void BtlTaskList_Destroy(void *list);
extern void *BtlTaskList_AddFirst(void *list, BtlTaskClass *cls, void *arg);
extern void *BtlTaskList_AddHead(void *list, BtlTaskClass *cls, void *arg);
extern void *BtlTaskList_AddTail(void *list, BtlTaskClass *cls, void *arg);
extern void BtlTask_Kill(void *task);

extern s32 BtlStage_IsReady(void);

extern void EftHit_Init(void);
extern void EftHit_Term(void);
extern void EftHit_BeginFrame(void);
extern void EftHit_Clear(void);
extern BtlBlastList *EftHit_GetList(void);
extern s32 EftHit_GetTaskFlags(s32 idx);
extern void EftHit_SpawnImpacts(void);
extern s32 EftHit_HasDefFlag200000(BtlBlastRec *rec);
extern void EftHit_ClampToStage(void);
extern void EftHit_UpdateResults(void);
extern void EftCam_Init(void);
extern void EftCam_Term(void);
extern void EftCam_Clear(void);
extern s32 EftCam_IsActive(void);
extern void EftCam_Update(void);
extern void EftGfx_UpdateClipPlanes(void);
extern void EftBubble_OnBlastRecord(BtlBlastRec *rec);
extern void EftSurf_BuildPalettes(void);
extern void EftWater_UpdateBlast(BtlBlastRec *rec);
extern void EftShot_DestroyChar(s32 chr);
extern void EftShot_CreateChar(s32 chr);
extern void EftChar_Kill(s32 chr);
extern void EftChar_Create(s32 chr);
extern void EftSprAnim_InitPool(void);
extern void EftSprAnim_TermPool(void);
extern void EftVram_Init(void);
extern void EftVram_Term(void);
extern void EftVram_UploadAll(void);
extern void EftVram_Reset(void);
extern s32 BtlChars_IsTimeStopped(void);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_IsFighter(s32 objId);
extern s32 BtlCharApi_GetOpponentObjId(s32 objId);
extern s32 *BtlCharApi_GetPlayerObjUnk58(s32 side);
extern s32 BtlCharApi_IsHidden(s32 objId);
extern s32 BtlCharApi_IsFrozen(s32 objId);
extern s32 BtlCharApi_AnyFrozen(void);
extern s32 BtlCharApi_IsInRushSequence(s32 objId);
extern s32 BtlCharApi_IsChanging(s32 objId);
extern void BtlCharApi_SetHeldFlagAB(s32 objId);
extern s32 BtlCharApi_IsTargetBelowHalfHp(s32 objId, s32 targetId);
extern s32 BtlCharApi_CanTechniqueFinish(s32 objId, s32 targetId);
extern s32 BtlCharApi_IsCamShown(s32 objId);
extern s32 BtlCharApi_AnyCamPriority(void);
extern s32 BtlGame_IsFighting(void);
extern void BtlStage_RequestChange(void);
extern u8 *StgTint_GetWork(void);

/* Allocates the scene, the pool arenas and the effect subsystems, then creates the root task (0 = every layer). */
void BtlScene_Init(s32 layerMask);

/* Resets every task, destroys the tree and frees everything BtlScene_Init created. */
void BtlScene_Term(void);

/* First per-frame pass: empties the record list, refreshes the character scales, runs every task's update. */
void BtlScene_Update(void);

/* Second per-frame pass: every task's post-update, then the blast records. */
void BtlScene_PostUpdate(void);

/* Resets the tasks selected by mode (BTL_SCENE_RESET_*) and drops a pending stage change request. */
void BtlScene_Reset(s32 mode);

/* Draws the scene for one view; the shared draw work is done for the first view only. */
void BtlScene_Draw(s32 first);

/* Returns entry idx of the offset table at the start of common file 3 (gCommonRes->data[1]). */
s32 *BtlScene_GetCommonEntry(s32 idx);

/* Returns entry idx of a pack: base + (offset table word idx, rounded down to 4). */
s32 *BtlScene_GetPackEntry(s32 *base, s32 idx);

/* Returns the size of entry idx of a pack (next offset - this offset). */
s32 BtlScene_GetPackEntrySize(s32 *base, s32 idx);

/* Tests bit (bit - 1) of the first word of entry 1 of entry 1 of a character's pack. */
/* Matching note: the mask has to be computed BETWEEN the two calls. It then lives across the second call (saved
 * register), `bit` across the first, and the second scheduling pass sinks all three instructions below both
 * calls, which is where the original has them although it uses $s0 / $s1 for them. */
s32 BtlScene_TestCharPackBit(s32 side, s32 bit);

/* Returns entry idx of a character's pack (0x2053B0), or NULL when the character has none. */
s32 *BtlScene_GetCharPackEntry(s32 side, s32 idx);

/* Returns gCommonRes + 0x24 (the stage data pointer). */
s32 BtlScene_GetStageData(void);

/* Returns 0 only when the stage is ready and the battle is not paused. */
s32 BtlScene_IsTimeStopped(void);

/* Returns 1 when the battle is paused or the fighter with this object id is in hit-stop (+0x1320 > 0). */
s32 BtlScene_IsCharStopped(s32 objId);

/* Returns 1 when paused, when any fighter is in hit-stop or when fighter 0 or 1 is in actions 0x12D..0x12F / 0x139..0x13B. */
s32 BtlScene_IsAnyCharStopped(void);

/* Sets the number of characters the per-character tables are sized for. */
void BtlScene_SetCharCount(s32 count);

/* Returns the number of characters. */
s32 BtlScene_GetCharCount(void);

/* Returns 1 while the second split-screen view is being drawn. */
s32 BtlScene_IsSecondView(void);

/* Tells a task whether to draw for this fighter in the view being drawn (split-screen aware). */
s32 BtlScene_IsCharInView(s32 objId);

/* Returns 1 on stages 3, 15, 16, 24, 26, 30 and 32, else byte 0x58 of the block at 0x31C4A0. */
s32 BtlScene_IsStageFlagOn(void);

/* Returns whether byte 0x58 of the block at 0x31C4A0 is set. */
s32 BtlScene_GetStageFlag(void);

/* Records whether the camera forced a single full-screen view this frame. */
void BtlScene_SetSingleView(s32 singleView);

/* Returns 1 when one view is drawn (not split-screen, or the camera forced it). */
s32 BtlScene_IsSingleView(void);

/* Kills layer 0 and rewinds its pool arena (slot 2). */
void BtlScene_FreeLayer0(void) {
    BtlPool_SetCurrent(2);
    BtlTask_Kill(gBtlScene->layer[0]);
    gBtlScene->layer[0] = NULL;
    BtlPool_Reset(2);
}

/* Creates layer 0 at the head of the group if it does not exist. */
void BtlScene_CreateLayer0(void) {
    if (gBtlScene->layer[0] == NULL) {
        gBtlScene->layer[0] = BtlTaskList_AddHead(gBtlScene->group, &D_002C3550, NULL);
    }
}

/* Returns the task list holding the layers. */
void *BtlScene_GetGroup(void);

/* Frees a character's task in layer 2 (0x1721D0). */
void BtlScene_FreeCharLayer2(s32 chr);

/* Creates a character's task in layer 2 (0x172240). */
void BtlScene_CreateCharLayer2(s32 chr);

/* Frees a character's tasks in layers 2 and 1; called when the character is streamed out. */
void BtlScene_FreeChar(s32 chr);

/* Creates a character's tasks in layers 1 and 2; called by the loader job when it is streamed in. */
void BtlScene_CreateChar(s32 chr);

/* Tells a task of the given kind (0..6) attached to an object whether its time is stopped this frame. */
s32 BtlScene_IsEffectStopped(s32 objId, s32 kind);

/* Second per-kind test of the tasks, on the object's state (0x205DC8) and its fighter's actions. */
#if 0
/* Not matching (12 of 92 after alignment, 90 instructions against 92): only the tails of the first switch differ.
 * Before delay-slot filling this C gives: case 0 `beqz v0,END / X: s2 = 1 / b END`, case 1 `bnez v0,END / b X`,
 * cases 3 and 6 `beq -> X`: the final jump pass has cross-jumped the three `result = 1; break;` tails into the
 * copy of case 0, whose label X then stops the "branch around one instruction" rewrite. The original shows that
 * rewrite in BOTH case 0 and case 1 (`bnezl v0,END / li s2,1 / b END+4 / li v0,4`, and `beqzl` in case 1), so
 * there each case still had its own unlabelled `result = 1` and the block of cases 3 / 6 was separate (its
 * `li s2,1` went into the delay slot of `beq kind,3`, and the block then disappeared). What kept the three
 * tails from being cross-jumped is not found. Tried: all 24 orders of the four case groups with two forms of
 * each test, eight statement forms per case (if / break-first / ternary / ++ / |= / else forms), a goto to a
 * shared label. The default case no longer needs the `one` variable: two plain ifs give the original's
 * `li s0,1` (in the delay slot of the first call) and `sltu` / `movz`. Behaviour is the same as the original.
 * Cleanup 4 (reorg / jump behaviour worked out from dumps, 130 more forms):
 * - The rewrite in cases 0 and 1 is reorg's optimize_skip: `beqz v0,END / li s2,1 / b END` (a branch around ONE
 *   unlabelled instruction that is followed by a jump to the branch's own target) becomes `bnezl v0,END /
 *   li s2,1`. So before reorg both cases had their own unlabelled `result = 1` and cases 3 / 6 a third copy
 *   (label X; both dispatch branches then take X's `li s2,1` into a delay slot or find it redundant, and X
 *   is deleted as unreachable). The dispatch ends `beq kind,6,X / b default`, so X did not directly follow it.
 * - Cross-jumping needs two matching instructions, or one when the copy it starts from is entered through a
 *   label. Cases 0 / 1 are entered by falling out of a conditional branch (no merge between them); the copy
 *   of cases 3 / 6 IS entered through a label, so it always merges into another copy, whose `li` then gets
 *   the label that blocks optimize_skip. That is the whole difference, and nothing tried keeps X apart.
 * - `if (!AnyFrozen()) break; goto hide;` with `hide:` in cases 3 / 6 placed FIRST gives case 0 exactly
 *   (`bnez X / b END` filled from X's thread), 7 differ; case 1's `beqz` is predicted not taken, takes the
 *   `li v0,4` of the following jump instead, and the dispatch falls into X (`bne kind,6,default`).
 * - Cases 3 / 6 last (behind `default`): the default's second `if` is no longer converted to a conditional
 *   move by the first jump pass (it must fall into the switch end for that) and merges with X: 51 to 114.
 * - An inline helper for the first switch (five shapes): 39 to 50. */
s32 BtlScene_IsEffectHidden(s32 objId, s32 kind);
#endif


/* Asks BtlScene_CheckStageChange to change the stage on the next frame (no caller). */
void BtlScene_RequestStageChange(void);

/* Returns 1 when a stage change was asked for. */
s32 BtlScene_IsStageChangeRequested(void);

/* Drops the stage change request. */
void BtlScene_ClearStageChangeRequest(void);

/*
 * Once per frame, while fighting, outside modes 4..7 and with the time limit off or at least 10: looks for the
 * first active blast record whose definition is of type 1 (flags & 3) and, when that definition has bit 0x4000,
 * whose own flag 0x10 is set. hit is 1 when rule word 0x18 is on, EftHit_HasDefFlag200000(rec) holds and the opponent is
 * below half HP (BtlCharApi_IsTargetBelowHalfHp), else 2 when BtlCharApi_CanTechniqueFinish holds. hit 1 marks the record (flags 2 and 8, two
 * separate stores in the source: with one `|= 0xA` the loop is short enough for the compiler to hoist its
 * constants) and asks for the stage change; hit 2 sets held flag 0xAB on the opponent. A pending
 * BtlScene_RequestStageChange() forces the stage change.
 */
void BtlScene_CheckStageChange(void);

/* Allocates the per-character rate table and sets every rate to 1.0. */
void BtlScene_InitRates(void);

/* Frees the per-character rate table. */
void BtlScene_TermRates(void);

/* Sets one of a character's six rates (out-of-range characters are ignored). */
void BtlScene_SetCharRate(s32 idx, s32 slot, f32 value);

/* Returns one of a character's six rates (1.0 for an out-of-range character). */
f32 BtlScene_GetCharRate(s32 idx, s32 slot);

/* Recomputes every character's body scale (no caller). */
void BtlScene_UpdateAllCharScales(void);

/* Recomputes the body scale of every fighter that exists and is not in actions 0xEC..0xF8 / 0x103..0x104. */
void BtlScene_UpdateCharScales(void);

/* Returns a character's body scale (1.0 for an out-of-range character). */
f32 BtlScene_GetCharScale(s32 idx);

/* Init callback of the root task: creates the group list (5 tasks) and the layers. */
void BtlSceneRoot_Init(void *task);

/* Term callback of the root task: empty. */
void BtlSceneRoot_Term(void);

/* Update callback of the root task: empty. */
void BtlSceneRoot_Update(void);

/* Creates the layer tasks enabled in layerMask, in the order 0, 1, 2, 3, 4. */
void BtlScene_CreateLayers(void *group);

/* Kills the layer tasks enabled in layerMask, in the order 3, 2, 1, 0, 4. */
void BtlScene_FreeLayers(void);

/* Returns the next value (0..150888) of the effects' generator; the state is kept unchanged while 0x1D63A8() is set. */
s32 BtlScene_Rand(void);

/* Returns a random float in [0, 1). */
f32 BtlScene_RandF(void);

/* Returns a random float between a and b. */
f32 BtlScene_RandRangeF(f32 a, f32 b);

/* Returns a random integer between a and b, both included. */
s32 BtlScene_RandRange(s32 a, s32 b);

/* Runs 0x140ED0 and 0x133478 on every blast record. */
void BtlScene_UpdateRecords(void);
