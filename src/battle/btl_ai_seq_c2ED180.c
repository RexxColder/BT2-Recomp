#define Rand_Range func_002EA050  /* fix_targets */ /* the original uses 0x2ea050 here */
#include "common.h"
#include "battle/btl_ai_int.h"
#include "battle/btl_ai_seq_a.h"

/*
 * CPU player, first object: 0x1B4140..0x1B6D50 (the former btl_ai_seq_a.c, 0x1B4140..0x1B6008, merged at
 * integration in front of the code that was here before: step handlers 14..23 and BtlAi_RunSeq, see the separator
 * comment further down). The rule conditions that follow are btl_ai_cond.c.
 *
 * First part: the generic scripted action ("sequence"), 0x1B4140..0x1B6008. The object itself starts at 0x1B3F78
 * (BtlAiSeq_Reset / BtlAiSeq_PushRule, eft_det_b_c.c).
 *
 * An action id on top of the sequence stack that BtlAi_RunSeq does not run itself (3, 7, 0x19, 0x1A, 0x36) is a
 * script in the common AI data: a list of steps (BtlAiSeqStep: the AI buttons to hold / press / tap, the state
 * class the fighter is in once the input has taken effect, and the handler that says when the step is over), and
 * per action a flag word, a timeout in seconds and a "pick" function. Steps carry a group number; the action
 * plays one step of group 0, then one of group 1, and so on, and ends when a group has no step. The pick function
 * chooses among the alternatives of the group and usually also sets the step's parameter (seq->timer) from the
 * argument byte of the rule that queued the action.
 *
 * Phases (gBtlAiStateFuncs): 0 init -> 1 start -> 2 run -> (step finished: 1 again, next group) ... -> 3 end.
 * Init, start and run call each other directly, so a new action sends its first input on the frame it starts;
 * a finished step costs one frame without input (the run phase returns before BtlAiPad_Set).
 *
 * The stick is never used here: every BtlAiPad_Set of this file passes x = y = 0. Directions are the four
 * direction button bits of the step.
 *
 * Random numbers: only Rand_Range, in the pick functions (see each one); the phases and the step handlers 0..13
 * draw none, except through AiThink_RollActRate when the last action of a plan ends.
 */

typedef struct BtlAiSeqData {
    /* 0x00 */ s32 size[0x29];
    /* 0xA4 */ BtlAiSeqActTable *act;
    /* 0xA8 */ void *rules[8];
    /* 0xC8 */ u8 *profile[32];
} BtlAiSeqData;

#define AI_DATA ((BtlAiSeqData *)gBtlAi->data)
#define SEQA(ai) ((BtlAiSeqA *)&(ai)->seq)
#define ABS(x) ((x) < 0 ? -(x) : (x))

extern BtlAiPickFunc gBtlAiPickFuncs[16];
extern BtlAiStepFunc gBtlAiStepFuncs[24];

extern void BtlAiPad_Set(BtlAiWork *ai, s32 hold, s32 press, s32 once, s16 special, f32 x, f32 y);
extern s32 BtlAiSense_IsBehindOpponent(BtlAiWork *ai);
extern s32 AiThink_RollActRate(BtlAiWork *ai, s32 cond);
extern s32 AiThink_GetBlastStep(BtlAiWork *ai);
extern f32 BtlCharApi_GetAltitude(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern f32 BtlStage_GetTop(void);
extern f32 BtlStage_GetInnerRadius(void);
extern void BtlCharApi_GetPos(s32 objId, BtlAiVec *out);
extern void BtlCharApi_GetRot(s32 objId, BtlAiVec *out);
extern f32 BtlCharApi_GetChargeRate(s32 objId);
extern s32 BtlCharApi_AnyHasFlag128(void);
extern s32 BtlCharApi_GetUnkD74Diff(s32 objId);
extern s32 BtlCharApi_PickFusionSlot(s32 objId);
extern s32 BtlCharApi_PickTransformSlot(s32 objId);
extern s32 BtlCharApi_GetActiveMember(s32 objId);
extern s32 BtlCharApi_GetMemberCount(s32 objId);
extern s32 BtlCharApi_GetMemberHpPercent(s32 objId, s32 member);
extern s32 BtlCharApi_GetMemberKiPercent(s32 objId, s32 member);
extern s32 BtlCharApi_GetSwitchTarget(s32 objId);
extern s32 BtlCharApi_IsBlockedByOpponent(s32 objId);
extern u64 BtlCharApi_GetUnk1288(s32 objId);
extern s32 BtlCharApi_CheckUnkCAC(s32 objId);
extern s32 BtlCharApi_IsBlastPassing(s32 objId);
extern s32 BtlCharApi_GetBlastShots(s32 objId);
extern f32 Vec3_Length(BtlAiVec *v);
extern void Vec3_Normalize(BtlAiVec *dst, BtlAiVec *src);
extern void Vec3_Scale(BtlAiVec *dst, BtlAiVec *src, f32 s);
extern void Vec3_Add(BtlAiVec *dst, BtlAiVec *a, BtlAiVec *b);
extern void Vec3_Sub(BtlAiVec *dst, BtlAiVec *a, BtlAiVec *b);
extern f32 Vec3_Dot(BtlAiVec *a, BtlAiVec *b);
extern void Vec3_RotateY(BtlAiVec *dst, BtlAiVec *src, f32 angle); /* rotate about Y */
extern f32 sinf(f32 x);
extern f32 cosf(f32 x);

/* ---- Helpers of the phases ---- */

/* 1 when the action's flag word says it has to end now: the fighter is in state class 1..7 (flag 1, unless step
 * handler 15 set BTLAI_SEQ_NO_HIT_END), it is in state class 0x20 or in a clash (flag 8), or the opponent is using
 * a technique that has a kind byte (flag 0x10). Also called by the dispatchers of actions 7, 0x19, 0x1A, 0x36. */
s32 BtlAiSeq_IsInterrupted(BtlAiWork *ai, s32 id);

/* mode 0: the fighter is closer to the stage ceiling than its height + 10; mode 1: it is less than 10 above the
 * ground (on stages 4 and 27 also when pose bit 0x80 is clear). */
s32 BtlAiSeq_CheckHeight(BtlAiWork *ai, s32 mode);

/* End test of the run phase that depends on the action id; non-zero ends the action.
 * 9, 11, 21: on stages 4 / 27, when the fighter's pose bit 0x80 is clear or its y is above -80 (+Y is down).
 * 13: on stages 4 / 27, when the opponent's pose bit 0x80 is clear.
 * 15: BtlAiSeq_CheckHeight with the chosen step as the mode (step 0 = going up, step 1 = going down).
 * 16 / 17: BtlAiSeq_CheckHeight(0) / (1): the ceiling / the ground is reached.
 * 29: on stages 4 / 27, when the fighter's pose bit 0x80 is clear; otherwise, when it is the only action, the
 *     fighter is in state class 12 and the pad's special-3 timer has run out, the "special 3 done" mark is
 *     cleared so that the step's special 3 is sent again. */
s32 BtlAiSeq_CheckStageAbort(BtlAiWork *ai, s32 id);

/* ---- The four phases (gBtlAiStateFuncs) ---- */

/* Phase 0. Ends the action at once when BtlAiSeq_IsInterrupted says so. An action with flag 2 waits here for the
 * fighter to be in state class 0, sending nothing, except in state class 10 where it presses DASH (alternate
 * frames) to stop the dash. Otherwise falls through to the start phase. */
void BtlAiSeq_PhaseInit(BtlAiWork *ai);

/* Phase 1: chooses the step of the current group. Clears the pad marks, the step parameter and the flags 0x40,
 * 0x200, 0x400, 0x800 and 0x1000, records the fighter's state, attack charge and the fighter distance, counts the
 * steps of the group and lets the action's pick function choose one; no step or a negative pick ends the action.
 * Action 10 stores the fighter distance in status.unk24 when its step 0 was chosen, every other action clears it.
 * Falls through to the run phase. */
void BtlAiSeq_PhaseStart(BtlAiWork *ai);

/* Phase 2, every frame, in this order:
 * 1. raise BTLAI_SEQ_TOOK_EFFECT once the fighter is in the step's state class in another state than at the start;
 * 2. the step handler: finished = back to phase 1 with the next group, nothing is sent this frame;
 * 3. BtlAiSeq_IsInterrupted: end;
 * 4. while the input has not taken effect, count frames (not while any fighter has flag 0x128) and end the action
 *    after timeout * 30 of them;
 * 5. BtlAiSeq_CheckStageAbort: end;
 * 6. send the step's hold / press / once bits and its special (nothing at all with BTLAI_SEQ_RELEASE). */
void BtlAiSeq_PhaseRun(BtlAiWork *ai);

/* After the last action of a plan: decides whether action 0x43 follows it. Needs the powered-up mode (fighter
 * flag 6), the plan's first action to be one of 0x22, 0x24, 0x26, 0x29, 0x2A, 0x2B, 0x32, 0x35 (or 0x2D / 0x2E
 * with BtlCharApi_GetUnkD74Diff == 0), and a successful AiThink_RollActRate(ai, 0x4C), which draws. The same ten
 * ids are the ones step handler 23 maps to a slot number. */
s32 BtlAiSeq_RollPowerUpChain(BtlAiWork *ai);

/* Phase 3: pops the action. In state class 10 (except for action 14) it first presses DASH until the dash has
 * stopped. When the stack is empty it either chains action 0x43 (keeping the old id in seq->prevId) or clears
 * BTLAI_SEQ_CHAIN; the next action starts at phase 0 on the next frame. */
void BtlAiSeq_PhaseEnd(BtlAiWork *ai);

/* ---- Pick functions (gBtlAiPickFuncs) ---- */

/* Pick 0: any alternative, evenly. One draw: Rand_Range(n). */
s32 func_002ED180(BtlAiWork *ai, s32 n, s32 arg) {
    return Rand_Range(n);
}

/* Pick 1: the alternative the rule names. */
s32 BtlAiPick_ByArg(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 2: arg = seconds * 10 + alternative; the step parameter is seconds * 30 frames. Alternative 9 draws
 * Rand_Range(n). An alternative the group does not have ends the action. */
s32 BtlAiPick_ArgSeconds(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 3: arg = parameter * 10 + alternative. A negative arg draws the parameter: Rand_Range(|arg| / 10) + 1.
 * Then Rand_Range(100) is always drawn. A group that does not have exactly five alternatives plays alternative 0.
 * With five: alternative 8 replaces the parameter by -1 (30%), 10 (30%) or Rand_Range(10) (40%), and the
 * alternatives 5, 8 and 9 mean "any": Rand_Range(5). So one to four draws. */
s32 BtlAiPick_ArgFrames(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 4: how far to charge ki, as the step parameter in percent: arg 0 = 100, 1 = 101 (until powered up), 2 /
 * 3 = the dearer / cheaper of the fighter's first two skill costs (work + 0x14 / + 0x10, set by AiThink_ReadKit).
 * Always alternative 0. No draw. */
s32 BtlAiPick_KiTarget(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 5: the planned skill slot (plan.unk8) is the alternative; none (-1) or slot 2 ends the action. The step
 * parameter is 100 (30%), 0 (30%) or Rand_Range(100) (40%). Rand_Range(100) is drawn before the slot is tested,
 * so one or two draws. */
s32 BtlAiPick_SkillCharge(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 6: a reaction delay in frames as the step parameter. arg 1: b + b * r with b = half of { 45, 33.75, 22.5,
 * 11.25, 0 }[level / 6] and r = Rand_Range(100) / 100, i.e. 22..44 frames at the lowest levels and 0 at the
 * highest; arg 2: 10 + (29 - level) * 20 / 29 (30 frames at level 0, 10 at level 29; 0 for the dummy). The draw
 * is made for every arg. Always alternative 0. */
s32 BtlAiPick_LevelDelay(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 7: one Rand_Range(100) against three level-scaled weights of the AI type's profile (bytes 0x15C + 0x10 +
 * step * 3 .. at level 0, 0x41C + .. at level 29), where step is AiThink_GetBlastStep (0, 1 in state class 15, or
 * the place in the rush chain for states 0x3C..0x3F). A group with one alternative clears BTLAI_SEQ_COMBO_SECOND
 * and plays it (the draw is still made). Alternative 1 at step 0 sets that flag; at step 1 with the flag set the result
 * is always alternative 0; alternative 2 becomes 0 when situation bit 61 is set (the opponent's parameter byte
 * +2 is 4). When the roll is above all three weights: alternative 0. */
s32 BtlAiPick_ComboBranch(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 8: the fusion slot BtlCharApi_PickFusionSlot proposes (it draws Rand_Range; none = alternative 0). */
s32 BtlAiPick_FusionSlot(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 9: the transformation slot BtlCharApi_PickTransformSlot proposes (it draws; none = alternative 0). */
s32 BtlAiPick_TransformSlot(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 10: which team member to switch to (the step parameter). Members other than the active one with health
 * left are scored health% * 0.7 + ki% * 0.3 and sorted best first; Rand_Range(100) then takes the best with 60%
 * of two, 50 / 35 / 15% of three, 40 / 30 / 30% of four (the fourth is never taken); with any other number of
 * candidates (none, or more than four) the parameter is 0. A single candidate is taken as it is with alternative
 * 0; otherwise the alternative is a second draw, Rand_Range(n). */
s32 BtlAiPick_SwitchMember(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 11: the alternative by the (negative) level of a training dummy: -2 gives 0, -3 gives 1, and so on. */
s32 BtlAiPick_DummyMode(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 12: the button the fighter's open prompt asks for (BtlCharApi_GetPromptButtons): UP, DOWN, LEFT, RIGHT,
 * BLAST = alternatives 0..4; no prompt ends the action. No draw: the CPU always answers correctly. */
s32 BtlAiPick_PromptButton(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 13: the step parameter of step handler 8 by the rule's argument (1 -> 0, 2 -> 15, 3 -> -1); any other
 * argument ends the action. Always alternative 0. */
s32 BtlAiPick_GuardMode(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 14: a direction. arg = seconds * 10 + alternative as in pick 2. A group of one plays it (without setting
 * the time). A group of 4 or 8 ignores the alternative in arg and draws: each alternative weighs 10, Rand_Range
 * (n * 10). But when the fighter is further from the stage centre than half the stage radius (or on stages 4 /
 * 27), n probes of length 15 are made from the fighter, starting along its facing and turning 45 degrees each
 * time (also with four alternatives), and the alternative whose probe ends furthest from the centre weighs 3
 * instead of 10, with eight alternatives also its two neighbours: Rand_Range(33) or Rand_Range(59). Other group
 * sizes take the alternative from arg. */
s32 BtlAiPick_Direction(BtlAiWork *ai, s32 n, s32 arg);

/* Pick 15: the rule's argument is the step parameter. Always alternative 0. */
s32 BtlAiPick_SetTimer(BtlAiWork *ai, s32 n, s32 arg);

/* ---- Step handlers 0..13 (gBtlAiStepFuncs). Non-zero = step finished. ---- */

/* Step handler 0, the default: finished when the fighter is in the state class of the chosen step, in a state
 * other than the one it started in (or in class 0) whose flag bit 1 is clear. Finished at once when the action's
 * first step has no class (-1); action 0x2E is finished as soon as the input took effect. */
s32 BtlAiStep_ReachClass(BtlAiWork *ai);

/* Step handler 1 (ki charge): finished when ki has reached the step parameter in percent of 100000 (101: when
 * the powered-up mode is on), or as soon as BtlAiSense_IsBehindOpponent is true for the opponent's side, i.e. this
 * fighter is turned away from the opponent. */
s32 BtlAiStep_ChargeKi(BtlAiWork *ai);

/* Step handler 2 (approach): finished in state class 0, when the opponent blocks the way
 * (BtlCharApi_IsBlockedByOpponent) or when bit 29 of the fighter word +0x1288 is set. Refreshes seq->startDist. */
s32 BtlAiStep_UntilBlocked(BtlAiWork *ai);

/* Step handler 3: finished after the step parameter's number of frames (not counted while any fighter has flag
 * 0x128). */
s32 BtlAiStep_Countdown(BtlAiWork *ai);

/* Step handler 4: handler 2 or handler 7. */
s32 BtlAiStep_BlockedOrCharged(BtlAiWork *ai);

/* Step handler 5: handler 2 and handler 7. */
s32 BtlAiStep_BlockedAndCharged(BtlAiWork *ai);

/* Step handler 6: finished when the fighter's state class is not 1..7. */
s32 BtlAiStep_NotHit(BtlAiWork *ai);

/* Step handler 7 (held attack): finished when BtlCharApi_GetChargeRate * 10 has reached the step parameter; with
 * -1, one frame after the charge is full (1.0). Also finished when the charge went down, or is 0 after the input
 * took effect. */
s32 BtlAiStep_Charged(BtlAiWork *ai);

/* Step handler 8: the guard step. What ends it depends on the step parameter (pick 13): -1 = the opponent's
 * technique is not of kind 1 or 2; 15 (any other value) = no foreign blast is flying past; 0 = the opponent has
 * stopped attacking (BtlCharApi_CheckUnkCAC) and its state has flag bit 1 clear. For action 0x45 it also picks
 * the step to play from the opponent's state class (0x10 -> 1, 0x11 -> 2, else 0) on every frame. */
/* FAKE MATCH (permuter): two constants held in variables. `hitCls = 0x10` is set at the top (in front of the
 * flag), and `none = 0` is set behind the id block and compared with the timer. Without them 2 of 74 instructions
 * differ: `sltiu v0,v0,1` (the "kind is not 1 or 2" result) and `li a1,0x10` in front of / in the delay slot of
 * the `bne id,0x45` branch come out exchanged. What happens (RTL dumps): written as a literal, the 0x10 is created
 * in the next block and the first scheduling pass moves it up with priority 2 while the flag has priority 1; as a
 * variable it is an instruction of the first block (that alone gives 5 differences, the same instructions in
 * another order). `none = 0` is one more instruction in the timer block that the timer branch depends on until
 * reload replaces the pseudo by the constant; it changes the order in which the instructions of that block are
 * moved up (`li a2,-1`). Only the compare `timer != none` needs it; `none` at its declaration, in front of the
 * id block, or used only in the later returns does not work, nor does `hitCls` set behind the flag.
 * What the two stand for is unknown (a dependent of the flag in the first block that is gone afterwards would do
 * the same). Natural forms that were tried and do not match: `ret = !(...)`, an if / else pair, a switch (on the
 * kind and on the timer), a ternary, the test inside the `timer == -1` branch, an inline helper returning the
 * flag or picking the step or deciding the result, a result variable with one `return`, `kind - 1` and the range
 * flag as locals, the class chain nested the other way, 0x11 in a variable as well.
 * Behaviour is identical in all of them. */
s32 BtlAiStep_GuardUntilSafe(BtlAiWork *ai);

/* Step handler 9: finished 30 frames after the opponent stopped attacking (BtlCharApi_CheckUnkCAC; the count
 * restarts while it attacks, and stands still while any fighter has flag 0x128); never while the opponent's
 * state has flag bit 1. With no attack at all it ends when the step parameter has been counted below 0. */
s32 BtlAiStep_GuardCountdown(BtlAiWork *ai);

/* Step handler 10: handler 0, and no ki blast shots left to fire. */
s32 BtlAiStep_ReachClassNoShots(BtlAiWork *ai);

/* Step handler 11: finished on the second frame (the buttons are sent once). */
s32 BtlAiStep_OneFrame(BtlAiWork *ai);

/* Step handler 12: finished when the fighter faces the opponent (facing . direction to the opponent > 0, on
 * the ground plane). While the facing did not change since the last frame the pad marks are cleared, so "once"
 * buttons are sent again. */
s32 BtlAiStep_FacingOpponent(BtlAiWork *ai);

/* Step handler 13: finished when the fighter's switch target is the member pick 10 chose. */
s32 BtlAiStep_SwitchQueued(BtlAiWork *ai);

/* ------------------------------------------------------------------------------------------------------------
 * Second part, 0x1B6008..0x1B6D50 (the file as it was before the first part was decompiled): step handlers
 * 14..23, the per-frame sequence runner and the input hand-over. Same header, no cast macros needed.
 *
 * Per frame (BtlAiMgr_Update, 0x1BB620, for each CPU-controlled fighter): sense (0x1BFF70), think (0x1BAC30: the
 * rule lists of the AI data, tested with the BtlAiCond_* functions), BtlAi_RunSeq, BtlAi_SendInput.
 *
 * The object's .rodata starts at 0x2ED8C0 with the jump table of BtlAiSeq_CheckStageAbort (0x1B4300); the object
 * itself starts at 0x1B3F78 (eft_det_b_c.c, whose table D_002ED8A0 is in front of it). Where the object ends: see
 * the note at the top of btl_ai_cond.c.
 * ------------------------------------------------------------------------------------------------------------ */

/* ---- Step handlers 14..23 of the table at 0x2C4708 (first object). Non-zero = step finished. ---- */

/* Step handler 14: compares a fighter value of both sides (kind 1 or 2 in seq->timer), picks one of two AI-type
 * rates for it and, on a successful roll, moves seq->step on (modulo 4). */
s32 BtlAiStep_Unk14(BtlAiWork *ai);

/* Step handler 15: runs BtlAiStep_ReachClass; once that is done, checks the queued move and arms the 300-frame cooldown. */
s32 BtlAiStep_Unk15(BtlAiWork *ai);

/* Step handler 16: waits up to 60 frames for the opponent to come within twice move.dist[1]. */
s32 BtlAiStep_WaitNear2(BtlAiWork *ai);

/* Step handler 17: waits for a skill (plan.unk8) to become affordable or usable against the opponent's action. */
/* Matching notes:
 * - the shared `return 0` sits directly behind the stage 4 / 27 block and the class tail is the END of the
 *   function: a `goto` over the `return 0` (early returns put `move v0,zero` into the flag update);
 * - `if (flags & 0x40) { ... }` falls into the shared `return 0`;
 * - `if (TestPoseBit80() == 0) { seq->step = 2; return 0; }` (v0 is still the call's 0);
 * - the unsigned copy of cls[1] is a local read in front of the `cls[1] == kind` test;
 * - the tail is nested under `if (kind == 2)` and `if (cls[1] != 0x1C)`, both falling out to the final
 *   `return 1`. With `if (kind != 2) return 1;` the code differs only in one delay slot (`ld s1` instead of
 *   `nop` at 0x1B6528): the return value is then loaded in front of that branch, the last jump pass deletes the
 *   same load in front of the `cls[0]` branch as redundant, and the delay-slot pass gives that branch the first
 *   epilogue load at once. In the original that branch first holds `li v0,1`, loses it as redundant in the
 *   first relax pass and gets `ld s0` only in the second round, after the range-test branch took its own copy
 *   of `ld s0`, which the last relax pass deletes: an empty slot that is never refilled.
 * Differential test against the original bytes: build/scratch_cleanup3_S/t_unk17.py. */
s32 BtlAiStep_FireSkill(BtlAiWork *ai);

/* Step handler 18: counts seq->timer down, reloading it by level and distance, then runs BtlAiStep_NotHit. */
s32 BtlAiStep_Unk18(BtlAiWork *ai);

/* Step handler 19: same countdown, done when BtlCharApi_GetStunTimer is not positive. */
s32 BtlAiStep_Unk19(BtlAiWork *ai);

/* Step handler 20: done when BtlCharApi_IsOppSkillFlag4 is zero. */
s32 BtlAiStep_Unk20(BtlAiWork *ai);

/* Step handler 21: same countdown, done when BtlCharApi_TestFlagBE is zero. */
s32 BtlAiStep_Unk21(BtlAiWork *ai);

/* Step handler 22: like 16 with three times the range, then BtlAiStep_ReachClass. */
s32 BtlAiStep_WaitNear3(BtlAiWork *ai);

/* Step handler 23: after BtlAiStep_ReachClass, on stage 4 or 27, picks the next step from a skill slot lookup. */
s32 BtlAiStep_Unk23(BtlAiWork *ai);

/* ---- Top level. The object boundary is somewhere between here and BtlAi_ScaleByLevel. ---- */

/* Runs sequence 3: a one-shot chosen by the entry's kind byte. */
void BtlAi_RunInstant(BtlAiWork *ai);

/* Once per frame: clears the output, runs the sequence on top of the stack, then finishes the output. */
void BtlAi_RunSeq(BtlAiWork *ai);

/* Hands this frame's buttons and stick to the fighter (the same path a pad feeds). */
void BtlAi_SendInput(BtlAiWork *ai);

/* Interpolates between lo (level 0) and hi (level 29). Last function of this object: its callers in the next one
 * (btl_ai_cond.c) only compile to the original bytes when it is NOT defined in their translation unit. */
s32 BtlAi_ScaleByLevel(s32 level, s32 lo, s32 hi);
