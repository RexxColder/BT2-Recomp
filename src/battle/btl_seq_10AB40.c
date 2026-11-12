#include "common.h"
#include "battle/btl_seq.h"
#include "battle/battle_setup.h"
#include "battle/battle_work.h"
#include "sys/heap.h"
#include "sys/adx.h"

/* ---- Skill-list text of the pause menu, 0x215420-0x216AC0 ----
 * The list is a UTF-16 script. Every line starts with two characters whose second one is a hex digit (a mask
 * tested against work->unk10), optionally followed by "&ddd" (unlock condition), then a tag:
 *   '$n'   page n title          '*abc' entry (three digits a, b, c)      '%0' / '%1' detail lines
 *   '#'    note                  '@'    end of the script
 * Lines are separated by BtlText_NextLine(). BtlTextList / BtlTextWork are in battle/btl_seq.h.
 *
 * What the matching code says about the original source file (see also the note above BtlSeq_FirstState):
 * - BtlText_DrawPart (0x215420) was defined in the same file as, and above, BtlText_DrawList: two branches of
 *   DrawList are annulled / not annulled the right way only when the compiler has already compiled DrawPart.
 *   That is why this file starts at 0x215420 and not at 0x215540. The file may well have started earlier still.
 * - BtlText_IsLineDimmed was `static`: DrawList keeps the text pointer in a register across the call, which the
 *   compiler only does for a function it has marked `const` itself, and it only does that for static ones. */

extern f32 gBtlTextAlpha;
extern u64 *gSaveData; /* local view: only charaBits (+0xC10) is used here */

extern BtlTextWork *BtlMenu_GetWork(void);
extern u16 *BtlMenu_GetScript(void);
extern u16 *BtlMenu_GetScript2(void);
extern u16 *BtlText_NextLine(u16 *line);        /* start of the next line */
extern void BtlText_PutScissor(void *pkt, s32 x0, s32 y0, s32 x1, s32 y1); /* GS scissor */
extern void BtlText_PutSprite(void *pkt, s32 x0, s32 y0, s32 x1, s32 y1, s32 u, s32 v, s32 w, s32 h, u32 color, s32 part);
extern s32 BtlCtrl_TestMemberUnk70(s32 side);
extern s32 Font_GetCmdCount(void);
extern void Font_Flush(s32 font);
extern s32 Font_GetGlyphHeight(void);
extern f32 Font_FitScale(u16 *str, s32 width);
extern void Font_PrintAt(s32 x, s32 y, u16 *str);
extern void Font_PushStyle(void);
extern void Font_PopStyle(void);
extern void Font_SetScale(f32 a);
extern void Font_SetScaleXY(f32 sx, f32 sy);
extern void Font_GetScaleXY(f32 *sx, f32 *sy);
extern void Font_SetClip(s32 x0, s32 y0, s32 x1, s32 y1);
extern void Font_SetAlign(s32 align);
extern void Font_SetFlags(s32 a);
extern void Font_SetShadowMode(s32 a);
extern void Font_SetColorRGBA(s32 r, s32 g, s32 b, s32 a);
extern void Font_SetColor2RGBA(s32 r, s32 g, s32 b, s32 a);
extern void Font_SetShadowColorRGBA(s32 r, s32 g, s32 b, s32 a);
extern s32 FontIcon_GetPadTagSize(u16 *str);
extern s32 Battle_IsSplitScreen(void);


/* Draws one part of the list sprite sheet: a w x h rectangle at (x, y); a negative h flips it vertically. */
void BtlText_DrawPart(void *pkt, s32 x, s32 y, s32 w, s32 h, s32 part);

/* Draws the icon of a page title: digit '0'..'8' picks part 7..14 ('7' and '8' share the last one). */
void BtlText_DrawPageIcon(void *pkt, s32 x, s32 y, u16 digit);
static s32 BtlText_IsLineDimmed(s32 page, s32 entry, s32 side);

/* Reads the mask digit of a line, steps over the two leading characters and tells if the line is shown. */
s32 BtlText_CheckLineMask(u16 **cursor, s32 side);

/* Steps over an "&ddd" unlock prefix; 0 when the line is locked (character ddd not unlocked in the save). */
s32 BtlText_CheckUnlock(u16 **cursor);

/* Stub: never dims a line. It has to be static: only then does the compiler see that it is a `const` function,
 * which BtlText_DrawList needs (p stays in a register across the call). */
static s32 BtlText_IsLineDimmed(s32 page, s32 entry, s32 side);

/* A colour component scaled by the line alpha. */
#define BTLTEXT_COL(v) ((u8)(u32)(gBtlTextAlpha * (v)))

/* Draws the list inside the clip rectangle (x0, y0)-(x1, y1). mode 0: the page title and the entries of the
 * current page, scrolled, with the selected one highlighted; other modes: the detail lines ('%') and the note
 * ('#') of the selected entry.
 * Matching notes: the locals are declared in the order of their stack slots (most of them are spilled); the
 * three entry digits are an array; `line` is a register copy of p taken once per line. */
void BtlText_DrawList(void *pkt, s32 x0, s32 x1, s32 y0, s32 y1, s32 mode);

/* Draws the scroll bar of the current page: the frame, then the thumb (always drawn; with more than 7 entries it
 * is shortened and moved, otherwise it fills the frame).
 * Matched in cleanup 4. Two things were needed. (1) A BEHAVIOURAL FIX: the earlier attempt drew the thumb's upper
 * part only inside `if (over)`; the original's `beqz` skips only the two coordinate updates (the wrong branch
 * target was hidden among 29 "register swap" lines). (2) `len` is computed in front of the `if`, and the height
 * behind it goes through `h = y0; h = y1 - h;`: written `h = y1 - y0;` gcse sees the same expression as `len`,
 * calls it partially redundant and adds a copy (`subu v0 / move t0,v0`). The two-step form came from the
 * permuter and may be a stand-in for what the source really had (`half = y0; half = (y1 - half) / 2;` works
 * too): what matters is that the subtraction's operand is a variable set twice. */
void BtlText_DrawScrollBar(void *pkt, s32 unused, s32 x, s32 y0, s32 y1);

/* Counts the pages and the entries of each page of the current side's list. */
void BtlText_CountEntries(void);

/* Returns the name of the n-th entry of the second script (8 characters into its line), NULL when it has none.
 * The bare `return;` is what the original does when there is no script: v0 is left as the NULL just returned. */
u16 *BtlText_FindEntry(s32 n);

/* Draws the name of entry n at (x, y); align 0 / 1 / other picks the font alignment 0 / 2 / 1. */
void BtlText_DrawEntryName(s32 x, s32 y, s32 n, s32 align, f32 alpha);

/* Battle sequence state machine, 0x216AC0-0x2187E0. See battle/btl_seq.h for the state list.
 *
 * Object boundaries, from .rodata: the tick table of BtlClock_Tick (0x2F1AD8) follows jtbl_002F1A80 of
 * BtlText_CheckLineMask with no padding, and the jump tables after it sit at +0x18 from it, so the text
 * functions and at least BtlClock_Tick were one object. With the file starting at BtlText_DrawPart (0x215420,
 * .rodata from jtbl_002F1A50) every table lands on its original address.
 *
 * Object boundaries, from code generation: a call to a function the compiler has already compiled in the same
 * file is treated differently by the delay-slot pass than a call to an unknown one (it looks through the call
 * when deciding whether a branch must be annulled). Two places depend on it:
 * - BtlText_DrawList needs BtlText_DrawPart known (same file, above it): matches as written.
 * - BtlSeq_CheckBattleEnd needs BtlSeq_TickClocks NOT known. So the state handlers and the win check
 *   (BtlSeqIntroTalk_Setup .. the end; their first jump table, 0x2F1AF0, is 16-byte aligned, which is where a
 *   new object's .rodata would start) were most likely a second source file, and this file should be split
 *   somewhere after BtlSeq_TickClocks (0x217090) and before BtlSeq_CheckBattleEnd (0x217EF0). Until then
 *   BtlSeq_CheckBattleEnd calls it through a second declaration of the same symbol. */

extern void *memset(void *dst, s32 c, u32 n);
extern s32 rand(void);

/* Local views of things owned by other modules (their headers are still moving). */
typedef struct BtlSeqObj {
    /* 0x000 */ u8 unk0[0xC];
    /* 0x00C */ s32 chara;  /* character id */
    /* 0x010 */ u8 unk10[0x93C - 0x10];
    /* 0x93C */ u8 *talkTbl; /* 4 bytes per opponent character id: {intro line or 0xFF, speaks second, win line or 0xFF, ?} */
} BtlSeqObj;

extern void BtlFacade_SetCtrl10D(s32 side);
extern BtlSeqObj *BtlObj_Get(s32 idx);
extern void BtlObj_SetSubState(BtlSeqObj *obj, s32 a, s32 line); /* mouth / talk animation */
extern void BtlCtrl_StartEntrance(s32 side);        /* character flag 0xEF: entrance pose */
extern void BtlCtrl_EndEntrance(s32 side);        /* character flag 0xF0: end of entrance */
extern void BtlCtrl_StartWinPose(s32 side);        /* character flag 0xF1: win pose */
extern void BtlCtrl_StartLosePose(s32 side);        /* character flag 0xF2: lose pose */
extern s32 BtlCtrl_IsPoseReached(s32 side);         /* pose reached */
extern void DemoCam_PlayObjAnim(s32 side, s32 cut); /* fighter camera cut */
extern void DemoCam_SetScaleHeight(s32 a);
extern s32 DemoCam_PlayStageAnim(s32 cut);          /* stage camera cut */
extern s32 DemoCam_IsActive(void);             /* camera cut still playing */
extern s32 DemoCam_IsInUse(void);
extern void DemoCam_Stop(void);            /* stop the camera cut */
extern void ScrXfade_RequestCapture(void);
extern void ScrXfade_Start(s32 a, f32 seconds);
extern s32 BtlScript_IsEventRunning(void);
extern void BtlScript_AbortEvents(void);
extern u8 *BtlScript_GetCurrentEvent(void);
extern void HudNotice_Show(s32 id);          /* HUD announcement */
extern s32 BtlCharApi_AnyHasFlag128(void);             /* any character has flag 0x128 */
extern s32 BtlCharApi_HasMemberUnk70(s32 side);
extern s32 BtlCtrl_TestFlag7(s32 side);         /* character flag 7 */
extern s32 BtlCtrl_IsTeamDead(s32 side);         /* every character of the side has no health */
extern s32 BtlPause_GetPadCount(void);
extern void BtlPause_SetPad(s32 pad);
extern s32 BtlPause_GetMenuPad(void);
extern s32 BtlPause_GetPad(void);
extern s32 PauseMenu_Update(s32 a, s32 b);     /* pause / result menu update */
extern void PauseMenu_Draw(void);
extern void Snd_SetPause(s32 a, s32 b);
extern void Hud_ShowAll(s32 on);          /* HUD visibility bits */
extern void Hud_ShowGauges(s32 on);
extern void Hud_ShowTimer(s32 on);
extern void Hud_ShowNotice(s32 on);
extern void Hud_ShowCombo(s32 on);
extern void Hud_ShowPrompt(s32 on);
extern void Fade_Start(s32 idx, s32 dir, f32 seconds);


s32 BtlSeqIntroTalk_Setup(BtlSeqTalkCtx *ctx);
s32 BtlSeqWinTalk_Setup(BtlSeqTalkCtx *ctx);
s32 BtlSeq_CanDraw(void);
void BtlSeq_JudgeByHealth(BattleResult *result);
void BtlSeq_SetResultPad(void);
s32 BtlSeq_IsModeZero(void);

/* Returns the first state of a table that has an enter handler (0 when none has). */
s32 BtlSeq_FirstState(BtlSeqState *table);

/* Calls one handler of a state with the state's poll callback loaded into the context; -1 for an empty slot. */
s32 BtlSeq_Call(BtlSeqFunc func, s32 state);

/* Clears the sequence, picks the state table for the battle mode and enters its first state. */
s32 BtlSeq_Reset(void);

/* Allocates the sequence and starts it. */
s32 BtlSeq_Init(void);

/* Frees the sequence. */
void BtlSeq_Term(void);

/* Runs the current state's preUpdate handler (before the battle simulation). */
s32 BtlSeq_PreUpdate(void);

/* Runs the current state's update handler and performs the state change it asks for; 1 = leave the battle. */
s32 BtlSeq_Update(void);

/* Returns the battle clock. */
BtlClock *BtlSeq_GetClock(void);

/* Returns the second clock. */
BtlClock *BtlSeq_GetSubClock(void);

/* Returns the current state. */
s32 BtlSeq_GetState(void);

/* True while the fight itself is running (state 3). */
s32 BtlSeq_IsFighting(void);

/* True during the finish announcement (state 4). */
s32 BtlSeq_IsFinish(void);

/* Runs the current state's extra handler (mode 1: skip the talk). */
s32 BtlSeq_CallExtra(void);

/* Turns the battle-end check (and the clocks) off or on. */
void BtlSeq_SetEndCheckOff(s32 off);

/* Returns whether the battle-end check is off. */
s32 BtlSeq_GetEndCheckOff(void);

/* Zeroes a clock. */
void BtlClock_Clear(BtlClock *clock);

/* Advances a clock by one tick (34, 32, 34 ms in turn), stopping at 9:59:59.999. */
s32 BtlClock_Tick(BtlClock *clock);

/* Clears both clocks and loads the time limit into the battle clock. */
void BtlSeq_ResetClocks(void);

/* Ticks both clocks and updates the time left; 1 when the time limit is reached. */
s32 BtlSeq_TickClocks(void);

/* Restarts the second clock. */
void BtlSeq_ResetSubClock(void);

/* Seconds left of the time limit, -1 when there is none. */
s32 BtlSeq_GetTimeLeft(void);

/* Stops both fighters' talk animation and both voice players. */
void BtlSeq_StopTalk(void);

/* Chooses the two entrance lines: the pair's special dialogue when both have a table entry, else random. */
s32 BtlSeqIntroTalk_Setup(BtlSeqTalkCtx *ctx);

/* State 1 enter: prepares the entrance lines; mode 1 has none and waits for the skip request. */
s32 BtlSeqIntroTalk_Enter(BtlSeqTalkCtx *ctx);

/* State 1 preUpdate: at steps 0 and 2 starts a speaker's pose, camera cut, voice line and talk animation. */
s32 BtlSeqIntroTalk_PreUpdate(BtlSeqTalkCtx *ctx);

/* State 1 update: waits for each line to end (voice stopped or 10 s), or for the skip; then goes to state 2. */
s32 BtlSeqIntroTalk_Update(BtlSeqTalkCtx *ctx);

/* State 1 exit: stops the camera cut and ends both entrance poses (not in mode 1). */
s32 BtlSeqIntroTalk_Exit(BtlSeqTalkCtx *ctx);

/* State 1 extra (mode 1): asks the state to end. */
s32 BtlSeqIntroTalk_Skip(BtlSeqTalkCtx *ctx);

/* Chooses the speaker, line and announcement of the winner scene. */
s32 BtlSeqWinTalk_Setup(BtlSeqTalkCtx *ctx);

/* State 5 enter: prepares the winner scene and hides HUD parts; mode 1 can be told to wait for the skip instead. */
s32 BtlSeqWinTalk_Enter(BtlSeqTalkCtx *ctx);

/* State 5 preUpdate: step 0 starts the pose, camera cut and voice line; step 2 starts a 1.5 s hold. */
s32 BtlSeqWinTalk_PreUpdate(BtlSeqTalkCtx *ctx);

/* State 5 update: waits for the line (or 10 s), holds 1.5 s, then goes to state 6; the poll callback skips. */
s32 BtlSeqWinTalk_Update(BtlSeqTalkCtx *ctx);

/* State 5 exit: stops the talk (not in mode 1). */
s32 BtlSeqWinTalk_Exit(BtlSeqTalkCtx *ctx);

/* State 5 extra (mode 1): asks the state to end. */
s32 BtlSeqWinTalk_Skip(BtlSeqTalkCtx *ctx);

/* State 0 enter: restarts the step counter and holds the fighters. */
s32 BtlSeqStageIntro_Enter(BtlSeqWaitCtx *ctx);

/* State 0 preUpdate: at steps 0, 2 and 4 starts stage camera cut 0, 1 and 2. */
s32 BtlSeqStageIntro_PreUpdate(BtlSeqWaitCtx *ctx);

/* State 0 update: steps on when a camera cut ends; goes to state 1 after the third or on the poll callback. */
s32 BtlSeqStageIntro_Update(BtlSeqWaitCtx *ctx);

/* State 0 exit: stops a camera cut that is still playing. */
s32 BtlSeqStageIntro_Exit(BtlSeqWaitCtx *ctx);

/* True when the battle ended by time up in mode 0: the only case where equal health is a draw. */
s32 BtlSeq_CanDraw(void);

/* Picks the winner from the two sides' health; equal health falls back to a rule flag, a draw, or rand(). */
void BtlSeq_JudgeByHealth(BattleResult *result);

/* Ticks the clocks and decides whether the battle is over, filling the result block; 1 when it is.
 *
 * Two things were needed to match:
 * - The function has to END with the last success path (`return 1` falling off the end) and every `return 0`
 *   has to be an early return. Then the compiler shares only the final `return 1` between the blocks and keeps
 *   the three "set reason + BtlSeq_JudgeByHealth" blocks separate; with `return 0` as the last statement it
 *   merges those three blocks into one.
 * - The call to BtlSeq_TickClocks() must look like a call to a function the compiler has not seen the body of
 *   (the branch before it is `bnezl` only then). In the original this function was therefore compiled without
 *   BtlSeq_TickClocks() defined above it, i.e. the clock code was most likely a separate source file. Until the
 *   file is split, the call goes through a second declaration of the same symbol. */
extern s32 BtlSeq_TickClocksExt(void) __asm__("BtlSeq_TickClocks");

s32 BtlSeq_CheckBattleEnd(void);

/* State 3 enter: releases the fighters (clears the demo and ready flags); mode 8 shows the HUD. */
s32 BtlSeqFight_Enter(BtlSeqWaitCtx *ctx);

/* State 3 preUpdate: nothing. */
s32 BtlSeqFight_PreUpdate(BtlSeqWaitCtx *ctx);

/* State 3 update: opens / runs the pause menu, then checks for the end of the battle (-> 4, or 6 without a finish scene). */
s32 BtlSeqFight_Update(BtlSeqWaitCtx *ctx);

/* State 3 exit: nothing. */
s32 BtlSeqFight_Exit(BtlSeqWaitCtx *ctx);

/* State 2 enter: holds the fighters, starts the 0.8 s wait and shows the HUD. */
s32 BtlSeqReady_Enter(BtlSeqWaitCtx *ctx);

/* State 2 preUpdate: nothing. */
s32 BtlSeqReady_PreUpdate(BtlSeqWaitCtx *ctx);

/* State 2 update: after 0.8 s shows announcement 0 and releases the fighters; 2 s later goes to state 3. */
s32 BtlSeqReady_Update(BtlSeqWaitCtx *ctx);

/* State 2 exit: announcement 1. */
s32 BtlSeqReady_Exit(BtlSeqWaitCtx *ctx);

/* Gives the result menu to pad 0 when one pad plays, else to the winning side. */
void BtlSeq_SetResultPad(void);

/* True in battle mode 0. */
s32 BtlSeq_IsModeZero(void);

/* State 6 enter: mode 0 with a finished battle opens the result menu (step 0); otherwise starts the 1.2 s fade out (step 1). */
s32 BtlSeqEnd_Enter(BtlSeqWaitCtx *ctx);

/* State 6 preUpdate: nothing. */
s32 BtlSeqEnd_PreUpdate(BtlSeqWaitCtx *ctx);

/* State 6 update: step 0 runs the result menu until it aborts the battle, step 1 waits for the fade and returns 99. */
s32 BtlSeqEnd_Update(BtlSeqWaitCtx *ctx);

/* State 6 exit: stops the camera cut. */
s32 BtlSeqEnd_Exit(BtlSeqWaitCtx *ctx) {
    if (DemoCam_IsInUse()) {
        DemoCam_Stop();
    }
    DemoCam_SetScaleHeight(0);
    return 1;
}

/* State 4 enter: holds the fighters, starts the 3.5 s wait and shows the announcement for the finish reason. */
s32 BtlSeqFinish_Enter(BtlSeqWaitCtx *ctx);

/* State 4 preUpdate: nothing. */
s32 BtlSeqFinish_PreUpdate(BtlSeqWaitCtx *ctx);

/* State 4 update: when the wait ends goes to the winner scene (5) if a side won and the mode is not 8, else to 6. */
s32 BtlSeqFinish_Update(BtlSeqWaitCtx *ctx);

/* State 4 exit: nothing. */
s32 BtlSeqFinish_Exit(BtlSeqWaitCtx *ctx);
