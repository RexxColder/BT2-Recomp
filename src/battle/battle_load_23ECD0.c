#include "common.h"
#include "battle/battle_work.h"
#include "battle/battle_setup.h"
#include "battle/btl_seq.h"
#include "sys/common.h"
#include "sys/file.h"
#include "sys/heap.h"
#include "sys/job.h"
#include "sys/loading.h"
#include "sys/save.h"

/*
 * Battle loader, result block, events, battle setup and replay block: 0x127120..0x12B570, one object file in
 * the original (its .rodata only lines up as one object: the jump table of BtlLoad_StepStageChange at +0, the
 * time-event table of BtlEvent_RaiseTimeEvents at +0x28, the jump tables of BattleSetup_FixForMode and
 * BattleSetup_FinishEx at +0x80 and +0xA0; original addresses 0x2EC350, 0x2EC378, 0x2EC3D0, 0x2EC3F0).
 *
 *   0x127120..0x129170  loader job pool, the five job step functions, load requests, result accessors
 *                       (what a load does step by step: include/battle/battle_work.h)
 *   0x129170..0x12B570  result finish, per-side event bits, setup builders and getters, replay block
 *                       (include/battle/battle_setup.h)
 * The battle block itself is described in include/battle/battle.h.
 *
 * The battle work accessors at 0x126EC8..0x127120 are a separate translation unit (src/battle/battle_work.c):
 * with Battle_GetWork or Battle_GetEventWork defined earlier in this file, ee-gcc 2.96 fills the branch delay
 * slots of BtlLoad_StepStageReload / StepObject / StepChara / StepInitial differently and they do not match.
 * For the same reason the order of the functions here must stay the original one: the loader functions call
 * the setup getters that are defined after them.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern s32 rand(void);

extern BtlJobPool gBtlJobPool;
extern s32 gBtlLoadHandle; /* handle of the model BtlLoad_StepObject is loading */
extern s32 gBtlLoadObj;    /* object made from it */

/* sys/file.h declares File_Request with two parameters (it ignores a third); every caller here passes the
 * buffer size as a third argument, so the calls go through a cast. */
#define File_Request3(id, buf, size) ((void *(*)(s32, void *, s32))File_Request)(id, buf, size)

extern void Fade_Start(s32 idx, s32 dir, f32 seconds);
extern s32 Fade_IsDone(s32 idx);
extern void Snd_LoadBank(s32 mask, void *data, s32 arg);
extern void Snd_UnloadBank(s32 mask);
extern void Res_RelocateOffsets(void *out, void *base, void *hdr);
extern s32 BtlObj_Get(s32 id);

/* Sound driver. */
extern void Snd_Reset(void);                         /* clears the 8 bank slots' transfer state */
extern void Snd_ReloadBank(s32 mask, void *data, s32 arg); /* reloads a bank from a buffer that stays allocated */
extern s32 Snd_IsUploadDone(void);                          /* 1 when no bank slot has a transfer pending */

extern void BtlScene_FreeChar(s32 side);
extern void BtlScene_CreateChar(s32 side);

/* Stage / scene. */
extern void StgModel_InitStage(void);
extern void EftStage_Recreate(void);
extern void EftStage_ResetAll(void);
extern void EftBurst_Start(void);
extern s32 EftBurst_IsBusy(void);
extern void EftBurst_End(void);
extern void StgNav_Rebind(void);
extern void BtlStage_Term(void);
extern void StgFx_SetDisabled(s32 arg);
extern void StgFx_Reset(void);

/* Fighters. */
extern void BtlAiMgr_ResetSide(s32 side);
extern void BtlChars_OnModelLoaded(s32 side);
extern void BtlChars_OnStageLoaded(void);
extern s32 BtlChange_IsPendingType0(s32 side); /* pending request of type 0 for this side */
extern s32 BtlChange_IsPendingType1(s32 side); /* pending request of type 1 for this side */
extern void BtlChange_GetArgs(s32 *a, s32 *b, s32 *c, s32 *d, s32 *e, s32 *f, s32 *g); /* request words +8..+0x20 */
extern void BtlChange_NotifyTaken(void);    /* request taken */
extern void BtlChange_NotifyLoaded(void);    /* request's files are in */
extern s32 BtlChange_IsReady(void);     /* request state == 4 and not paused */
extern void BtlCtrl_AttachPartner(s32 side, s32 handle, s32 obj);
extern s32 BtlSide_GetActiveMember(s32 side); /* member index */
extern s32 BtlCtrl_IsSwitching(s32 side);

/* Battle objects / models. */
extern s32 BtlObj_Create(s32 slot, s32 model, s32 arg);
extern s32 BtlObj_CreateChara(s32 id);
extern void BtlObj_Rebind(s32 objId, s32 id);
extern s32 BtlObj_RequestCharaModel(s32 side, s32 chara, s32 costume, s32 variant);
extern void BtlRes_CommitReloadEx(void);
extern void BtlObj_Init(s32 arg);
extern void BtlObj_Term(void);
extern s32 BtlRes_Request(s32 arg, s32 file, s32 file8, s32 file9);
extern s32 BtlRes_GetSlot(s32 handle);
extern void BtlRes_Reload(s32 id, s32 file, s32 file8, s32 file9);
extern void BtlRes_CommitReload2(void);
extern void BtlObjAnim_PlayAuto(s32 obj, s32 arg, s32 arg2);
extern void BtlObjAnim_PlayModel(s32 obj, s32 arg, s32 arg2);

/* Script / message objects. */
extern void Gsc_InitDefault(s32 *tbl);
extern void Gsc_Exit(void);
extern s32 Gsc_LoadFile(void *data);
extern void Gsc_UnloadFile(s32 script);
extern s32 Gsc_StartMain(s32 script);
extern void Gsc_RunAction(s32 script, s32 arg);
extern void BtlScript_Init(void);
extern void BtlScript_Nop(void);
extern void BtlScript_ScanEvents(s32 script);
extern void BtlScript_Restart(void);
extern void BtlScript_Free(void);

#define BATTLE_RES ((BattleRes *)((u8 *)gCommonRes + 0x20))

/* Returns the loader job pool. */
BtlJobPool *BtlJob_GetPool(void);

/* Clears the job pool and puts all 8 jobs on its free list. */
void BtlJob_InitPool(void);

/* Takes a zeroed job from the pool; NULL when all 8 are in use. */
BtlJob *BtlJob_Alloc(void);

/* Gives a job back to the pool. */
s32 BtlJob_Free(BtlJob *job);

/* Number of jobs not in use. */
s32 BtlJob_GetFreeCount(void);

/* Shuts the stage-dependent systems down before the stage file is replaced. */
void BtlLoad_BeginStageSwap(void);

/* Brings them back up on the new stage. */
void BtlLoad_EndStageSwap(void);

/* Job: reloads the stage model and stage sound bank (no transition). */
s32 BtlLoad_StepStageReload(BtlJob *job);

/* Job: in-battle stage change, with the transition scene and a fade out / in. */
s32 BtlLoad_StepStageChange(BtlJob *job);

/* Job: loads one extra model and makes a battle object from it. */
s32 BtlLoad_StepObject(BtlJob *job);

/* Job: loads a side's character (model, voice bank, data block) and swaps it in. */
s32 BtlLoad_StepChara(BtlJob *job);

/* Job: the first load of a battle. */
s32 BtlLoad_StepInitial(BtlJob *job);

/* Starts a plain stage reload unless a load is running or the stage is already loaded. */
s32 BtlLoad_RequestStageReload(s32 stage);

/* Starts an in-battle stage change (with fade) under the same conditions. */
s32 BtlLoad_RequestStageChange(s32 stage);

/* Per frame: turns a pending type-1 request of the fighter manager into a BtlLoad_StepObject job. */
void BtlLoad_PollObjectRequest(void);

/* Per frame: turns a pending type-0 request (character change) into a BtlLoad_StepChara job. */
void BtlLoad_PollCharaRequest(void);

/* Restart: drops running jobs and reloads the initial stage / characters where they changed (blocking). */
void BtlLoad_Reload(void);

/* Resets the job pool and queues the first load. */
void BtlLoad_PushInitialJob(void);

/* Frees every buffer of the first load and unloads the four battle sound banks. */
void BtlLoad_FreeAll(void);

/* Zeroes the result block. */
void BattleResult_Clear(void);

/* Stores the winner bits and the reason bits; a restart reason is forwarded to BattleReplay_SetActive. */
void BattleResult_Set(s32 flags, s32 reason);

/* The battle was left without a finish (winner bit 3). */
s32 BattleResult_IsAborted(void);

/* A restart was asked for (reason bits 15 / 16). */
s32 Battle_IsRematchRequested(void);

/* One of the sides won. */
s32 BattleResult_HasWinner(void);

/* Side 0 won; always 1 in split-screen and in modes 8 and 1. */
s32 BattleResult_IsPlayerWin(void);

/* Reason bit 20. */
s32 BattleResult_IsReasonBit20(void);

/* Index of the winning side: 1 only when side 1 won and side 0 did not. */
s32 BattleResult_GetWinnerSide(void);

/* Reason bit 0: K.O. */
s32 BattleResult_IsKo(void);

/* Reason bit 1: time up. */
s32 BattleResult_IsTimeUp(void);

/* Reason bit 2. */
s32 BattleResult_IsReasonBit2(void);

/* Reason bit 18. */
s32 BattleResult_IsReasonBit18(void);

/* Reason bits 5 or 6. */
s32 BattleResult_IsReasonBit5or6(void);

/* Event 0x59 is clear in the winning side's event set. */
s32 BattleResult_IsWinnerEvent59Clear(void);

/* Event 0x3C is set in the given event set. */
s32 BattleResult_IsEvent3CSet(s32 side);

#define RESULT_EVENT(ev, bit) \
    if (BtlEvent_WasRaised(0, ev)) { \
        result->eventSummary |= (bit); \
    }

/* Rebuilds the result's 64-bit event summary from event set 0. */
void BattleResult_CollectEvents(BattleResult *result);

/*
 * ---------------------------------------------------------------------------------------------------------
 * Second half, 0x129170..0x12B570: result finish, the per-side event bits, the battle setup builders and
 * getters, and the replay block. include/battle/battle_setup.h describes how they are used.
 * ---------------------------------------------------------------------------------------------------------
 */

/* Other modules called by the setup half. */
s32 BtlFacade_AreBothInterruptible(void);  /* BtlCtrl_IsInterruptible(0) && BtlCtrl_IsInterruptible(1): both fighters ready */
void BtlFacade_SetFlag200(void); /* battle flags |= 0x200 */
void BtlFacade_ClearFlag200(void); /* battle flags &= ~0x200 */
void BtlFacade_ClearFixedCamera(void); /* tail call of DemoCam_ClearFixed (camera module) */
void BtlScript_StartWaitEvents(void); /* script module: reacts to events 0x5A / 0x5B */
void Hud_SlideOut(f32 t); /* five HUD parts (0x21FAF0, 0x21AD40, 0x22F2F0, 0x22E0B0, 0x2240A0), duration t */
void Hud_SlideIn(f32 t); /* their counterparts (0x21FB18, ...), duration t */
/* Sums the four stat bonuses and ORs the four ability words of the items; stats[4] = AI type. */
void ItemSet_GetStats(BattleItemSet *items, s32 *stats, s32 *ability, s32 chara);

#define SETUP() Battle_GetSetup()

/*
 * Side and member lookups. The original computes `setup + side * 0x270` first and adds the field offset
 * last, which only comes out when the setup pointer and the element pointer are locals (as here);
 * `SETUP()->sides[n].field` written in one expression adds the operands the other way round.
 */
static inline BattleSide *Side(s32 n);

static inline BattleMember *Member(s32 n, s32 i);

/* Adds one to result.frames on the frame after event 0x48 of side 0 is newly raised. */
void BattleResult_CountFrame(void);

/* Empty. */
void BattleResult_Stub1291B8(void);

/* Fills the result block at the end of the battle: event summary, clock copy, abort flag, forced winner. */
void BattleResult_Finish(void);

/* Returns result.flags (winner / draw / abort bits). */
s32 BattleResult_GetFlags(void);

/* Returns result.reason. */
s32 BattleResult_GetReason(void);

/* Returns result.eventSummary (64-bit). */
u64 BattleResult_GetEventSummary(void);

/* Returns the result block (wrapper of Battle_GetResult). */
BattleResult *BattleResult_GetPtr(void);

/* Converts a clock to whole seconds. */
s32 BtlClock_ToSeconds(BtlClock *clock);

/* Raises time event i (0..18) on both sides every frame once the sub clock has reached tbl[i] seconds. */
void BtlEvent_RaiseTimeEvents(void);

/* Per-frame handling of the pending interrupt (event 0x4C), the wait flag (events 0x4D / 0x4E) and event 0x4F. */
void BtlEvent_UpdateRequests(void);

/* End of frame for one side: prev = now, held |= now, now = 0. */
void BtlEventSet_Rotate(BattleEventSet *set);

/* Sets bit n of a 64-bit word array. */
void BtlEvent_SetBit(u64 *bits, s32 n);

/* 1 when event n is raised in `now` and was not in `prev`. */
s32 BtlEventSet_IsNew(BattleEventSet *set, s32 n);

/* 1 when event n was raised at any time since the last reset. */
s32 BtlEventSet_WasRaised(BattleEventSet *set, s32 n);

/* Zeroes the whole event work. */
void BtlEvent_ClearAll(void);

/* Zeroes the event work but keeps its first word (the script handle). */
void BtlEvent_Reset(void);

/* Raises event ev for a side; events 0x5A and 0x5B also notify the script module. */
void BtlEvent_Raise(s32 side, s32 ev);

/* BtlEventSet_IsNew on a side. */
s32 BtlEvent_IsNew(s32 side, s32 ev);

/* BtlEventSet_WasRaised on a side. */
s32 BtlEvent_WasRaised(s32 side, s32 ev);

/* Once per unpaused frame: requests, rotate both sides, then raise the time events for the new frame. */
void BtlEvent_Update(void);

/* Asks for event 0x4C: sets the pending word and battle flag 0x200, and fades the HUD out over 1.0. */
void BtlEvent_BeginInterrupt(void);

/* Fades the HUD back in over 1.0. */
void BtlEvent_EndInterrupt(void);

/* Stores the wait flag: waitFlag = (off == 0). */
void BtlEvent_SetWaitOff(s32 off);

/* 1 when the wait flag is clear. */
s32 BtlEvent_IsWaitOff(void);

/* Clamps the eight bonus levels of a member to -20..20, or -20..60 when wide. */
void BtlMember_ClampBonus(BattleMember *m, s32 wide);

/* Recomputes bonus levels, AI type and ability bits of a member from its equipped items. */
void BtlMember_ApplyItems(BattleMember *m);

/*
 * Clears a member and fills it: items (optional), character, costume, variant, CPU level, health.
 * BtlMember_ApplyItems runs while m->chara is still 0, so without an AI item the AI type is the one of
 * character 0, whatever `chara` is.
 */
void BtlMember_Init(BattleMember *m, s32 chara, s32 costume, s32 variant, s32 cpuLevel, f32 health,
                    BattleItemSet *items);

/* Forces the settings a mode does not allow (split-screen, time limit, team size, who is CPU). */
void BattleSetup_FixForMode(void);

/* Sets a side's usable-character bits: a copy of src, or the save's unlocked characters. */
void BattleSetup_InitCharaBits(BattleCharaBits *dst, BattleCharaBits *src);

/* Unless options were given, takes the two per-side options from the save data. */
void BattleSetup_DefaultOptions(void);

/* Zeroes the setup and writes its magic "btls" and version 7. */
void BattleSetup_Clear(void);

/* Clears bit 0 of the replay data flags. */
void BattleReplay_ClearDataFlag(void);

/* Selects battle script n (stored + 1; 0 = no script). */
void BattleSetup_SetScript(s32 script);

/* Sets the two per-side options explicitly. */
void BattleSetup_SetOptions(s32 optA0, s32 optA1, s32 optB0, s32 optB1);

/* Sets option word 0x14 and takes the per-side options from the save data. */
void BattleSetup_SetOption14(s32 val);

/* Sets the battle rules; bgm 24 means a random one of 0..23. */
void BattleSetup_SetRule(s32 screenMode, s32 mode, s32 bgm, s32 timeLimit, s32 announcer, s32 stage, s32 unk10);

/* Sets one side: who controls it, pad, team size, options, lead member and usable characters. */
void BattleSetup_SetSide(s32 sideNo, s32 control, s32 pad, s32 memberCount, s32 unk1FC, s32 unk200, s32 lead,
                   BattleCharaBits *bits);

/* Sets one team member from 0-based item ids stored in 32-bit words. */
void BattleSetup_SetMemberByItemIds(s32 sideNo, s32 idx, s32 chara, s32 costume, s32 variant, s32 cpuLevel,
                                    f32 health, u32 *itemIds);

/* Sets one team member (items: 1-based u16 ids or NULL). */
void BattleSetup_SetMember(s32 sideNo, s32 idx, s32 chara, s32 costume, s32 variant, s32 cpuLevel, f32 health,
                           BattleItemSet *items);

/* Sets entry idx of the opponent pool and the pool size. */
void BattleSetup_SetPoolMember(s32 count, s32 idx, s32 chara, s32 costume, s32 variant, s32 cpuLevel, f32 health,
                               BattleItemSet *items);

/* BattleSetup_FinishEx(0). */
void BattleSetup_Finish(void);

/* Last step of a setup: mode fix-ups, lead character, bonus clamps, rule.unk18, options, replay copy. */
void BattleSetup_FinishEx(s32 wide);

/* Returns the replay block (and its size) for saving; clears its two trailing words. */
BtlReplay *BattleReplay_GetBuffer(s32 *size);

/* Installs a loaded replay block: its setup becomes the battle setup. Returns 1 when the block is valid. */
s32 BattleReplay_Load(BtlReplay *buf, s32 size);

/* Non-zero while the battle plays a replay. */
s32 BattleReplay_IsActive(void);

/* Non-zero when the replay block came from BattleReplay_Load. */
s32 BattleReplay_IsLoaded(void);

/* Returns the recorded data part of the replay block. */
BtlReplayRec *BattleReplay_GetData(void);

/* 1 when no replay is active, else bit 0 of the replay data flags. */
s32 BattleReplay_TestDataFlag(void);

/* Sets the replay-active word. */
void BattleReplay_SetActive(s32 active);

/* First side whose control is 0 (a pad), or -1. */
s32 Battle_GetHumanSide(void);

/* Returns option word 0x14. */
s32 Battle_GetOption14(void);

/* Returns the battle script number, -1 when there is none. */
s32 Battle_GetScript(void);

/* 1 when the battle is drawn in split-screen. */
s32 Battle_IsSplitScreen(void);

/* Returns the battle mode (BATTLE_MODE_*). */
s32 Battle_GetMode(void);

/* Time limit in seconds (-1 = none). */
s32 Battle_GetTimeLimit(void);

/* 1 when the time limit setting is 0 (no limit). */
s32 Battle_IsTimeLimitOff(void);

/* Returns the announcer voice (0..7). */
s32 Battle_GetAnnouncer(void) {
    return SETUP()->rule.announcer;
}

/* Returns the BGM number. */
s32 Battle_GetBgm(void);

/* Returns the stage the battle starts on. */
s32 Battle_GetStartStage(void);

/* Returns the current stage. */
s32 Battle_GetStage(void);

/* Sets the current stage. */
void Battle_SetStage(s32 stage);

/* 1 when the current stage is not the starting one. */
s32 Battle_IsStageChanged(void);

/* Current stage = starting stage. */
void Battle_ResetStage(void);

/* Returns rule word 0x10 (setup + 0x18). */
s32 Battle_GetRuleUnk10(void) {
    return SETUP()->rule.unk10;
}

/* Per-side option A (save 0x1694 by default). */
s32 BattleSide_GetOptionA(s32 side);

/* Per-side option B (save 0x1698 by default). */
s32 BattleSide_GetOptionB(s32 side);

/* Returns the side's controller number. */
s32 BattleSide_GetPad(s32 side);

/* Returns who controls the side (0 pad, 2 CPU). */
s32 BattleSide_GetControl(s32 side);

/* 1 when the side is CPU controlled. */
s32 BattleSide_IsCpu(s32 side);

/* Returns side word 0x200. */
s32 BattleSide_GetUnk200(s32 side);

/* Returns side word 0x1FC. */
s32 BattleSide_GetUnk1FC(s32 side);

/* Character the side starts the battle with. */
s32 BattleSide_GetStartChara(s32 side);

/* Costume the side starts the battle with. */
s32 BattleSide_GetStartCostume(s32 side);

/* Model variant the side starts the battle with. */
s32 BattleSide_GetStartVariant(s32 side);

/* Character currently loaded for the side. */
s32 BattleSide_GetChara(s32 side);

/* Sets the character currently loaded for the side. */
void BattleSide_SetChara(s32 side, s32 chara);

/* 1 when the current character is not the starting one. */
s32 BattleSide_IsCharaChanged(s32 side);

/* Current character = starting character. */
void BattleSide_ResetChara(s32 side);

/* Character of team member idx. */
s32 BattleSide_GetMemberChara(s32 side, s32 idx);

/* Costume of team member idx. */
s32 BattleSide_GetMemberCostume(s32 side, s32 idx);

/* Model variant of team member idx. */
s32 BattleSide_GetMemberVariant(s32 side, s32 idx);

/* Team size of the side. */
s32 BattleSide_GetMemberCount(s32 side);

/* Object id of the side's fighter (argument of BtlObj_Get). */
s32 BattleSide_GetObjId(s32 side);

/* Returns side word 0x26C (model slot from BtlObj_RequestCharaModel). */
s32 BattleSide_GetModelSlot(s32 side);

/* Sets the object id of the side's fighter. */
void BattleSide_SetObjId(s32 side, s32 objId);

/* Sets side word 0x26C. */
void BattleSide_SetModelSlot(s32 side, s32 slot);

/* Sets the currently loaded character, costume and variant. */
void BattleSide_SetForm(s32 side, s32 chara, s32 costume, s32 variant);

/* 1 when the current character, costume or variant differs from the starting one. */
s32 BattleSide_IsFormChanged(s32 side);

/* Returns team member idx of a side. */
BattleMember *BattleSide_GetMember(s32 side, s32 idx);

/* Replaces a member's items and recomputes what derives from them; nothing when items is NULL. */
void BattleSide_SetMemberItems(s32 side, s32 idx, BattleItemSet *items);

/* 1 when character id is in the side's usable-character bits. */
s32 BattleSide_IsCharaUsable(s32 side, s32 chara);
