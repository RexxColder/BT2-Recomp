#include "common.h"
#include "battle/btl_script.h"
#include "battle/btl_seq.h"
#include "sys/gsc.h"

#include "battle/battle.h"
#include "battle/battle_setup.h"
#include "battle/btl_facade.h"
#include "sys/adx.h"
#include "sys/file.h"
#include "sys/heap.h"
#include "sys/save.h"

/*
 * Battle event script, first part: 0x258D20..0x259EC8.
 *
 * The battle's use of the GSC engine (src/sys/gsc.c): the module work, the scan of the script's event actions
 * at load time, the per-frame hooks, and everything that connects a script to the fight:
 *
 *   - Setup. The load job runs action 1000 to its end (Gsc_RunAction). Its commands fill this work: the story
 *     number, the text windows, who speaks which line (BtlScript_SetSpeaker) and the trigger list
 *     (BtlScript_AddLine: "say line L when trigger T fires"; BtlScript_AddEvent: "start action A when T fires").
 *   - Main task. In mode 1 Battle_ResetWork starts action -1 and keeps its task id in BattleEvents.unk4.
 *     Gsc_Update steps it every unpaused frame.
 *   - Triggers. BtlScript_Update (same frames, sequence states 3 and 5 only) tests every trigger against the
 *     battle events that are new this frame (BtlEvent_IsNew). A line is said at once if no other line is being
 *     said. An event action becomes `pending`, and BtlScript_StartPending starts it as soon as the fighters can
 *     be interrupted: the task in BattleEvents.unk4 is killed and replaced by the new action's task.
 *
 * The module goes on after 0x259EC8 with one handler per command of gBtlScriptCommands (0x259EC8..0x25C200,
 * the interpreter proper); that part is not decompiled.
 */

extern void *memset(void *dst, s32 c, u32 n);
/* file.h declares File_Request with two arguments; the callers here pass a third (0), as battle_load.c does */
#define File_Request3(id, buf, size) ((void *(*)(s32, void *, s32))File_Request)(id, buf, size)
extern void Vec4_Add(Vec4 *out, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *out, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *out, Vec4 *in, f32 scale);
/* text drawing of the next module (0x23A2D0..0x23AD48), not decompiled */
extern s32 Font_GetCmdCount(void);
extern void Font_PushStyle(void);
extern void Font_SetStyle(void *window);
extern s32 Font_GetHeight(void *text);
extern void Font_PrintAt(s32 x, s32 y, void *text);
extern void Font_PopStyle(void);
extern void Font_Flush(s32 state);
/* fighter / HUD side, not decompiled */
extern s32 BtlCtrl_IsActiveDead(s32 side);
extern void HudPrompt_ShowCue(void);
extern void HudPrompt_HideCue(void);
extern void HudPrompt_SetCueDim(s32 arg);
extern s32 BtlCtrl_GetActiveMember(s32 side);

extern List gGscTaskList;

extern BtlScriptWork gBtlScript;

/* Clears the work: no story, no text, no speaker set for any line. */
void BtlScript_InitWork(void);

/* Battle load: clears the script work. */
void BtlScript_Init(void);

/* Does nothing. */
void BtlScript_Nop(void);

/* Notes, for every event action (id 10000..10051) of the script, that it exists, its group and what it uses. */
void BtlScript_ScanEvents(s32 script);

/* Restarts the script state for a rematch. */
void BtlScript_Restart(void);

/* Per-frame update of the script side; only acts in sequence states 3 and 5. */
void BtlScript_Update(void);

/* Per-frame view update: keeps the camera shake going, runs the scripted camera move, draws the text. */
void BtlScript_UpdateView(void);

/* Frees the two loaded files and clears the work. */
void BtlScript_Free(void);

#define BtlScript_IsEventAction(id) (((id) < 10000) ? 0 : ((id) < 10052))

/* Returns 1 while a task started from an event action (10000..10051) is running. */
s32 BtlScript_IsEventRunning(void);

/* Tells every running event task to abort. */
void BtlScript_AbortEvents(void);

/* Stores the story number. */
void BtlScript_SetStory(s32 story);

/* Returns the story number. */
s32 BtlScript_GetStory(void);

/* Queues the read of the text file. */
void BtlScript_RequestTextFile(s32 id);

/* Returns entry n of the text file. */
void *BtlScript_GetText(s32 n) {
    u32 *file = gBtlScript.textFile;

    return (u8 *)file + (file[n + 1] / 4) * 4;
}

/* Queues the read of the second file. */
void BtlScript_RequestFile8(s32 id);

/* Returns entry n of the second file. */
void *BtlScript_GetFile8Entry(s32 n);

/* Returns text window n. */
BtlScriptWindow *BtlScript_GetWindow(s32 n);

/* Shows a text in a window from the next frame on. */
void BtlScript_SetText(s32 window, s32 text);

/* Hides the text if it is still the one given. */
void BtlScript_ClearText(s32 text);

/* Sets who speaks line n: bit 15 of who is the side, the low 12 bits the team member. */
void BtlScript_SetSpeaker(s32 n, s32 who);

/* Returns the speaker of line n. */
BtlScriptSpeaker *BtlScript_GetSpeaker(s32 n);

/* Returns what the scan found about the event action that is running (NULL before the first one). */
BtlScriptEvent *BtlScript_GetCurrentEvent(void);

/* Puts the view state back: no request, no text, no camera move, no shake; then resets the handlers' side. */
void BtlScript_ResetView(void);

/* Tests a trigger. 0xFFFF is "the wait flag is off"; otherwise bit 15 is the side and the low 12 bits a
 * battle event that must be new this frame. With `range`, events 0x16..0x1C also fire on any later one. */
s32 BtlScript_IsTriggered(s32 trigger, s32 range);

/* Returns the id of the streamed voice file of a line: 300 lines per story, two language sets. */
s32 BtlScript_GetVoiceFile(s32 line);

/* Registers "say this line when the trigger fires"; once = the line is switched off after it was said. */
void BtlScript_AddLine(s32 trigger, s32 line, s32 once);

/* Registers "start this event action when the trigger fires". */
void BtlScript_AddEvent(s32 trigger, s32 action);

/* Returns 1 when the voice channel of a line's speaker is silent. */
s32 BtlScript_IsLineVoiceStopped(BtlScriptLine *line);

/* Says a line: plays its voice file on the speaker's side and shows its text, unless the slot is busy. */
void BtlScript_PlayLine(BtlScriptLine *line);

/* Gives the voice channel (the side) and the text window of a speaker: window 0 when the speaker is the
 * member that is fighting, window 1 when it is another member or no member was set. */
void BtlScript_GetSpeakerSlot(s32 *side, s32 *window, BtlScriptSpeaker *speaker);

/* Returns 1 while any of the four line slots is in use. */
s32 BtlScript_IsLinePlaying(BtlScriptLine *line);

/* Starts every event action whose trigger is "wait flag off" at once. Called by BtlEvent_Raise for the
 * battle events 0x5A and 0x5B. */
void BtlScript_StartWaitEvents(void);

/* Per-frame event side of the script (sequence states 3 and 5). */
void BtlScript_UpdateEvents(void);

/* Ends lines: 60 frames after a line's voice has stopped its text is removed and its slot freed. */
void BtlScript_UpdateLines(void);

/* Tests every registered trigger: says lines, and picks the event action to start (work->pending). */
void BtlScript_UpdateRequests(void);

/* Starts the pending event action once the fight allows it: the running script task is killed and replaced.
 * What "allows" means depends on what the scan found in the action:
 *   uses command 0x4B1: at once for the triggers 0xFFFF, 0x22 and 0x49; otherwise both fighters must be
 *     interruptible and (0x20B840 true for a side, or the action's side bit set, or event 0x50 new on side 0);
 *   kind 1 or 2: the same second condition, with "the action's side can act" in place of "both interruptible";
 *   neither: at once when 0x20B840 is false for both sides, else when both fighters are interruptible. */
void BtlScript_StartPending(void);

/* While an event action is pending on side 0 and nobody is in the state 0x20B840 reports, shows the HUD cue
 * (0x22D990 / 0x22DA00); otherwise hides it (0x22D9B0). */
void BtlScript_UpdateHud(void);

/* Returns 1 when a line slot is in use. */
s32 BtlScript_IsSlotBusy(s32 side, s32 window);

/* Frees a side's first line slot and stops its voice. */
void BtlScript_StopVoice(s32 side);

/* Frees the four line slots and stops both voices and both streamed sound effects. */
void BtlScript_StopVoices(void);

/* Returns 1 while a text is shown. */
s32 BtlScript_IsTextShown(void);
