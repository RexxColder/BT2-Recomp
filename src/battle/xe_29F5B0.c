#include "common.h"
#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/btl_char_mgr.h"
#include "battle/btl_scene.h"
#include "battle/btl_seq.h"
#include "sys/common.h"
#include "sys/heap.h"
#include "sys/save.h"

/*
 * Fighter manager, 0x1C0058..0x1C2FF0: the roster (gBtlChars), the per-fighter reset and the whole-roster
 * phases of a battle frame. Layouts: include/battle/btl_char_mgr.h.
 *
 * Lifecycle
 *   BtlChar_AllocAll(n)   Battle_Init, n = 2: the manager, n fighters of 0x1600 bytes and two side arrays, all
 *                         zeroed; caches six table pointers of common file 2; BtlChar_ResetAll(); BtlCharSnd_Init().
 *   BtlChar_ResetAll()    Battle_Restart, and BtlChars_CheckStart when the fight starts: releases what the
 *                         fighters hold, zeroes the manager's counters and every fighter, then per fighter
 *                         side / pad / index, BtlChar_BindObject, BtlChar_Reset.
 *   BtlChar_FreeAll()     Battle_Term.
 *
 * One frame (the callers are Battle_Loop and Battle_Update, src/battle/battle.c). "per fighter" means a loop
 * over the roster in index order, and every per-fighter body does nothing while the fighter is frozen
 * (chr->freeze > 0, BtlChar_IsFrozen).
 *
 *   1. BtlChars_CheckStart      before Pad_Update, paused or not. The first frame the sequence is in Ready or
 *                               Fight: BtlChar_ResetAll() (except in mode 1) and set BTL_CHARS_STARTED.
 *   2. BtlChars_SampleInput     skipped under PAUSE / LOADING. per fighter: stage 2, BtlInput_Sample.
 *   3. BtlChars_UpdateInput     skipped under PAUSE; under LOADING only BtlChars_ClearObjFlag2.
 *        frame counter          if started and BtlChars_IsTimeStopped() == 0: frame++, unk1C counts down
 *        BtlChars_CheckRoundReset
 *        BtlChars_UpdateFreeze  decides who is frozen this frame
 *        BtlCharSnd_ClearRequests          empties the manager's sound request list at +0xA0
 *        per fighter            BtlChar_BeginFrame: stage 3, previous-frame copies, per-frame clears,
 *                               BtlInput_Update, re-reads of member bonus / ability
 *        BtlChars_Snapshot(0)       snapshot 0 of every fighter's position
 *        BtlChars_UpdateSightFlag          two-fighter test that sets held flag 0xBA on both
 *        per fighter            BtlChar_UpdateSeqFlags: held flags 1..4 from the sequence state, 0x135
 *   4. BtlChars_UpdateMain      skipped under PAUSE / LOADING.
 *        per fighter            BtlChar_UpdateMotion: BtlMove_UpdateAction (the action state machine: BtlAct_Update
 *                               sets stages 4 and 5 itself), seven placement requests (BtlChar_PlaceRestart..), then
 *                               pose -> object, animation (BtlObjAnim_SamplePose, BtlObjAnim_UpdateEvents), matrices
 *                               (BtlObjPose_CalcMatrices), object -> pose
 *        per fighter            BtlChar_UpdateStage6: stage 6, BtlOpp_MirrorFlags, BtlPartner_Update
 *        BtlChars_UpdateHold          fighter against fighter push-out
 *        BtlChars_Snapshot(1)
 *        per fighter            BtlChar_UpdateStage7: stage 7, BtlMove_PushOut, BtlMove_ApplyOrbit, matrices
 *        BtlChars_Snapshot(2)
 *        per fighter            BtlChar_UpdateStage8: stage 8, BtlMove_ClampToStage (stage queries), matrices,
 *                               StgCol_UpdateFighter / StgGround_UpdateFighter on the object
 *        BtlChars_Snapshot(3)
 *        per fighter            BtlChar_UpdateStage9: stage 9, BtlColl_UpdateGround, matrices
 *        BtlChars_Snapshot(4)
 *        per fighter            BtlChar_UpdateCamera: ChrCam_StartCut, ChrCam_UpdateDemo, ChrCam_UpdateInput,
 *                               then the object's final placement, BtlChar_UpdateHead, matrices, BtlFx_UpdateAll
 *        BtlReplay_UpdateViewer, BtlFx_UpdateRoster, BtlMembers_UpdateQueuedDamage (gauges), BtlChars_UpdateCollision (hits)
 *        per fighter            BtlChar_UpdateStage10: stage 10, BtlPartner_UpdateEvents, BtlFx_UpdateAfterHits
 *        BtlClash_Update
 *      (Battle_Update then runs the effect scene: BtlScene_Update, EftDet_Update, BtlScene_PostUpdate)
 *   5. BtlChars_PostScene       skipped under PAUSE / LOADING. per fighter: BtlChar_PostScene (ChrCam_Update,
 *                               low-health state, the vector pushed onto the opponent).
 *      (Battle_Update: BtlScene_CheckStageChange, loader polls, stage, both cameras, BtlCam_UpdateOverride)
 *   6. BtlChars_EndFrame        skipped under LOADING. BtlChange_Update() runs even when paused; the rest is
 *                               skipped under PAUSE:
 *        per fighter            BtlChar_UpdateLate
 *        BtlChars_UpdateObjFlag2
 *        BtlCharSnd_PlayRequests          plays the sound request list at +0xA0
 *        per fighter            BtlChar_EndFrame: stage 11, BtlChar_RaiseEvents, BtlChar_UpdateVibration,
 *                               stage 12
 *        BtlChars_Snapshot(5)
 *
 * What the callees named func_XXXXXXXX do is from a first read of their code, not from matching C:
 *   BtlChar_SetStage(chr, n) sets the stage byte chr+0x1084 = n and moves the flag bits queued "for stage n"
 *                        from the pending arrays into the live ones (BtlChar_PromoteFlags)
 *   BtlChar_IsFlagRaised(chr, f) flag f went 0 -> 1 this frame;   BtlChar_IsFlagDropped(chr, f) went 1 -> 0
 *   BtlChar_SetFrameBits(chr, m) chr->frameBits |= m
 *   BtlAct_GetCurrent(chr)   chr->action;  BtlAct_GetCurrentClass(chr) a class number of the action
 *   BtlMember_Get(chr, n) &chr->members[n]; BtlMember_GetActive(chr) the current member; BtlMember_GetActiveGauge(chr) its gauge
 *   BtlMember_GetActiveIndex(chr)   chr->curMember; BtlMember_SetActiveIndex(chr, n) sets it; BtlMember_CountAlive(chr) members with health
 *   BtlMember_GetHealthRatio(chr)   health / healthMax of the current member; BtlMember_GetTeamHealthRatio(chr) the same over the team
 *   BtlMember_HasAbility(chr, n) the current member has ability bit n
 *   BtlMember_LoadParams(chr, member, init, variant, health)  loads a member's parameters
 *   BtlMember_AddHealth(chr, n) adds n health, clamped to the maximum
 *   BtlOpp_GetPlayer(chr)   the opponent's roster index (1 for side 0, else 0)
 *   BtlChars_IsTimeStopped()      gBtlChars + 0x274: non-zero while time is stopped
 *   BtlChar_PoseToObj(chr, f) writes the pose (position, rotation matrix) into the BtlObj
 *   BtlChar_ObjToPose(chr)   reads position / rotation back from the BtlObj into the pose
 *   BtlObjAnim_SamplePose, BtlObjAnim_UpdateEvents, BtlObjPose_CalcMatrices, BtlObjBody_Warp, BtlObjHit_BuildVolumes, BtlObj_SetColorPreset, BtlObj_BindCommonTables,
 *   BtlObj_SaveNodePositions, BtlObj_SetMoveVec, BtlObj_InitChains, BtlObj_UpdateChains   BtlObj (model / skeleton) updates
 *   BtlChars_Snapshot(n)     per fighter BtlChar_Snapshot(chr, &pose, &pose + 0x10, n): position snapshot n
 *   BtlParam_GetUnkAD(chr)   byte 0xAD of the object's parameter block (BtlObj + 0x91C)
 *   BtlAtk_GetId(chr)   id of the technique in use
 *   Vec4_SetZero(v)     zeroes a Vec4
 * BtlChar_GetObj / BtlChar_GetPos / BtlChar_IsFrozen / BtlUtil_Clamp / BtlUtil_Max and the ChrCam_ / BtlReplay_
 * names come from config/symbols (btl_replay.txt, btl_char_cam.txt); they are declared here with this
 * module's own view of the fighter.
 */

extern void *memset(void *dst, s32 c, u32 n);

extern s32 BtlChar_GetCount(void);
extern BtlMgrChr *BtlChar_Get(s32 idx);
extern void BtlChar_SetFlag(BtlMgrChr *chr, s32 flag);
extern s32 BtlChar_TestFlag(BtlMgrChr *chr, s32 flag);
extern void BtlChar_SetHeldFlag(BtlMgrChr *chr, s32 flag);
extern void BtlChar_ClearFlag(BtlMgrChr *chr, s32 flag);
extern void BtlInput_Init(BtlMgrChr *chr);
extern void BtlInput_Sample(BtlMgrChr *chr);
extern void BtlInput_Update(BtlMgrChr *chr);
extern void BtlInput_Stub(BtlMgrChr *chr);
extern s32 BtlInput_IsPressed(BtlMgrChr *chr, u32 mask);
extern s32 BtlCtrl_CanAct(s32 side);

extern void Vec4_SetZero(void *vec);
extern void BtlBodyHit_Update(void);
extern void StgGround_UpdateFighter(BtlMgrObj *obj);
extern void StgCol_UpdateFighter(BtlMgrObj *obj, s32 arg1, s32 arg2);
extern void BtlStat_ClearFrameMods(BtlMgrChr *chr);
extern void BtlStat_Reset(BtlMgrChr *chr);
extern void BtlStat_SetFrameMod(BtlMgrChr *chr, s32 idx, s32 val, s32 add);
extern void BtlAnim_Play(BtlMgrChr *chr, s32 arg1, f32 arg2);
extern void BtlAnim_FlushRequest(BtlMgrChr *chr);
extern void BtlAnim_SetObjRate(BtlMgrChr *chr, f32 rate);
extern void BtlAnim_SetRate(BtlMgrChr *chr, f32 rate);
extern s32 BtlAnim_GetId(BtlMgrChr *chr);
extern s32 BtlAnim_GetFlags(s32 idx);
extern void ChrCam_UpdateInput(BtlMgrChr *chr);
extern void ChrCam_Update(BtlMgrChr *chr);
extern void ChrCam_UpdateDemo(BtlMgrChr *chr);
extern void ChrCam_StartCut(BtlMgrChr *chr);
extern void BtlColl_Update(void);
extern void BtlColl_UpdateFrozen(BtlMgrChr *chr);
extern void BtlColl_UpdateGround(BtlMgrChr *chr);
extern void BtlColl_ClearActionBits(BtlMgrChr *chr);
extern void BtlMember_LoadParams(BtlMgrChr *chr, s32 member, s32 init, f32 health, s32 variant);
extern BtlMgrMember *BtlMember_Get(BtlMgrChr *chr, s32 idx);
extern BtlMgrMember *BtlMember_GetActive(BtlMgrChr *chr);
extern BtlMgrGauge *BtlMember_GetActiveGauge(BtlMgrChr *chr);
extern void BtlMember_SetActiveIndex(BtlMgrChr *chr, s32 member);
extern s32 BtlMember_CountAlive(BtlMgrChr *chr);
extern s32 BtlMember_GetActiveIndex(BtlMgrChr *chr);
extern s32 BtlMember_GetSwitchTarget(BtlMgrChr *chr);
extern void BtlMember_AddHealth(BtlMgrChr *chr, s32 amount);
extern f32 BtlMember_GetHealthRatio(BtlMgrChr *chr);
extern f32 BtlMember_GetTeamHealthRatio(BtlMgrChr *chr);
extern s32 BtlMember_HasAbility(BtlMgrChr *chr, s32 ability);
extern void BtlMembers_UpdateQueuedDamage(void);
extern void BtlFx_UpdateObjEvents(BtlMgrChr *chr);
extern void BtlFx_UpdateAll(BtlMgrChr *chr);
extern void BtlFx_UpdateAfterHits(BtlMgrChr *chr);
extern void BtlFx_UpdatePostScene(BtlMgrChr *chr);
extern void BtlFx_UpdateLate(BtlMgrChr *chr);
extern void BtlFx_UpdateRoster(void);
extern void BtlPartner_Release(BtlMgrChr *chr);
extern void BtlPartner_Update(BtlMgrChr *chr);
extern void BtlPartner_UpdateEvents(BtlMgrChr *chr);
extern void BtlChange_Reset(void);
extern void BtlChange_Update(void);
extern s32 BtlChars_IsTimeStopped(void);
extern void BtlChar_ResetLook(BtlMgrChr *chr);
extern void BtlChar_UpdateLookOffset(BtlMgrChr *chr);
extern void BtlChar_SetLookEnabled(BtlMgrChr *chr, s32 arg1);
extern void BtlChar_UpdateHead(BtlMgrChr *chr);
extern void BtlChar_ObjToPose(BtlMgrChr *chr);
extern void BtlChar_PoseToObj(BtlMgrChr *chr, s32 arg1);
extern void BtlChar_UpdateLean(BtlMgrChr *chr);
extern void BtlChar_PlaceAtStart(BtlMgrChr *chr);
extern void BtlChar_PlaceRestart(BtlMgrChr *chr);
extern void BtlChar_PlaceCenter(BtlMgrChr *chr);
extern void BtlChar_PlaceRelative(BtlMgrChr *chr);
extern void BtlChar_PlaceOnPath(BtlMgrChr *chr);
extern void BtlChar_PlaceCenterHigh(BtlMgrChr *chr);
extern void BtlChar_PlaceSaved(BtlMgrChr *chr);
extern void BtlChar_PlaceWarp(BtlMgrChr *chr);
extern void BtlChars_UpdateHold(void);
extern void BtlChar_ClearSnapshots(BtlMgrChr *chr);
extern void BtlChars_Snapshot(s32 pass);
extern void BtlChar_GetSnapDelta(BtlMgrChr *chr, void *vec, s32 arg2, s32 arg3);
extern void BtlChar_GetMoveSince(BtlMgrChr *chr, void *vec, s32 arg2);
extern void BtlReplay_Rewind(BtlMgrChr *chr);
extern void BtlReplay_ResetViewer(void);
extern void BtlReplay_UpdateViewer(void);
extern void BtlClash_Update(void);
extern void BtlCharSnd_Init(void);
extern void BtlCharSnd_ClearRequests(void);
extern void BtlCharSnd_PlayRequests(void);
extern void BtlCharSnd_PlayTechSounds(BtlMgrChr *chr);
extern void BtlChar_SetStage(BtlMgrChr *chr, s32 stage);
extern void BtlChar_ClearFlagRange(BtlMgrChr *chr, s32 first, s32 last);
extern s32 BtlChar_IsFlagRaised(BtlMgrChr *chr, s32 flag);
extern s32 BtlChar_IsFlagDropped(BtlMgrChr *chr, s32 flag);
extern void BtlChar_UpdateLockOn(BtlMgrChr *chr);
extern void BtlChars_UpdateSightFlag(void);
extern void BtlChar_SetFrameBits(BtlMgrChr *chr, u64 bits);
extern s32 BtlOpp_GetPlayer(BtlMgrChr *chr);
extern void BtlOpp_MirrorFlags(BtlMgrChr *chr);
extern s32 BtlUtil_Clamp(s32 val, s32 lo, s32 hi);
extern s32 BtlUtil_Max(s32 a, s32 b);
extern BtlMgrObj *BtlChar_GetObj(BtlMgrChr *chr);
extern BtlMgrPose *BtlChar_GetPos(BtlMgrChr *chr);
extern s32 BtlChar_IsFrozen(BtlMgrChr *chr);
extern s32 BtlChar_TestMemberUnk70(BtlMgrChr *chr);
extern void BtlChar_UpdateVibration(BtlMgrChr *chr);
extern void BtlChar_StopVoiceOnFlag(BtlMgrChr *chr);
extern void BtlChar_TickVoiceTimers(BtlMgrChr *chr);
extern void BtlMove_UpdateAnimVoice(BtlMgrChr *chr);
extern void BtlMove_UpdateAction(BtlMgrChr *chr);
extern void BtlMove_ClampToStage(BtlMgrChr *chr);
extern void BtlMove_ApplyOrbit(BtlMgrChr *chr);
extern void BtlMove_PushOut(BtlMgrChr *chr);
extern void BtlAct_ClearQueue(BtlMgrChr *chr);
extern s32 BtlAct_GetCurrent(BtlMgrChr *chr);
extern s32 BtlAct_GetCurrentClass(BtlMgrChr *chr);
extern s32 BtlCharApi_EnteredTechnique(s32 objId);
extern s32 BtlCharApi_IsSkillStart(s32 objId);
extern s32 BtlCharApi_IsChanging(s32 objId);
extern s32 BtlAtk_GetId(BtlMgrChr *chr);
extern s32 BtlParam_GetUnk0(BtlMgrChr *chr);
extern s32 BtlParam_GetUnkAD(BtlMgrChr *chr);
extern s32 BtlParam_GetAuraKind(BtlMgrChr *chr);
extern s32 BtlParam_GetUnk70(BtlMgrChr *chr);
extern s32 BtlParam_GetUnk72(BtlMgrChr *chr);
extern void BtlObjAnim_SamplePose(BtlMgrObj *obj);
extern void BtlObjAnim_UpdateEvents(BtlMgrObj *obj);
extern void BtlObjBody_Warp(BtlMgrObj *obj, void *vec);
extern void BtlObjHit_BuildVolumes(BtlMgrObj *obj);
extern void BtlObjPose_CalcMatrices(BtlMgrObj *obj);
extern void BtlObj_SetColorPreset(BtlMgrObj *obj, s32 arg1, s32 arg2);
extern void BtlObj_BindCommonTables(BtlMgrObj *obj);
extern void BtlObj_SaveNodePositions(BtlMgrObj *obj, s32 arg1);
extern void BtlObj_SetMoveVec(BtlMgrObj *obj, void *vec);
extern void BtlObj_InitChains(BtlMgrObj *obj);
extern void BtlObj_UpdateChains(BtlMgrObj *obj);

/* The word of the object's +0x1660 block that mirrors BtlChar_TestMemberUnk70(). */
#define OBJ_WORD_18028(obj) (*(s32 *)((obj)->unk1660 + 0x18028))

/* A table inside a data file: the header word gives its byte offset. */
#define FILE_TABLE(file, word) ((u32 *)(file) + ((u32 *)(file))[word] / 4)


/* Loader callback: a side's new character model is ready. */
void BtlChars_OnModelLoaded(s32 side) {
    BtlMgrChr *chr = BtlChar_Get(side);

    if (chr != NULL) {
        BtlChar_OnModelLoaded(chr);
    }
}
