#include "common.h"
#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/battle_work.h"
#include "battle/btl_facade.h"
#include "battle/btl_seq.h"

/*
 * Facade between the battle event script (the command interpreter at 0x259070..0x25BE58) and the battle
 * modules, 0x12BD58..0x12C9F0. See include/battle/btl_facade.h for who calls what.
 *
 * Nearly every function is a tail call, so what a wrapper passes through is not visible in its code: the
 * parameter lists below come from reading the targets. The targets are other modules, not decompiled; the
 * names given to them here (BtlCtrl_*, BtlObj_*SubState) are guesses recorded in
 * config/symbols/btl_scene.txt. BattleSide_*, BattleResult_Set and BtlEvent_* come from battle/battle_setup.h and
 * battle/battle_work.h; DemoCam_* are btl_cam's names at the time of writing, declared here as a local view.
 */

typedef struct Vec4 Vec4;

extern void *memset(void *dst, s32 c, u32 n);
extern void *BtlObj_Get(s32 id);

/* scripted camera, 0x23DD30..0x23DE58 (state at gp 0x2FEBCC); btl_cam's names (local view) */
extern void DemoCam_AddShake(f32 time);
extern void DemoCam_SetFixedPose(Vec4 *pos, Vec4 *rot);
extern void DemoCam_GetFixedPose(Vec4 *pos, Vec4 *rot);
extern void DemoCam_ClearFixed(void);

/* fighter object sub-state (object + 0x1664) */
extern void BtlObj_SetSubState(void *obj, s32 state, s32 arg);
extern s32 BtlObj_GetSubState(void *obj);

/* per-side controller block at gp 0x2FEB10 (two 0x520-byte entries) */
extern void BtlAiMgr_SetType(s32 side, s32 value);
extern void BtlAiMgr_SetLevel(s32 side, s32 value);

/* script control of a fighter, 0x20A050..0x20B200; `side` is the BtlChar_Get index */
extern void BtlCtrl_PlayMotion(s32 side, s32 type, s32 mode, f32 value);
extern void BtlCtrl_SetPos(s32 side, Vec4 *pos);
extern void BtlCtrl_SetRot(s32 side, Vec4 *dir);
extern s32 BtlCtrl_GetActiveMember(s32 side);
extern s32 BtlCtrl_IsAction4(s32 side);
extern s32 BtlCtrl_IsMotionPlaying(s32 side);
extern void BtlCtrl_StopMotion(s32 side);
extern void BtlCtrl_SetAuraOn(s32 side);
extern void BtlCtrl_SetAuraOff(s32 side);
extern void BtlCtrl_SetChargeFx(s32 side, s32 on);
extern void BtlCtrl_BurstChargeFx(s32 side);
extern void BtlCtrl_ClearHidden(s32 side);
extern void BtlCtrl_SetHidden(s32 side);
extern void BtlCtrl_ReloadMemberBonus(s32 side, s32 member);
extern void BtlCtrl_ReloadMemberAbilities(s32 side, s32 member);
extern void BtlCtrl_SetFlag10D(s32 side);
extern void BtlCtrl_ClearFlag10D(s32 side);
extern void BtlCtrl_AddHp(s32 side, s32 member, f32 ratio);
extern void BtlCtrl_RaiseHp(s32 side, s32 member, f32 ratio);
extern void BtlCtrl_LowerHp(s32 side, s32 member, f32 ratio);
extern void BtlCtrl_AddKi(s32 side, s32 member, s32 value);
extern void BtlCtrl_RaiseKi(s32 side, s32 member, s32 value);
extern void BtlCtrl_LowerKi(s32 side, s32 member, s32 value);
extern void BtlCtrl_AddBlast(s32 side, s32 member, s32 value);
extern void BtlCtrl_RaiseBlast(s32 side, s32 member, s32 value);
extern void BtlCtrl_LowerBlast(s32 side, s32 member, s32 value);
extern void BtlCtrl_SetMaxPower(s32 side, s32 on);
extern s32 BtlCtrl_Transform(s32 side, s32 id);
extern s32 BtlCtrl_Fuse(s32 side, s32 id);
extern s32 BtlCtrl_ChangeMember(s32 side, s32 member);
extern s32 BtlCtrl_ForceFlag11x(s32 side, s32 kind);
extern s32 BtlCtrl_UseTechnique(s32 side, s32 kind);
extern s32 BtlCtrl_ForceReaction(s32 side, s32 kind);
extern s32 BtlCtrl_IsInterruptible(s32 side);
extern s32 BtlCtrl_CanAct(s32 side);

/* BtlLoad_RequestStageChange(0x243470()): asks the loader for the destroyed version of the stage */
extern void BtlStage_RequestChange(void);

/* Shakes the scripted camera at full strength for `time` seconds. */
s32 BtlFacade_ShakeCamera(f32 time);

/* Switches the scripted camera to a fixed pose (position, rotation). */
void BtlFacade_SetFixedCamera(Vec4 *pos, Vec4 *rot);

/* Reads back the fixed camera pose. */
void BtlFacade_GetFixedCamera(Vec4 *pos, Vec4 *rot);

/* Turns the fixed camera off. */
void BtlFacade_ClearFixedCamera(void);

/* Puts the side's fighter object into sub-state 14 with an argument (0x24F5D8). */
void BtlFacade_SetObjSubState14(s32 side, s32 arg);

/* Puts the side's fighter object back to sub-state 0 if it is in sub-state 3. */
void BtlFacade_EndObjSubState3(s32 side);

/* Stores a value in word +8 of both sides' 0x1BBxxx controller and restarts it. */
void BtlFacade_SetCpuParam8(s32 arg);

/* Stores a value in word +4 of both sides' 0x1BBxxx controller and restarts it (no caller). */
void BtlFacade_SetCpuParam4(s32 arg);

/* Requests a fighter position (BtlCtrl_SetPos). */
void BtlFacade_SetCharPos(s32 side, Vec4 *pos);

/* Requests the fighter's second vector, +0x1570 (BtlCtrl_SetRot). */
void BtlFacade_SetCharRot(s32 side, Vec4 *dir);

/* Starts a scripted move of a fighter (BtlCtrl_PlayMotion). */
void BtlFacade_PlayCharMotion(s32 side, s32 type, s32 mode, f32 value);

/* Returns 1 when the scripted move has ended. */
s32 BtlFacade_IsCharMotionPlaying(s32 side);

/* Returns 1 when the fighter's action id is 4 (no caller). */
s32 BtlFacade_IsCharAction4(s32 side);

/* Cancels the scripted move. */
void BtlFacade_StopCharMotion(s32 side);

/* Sets control flag 0xFE and clears 0xFF. */
void BtlFacade_SetCtrlFE(s32 side);

/* Clears control flag 0xFE and sets 0xFF. */
void BtlFacade_SetCtrlFF(s32 side);

/* Sets control flag 0x101. */
void BtlFacade_SetCtrl101(s32 side) {
    BtlCtrl_SetChargeFx(side, 1);
}

/* Clears control flag 0x101. */
void BtlFacade_ClearCtrl101(s32 side);

/* Sets control flag 0x102. */
void BtlFacade_SetCtrl102(s32 side);

/* Clears control flag 0x100. */
void BtlFacade_ClearCtrl100(s32 side);

/* Sets control flag 0x100. */
void BtlFacade_SetCtrl100(s32 side);

/* Sets control flag 0x10D. */
void BtlFacade_SetCtrl10D(s32 side);

/* Clears control flag 0x10D. */
void BtlFacade_ClearCtrl10D(s32 side);

/* Returns the index of the side's team member that is fighting. */
s32 BtlFacade_GetActiveMember(s32 side);

/* Raises the two per-member control flags (0x103 + member, 0x108 + member). */
void BtlFacade_NotifyMemberItems(s32 side, s32 member);

/* Stores a member's eight item ids (+1) in the setup and raises the per-member flags. */
void BtlFacade_SetMemberItems(s32 side, s32 member, BtlFacadeItem *src);

/* Adds ratio * max to a member's HP (damage or heal through the fighter when it is the active one). */
void BtlFacade_AddHp(s32 side, s32 member, f32 value);

/* Raises a member's HP to at least ratio * max. */
void BtlFacade_RaiseHp(s32 side, s32 member, f32 value);

/* Lowers a member's HP to at most ratio * max; a ratio <= 0 also raises the KO events. */
void BtlFacade_LowerHp(s32 side, s32 member, f32 value);

/* Adds n * 20000 to a member's gauge +0xC. */
void BtlFacade_AddGaugeC(s32 side, s32 member, s32 value);

/* Raises a member's gauge +0xC to at least n * 20000. */
void BtlFacade_RaiseGaugeC(s32 side, s32 member, s32 value);

/* Lowers a member's gauge +0xC to at most n * 20000. */
void BtlFacade_LowerGaugeC(s32 side, s32 member, s32 value);

/* Adds n * 100000 to a member's gauge +0x14 (no caller). */
void BtlFacade_AddGauge14(s32 side, s32 member, s32 value);

/* Raises a member's gauge +0x14 to at least n * 100000. */
void BtlFacade_RaiseGauge14(s32 side, s32 member, s32 value);

/* Lowers a member's gauge +0x14 to at most n * 100000. */
void BtlFacade_LowerGauge14(s32 side, s32 member, s32 value);

/* Fills gauge +0xC, sets the 30000 timer and control flag 6, or clears flag 6. */
void BtlFacade_SetMaxPower(s32 side, s32 on);

/* Makes the fighter use the technique with this id from its 4-slot list; BtlEvent_SetWaitOff(0) on success. */
void BtlFacade_Transform(s32 side, s32 id);

/* Makes the fighter use the technique with this id from its 3-slot list; BtlEvent_SetWaitOff(0) on success. */
void BtlFacade_Fuse(s32 side, s32 id);

/* Makes the side switch to another team member; BtlEvent_SetWaitOff(0) on success. */
void BtlFacade_ChangeMember(s32 side, s32 member);

/* Clears then sets control flag 0x10D (no caller). */
void BtlFacade_PulseCtrl10D(s32 side);

/* Returns 1 when both fighters are in an action the script may interrupt. */
s32 BtlFacade_AreBothInterruptible(void);

/* Returns 1 when the fighter can take a scripted action now. */
s32 BtlFacade_CanCharAct(s32 side);

/* Forces action 0 or 1 on a side and the matching reaction on the other. */
void BtlFacade_ForceAction01(s32 side, s32 arg);

/* Forces action 2 or 3 on a side and the matching reaction on the other. */
void BtlFacade_ForceAction23(s32 side, s32 arg);

/* Forces action 4 on a side and the matching reaction on the other. */
void BtlFacade_ForceAction4(s32 side);

/* Empty. */
void BtlFacade_Nop(void);

/* Raises forced-action flag 0x111 on both sides. */
void BtlFacade_ForceBoth111(void);

/* Raises forced-action flag 0x110 on both sides. */
void BtlFacade_ForceBoth110(void);

/* Forces one action per side. */
void BtlFacade_ForceActions(s32 arg0, s32 arg1);

/* Runs the sequence state's extra handler. */
s32 BtlFacade_CallSeqExtra(void);

/* Same as BtlFacade_CallSeqExtra (second script command). */
s32 BtlFacade_CallSeqExtra2(void);

/* Restarts the sequence's second clock. */
s32 BtlFacade_ResetSubClock(void);

/* Turns the end-of-battle check off or on (no caller). */
void BtlFacade_SetEndCheckOff(s32 off);

/* Returns whether the end-of-battle check is off (no caller). */
s32 BtlFacade_GetEndCheckOff(void);

/* Requests the stage change of the current stage. */
void BtlFacade_RequestStageChange(void);

/* Sets battle flag 0x200. */
void BtlFacade_SetFlag200(void);

/* Clears battle flag 0x200. */
void BtlFacade_ClearFlag200(void);

/* Stores one of four battle results. */
void BtlFacade_SetResult(s32 kind);

/* Returns 1 while the sequence is not in the finish state. */
s32 BtlFacade_IsNotFinished(void);

/* Starts a script interrupt of the fight. */
void BtlFacade_BeginInterrupt(void);

/* Ends a script interrupt. */
void BtlFacade_EndInterrupt(void);

/* Calls BtlEvent_SetWaitOff(1): the script starts waiting for a forced action. */
void BtlFacade_BeginWait(void);

/* Returns the script wait state. */
s32 BtlFacade_IsWaitOff(void);
