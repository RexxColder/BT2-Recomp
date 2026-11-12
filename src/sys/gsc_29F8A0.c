#include "common.h"
#include "sys/gsc.h"
#include "sys/heap.h"

/*
 * GSC script engine: 0x257870..0x258D20.
 *
 * A small cooperative script machine. A script file is registered with Gsc_LoadFile, an "action" of it is
 * started as a task with Gsc_StartAction, and Gsc_Update steps every task once per frame. The engine knows
 * nothing about the game: each command id is looked up in a table of handlers given to Gsc_Init.
 *
 * File ("GSCF"), all words little-endian, every chunk = 0x10-byte header {tag, headSize, dataSize, arg},
 * dataSize bytes, then a 0x10-byte "EOFC" trailer:
 *   GSCF  wraps the whole file
 *     GSHD  header data (not read by this file)
 *     GSCD  code: a run of GSAC chunks, ended by anything that is not a GSAC
 *       GSAC  one action; arg = action id (-1 = the main action); data = 32-bit script words
 *     GSDT  data: 4-byte values (int, float or anything a handler takes the address of)
 *
 * Script words (low nibble = kind):
 *   0   end of the action: the task is freed
 *   1   command: byte 1 = number of plain operand words that follow, bytes 2..3 = command id
 *   2   start action (s16 in bytes 2..3) as a new task, step it once, go on
 *   3   start action and wait until that task is gone
 *   8   option: byte 1 = a letter, byte 2 = number of operand words that follow it
 *   10  operand: bits 8..31 index a 4-byte value in GSDT. Bits 4..7 give its type in the files (0 int,
 *       1 float; the dump's name table adds 2 = string) but no code left in the game reads them: the handler
 *       decides by calling Gsc_GetInt, Gsc_GetFloat or Gsc_GetString.
 * Options follow the plain operands of a command; every word with bit 3 set belongs to the command before.
 * A handler reads its plain operands in order, and looks an option up by its letter (Gsc_FindOption) before
 * reading that option's operands, so a command line reads like "cmd 1 2 -l 4.0 -w".
 *
 * A command runs in phases (see GSC_PHASE_*): BEGIN once, UPDATE every frame until it returns non-zero, then
 * END. A command that is not done stops the task for this frame and adds 10 to the task's timer.
 */

extern s32 gGscActive;
extern GscCommand *gGscCommands;
extern s32 gGscFileSerial;
extern s32 gGscFileMax;
extern GscFile *gGscFilePool;
extern GscTask *gGscCurTask;
extern s32 gGscTaskMax;
extern GscTask *gGscTaskPool;
extern List gGscTaskList; /* running tasks */
extern List gGscFileFree;
extern List gGscFileList; /* loaded files */
extern List gGscTaskFree;

/* Allocates the file and task pools and puts every element on its free list. */
void Gsc_Init(GscCommand *commands, s32 fileMax, s32 taskMax);

/* Starts the engine with room for 10 files and 50 tasks. */
void Gsc_InitDefault(GscCommand *commands);

/* Shuts the engine down and frees both pools. */
void Gsc_Exit(void);

/* Does nothing. */
void Gsc_Nop(void);

/* Replaces the command table. */
void Gsc_SetCommands(GscCommand *commands);

/* Steps every running task once. */
void Gsc_Update(void);

/* Steps the task with this id once. */
void Gsc_StepTaskById(s32 id);

/* Calls the handler of every task's current command with phase 3. */
void Gsc_NotifyAll(void);

/* Runs a task until one of its commands has to wait or its action ends. */
void Gsc_StepTask(GscTask *task);

/* Registers a loaded script file and returns its handle. */
s32 Gsc_LoadFile(GscChunk *file);

/* Kills the tasks of a file and releases it. */
void Gsc_UnloadFile(s32 handle);

/* Returns the loaded file with this handle, or NULL. */
GscFile *Gsc_FindFile(s32 handle);

/* Returns 1 when a file with this handle is loaded. */
s32 Gsc_IsFileLoaded(s32 handle);

/* Returns the number of loaded files. */
s32 Gsc_GetFileCount(void);

/* Returns the running task with this id, or NULL. */
GscTask *Gsc_FindTask(s32 id);

/* Returns 1 while the task with this id is running. */
s32 Gsc_IsTaskAlive(s32 id);

/* Returns the number of running tasks. */
s32 Gsc_GetTaskCount(void);

/* Returns how long the task's current command has been waiting (10 per frame), 0 if there is no such task. */
s32 Gsc_GetTaskTime(s32 id);

/* Starts the main action (id -1) of a file. */
s32 Gsc_StartMain(s32 handle);

/* Starts an action and steps it until it has ended. */
void Gsc_RunAction(s32 handle, s32 action);

/* Starts an action of a file as a new task and returns the task id. */
s32 Gsc_StartAction(s32 handle, s32 action);

/* Stops a task at once. */
void Gsc_KillTask(s32 id);

/* Tells a task to abort: its commands are begun with phase 4 from now on. */
void Gsc_AbortTask(s32 id);

/* Returns 1 when the file has an action with this id. */
s32 Gsc_HasAction(s32 handle, s32 action);

/* Returns the task being stepped (NULL outside a step). */
GscTask *Gsc_GetCurrentTask(void);

/* From inside a task: starts another action of the same file, steps it once and returns its task id. */
s32 Gsc_CallAction(s32 action) {
    GscTask *cur = Gsc_GetCurrentTask();
    s32 id = Gsc_StartAction(Gsc_GetFileHandle(cur->id), action);

    Gsc_StepTask(Gsc_FindTask(id));
    gGscCurTask = cur;
    return id;
}

/* Returns how long the current command has been waiting (10 per frame). */
s32 Gsc_GetCurrentTime(void) {
    return Gsc_GetTaskTime(Gsc_GetCurrentTask()->id);
}

/* Returns bit 0 of the current task's flags (the command has been begun). */
s32 Gsc_IsCurrentBegun(void);

/* Debug dump of a whole file (output compiled out). */
void Gsc_DumpFile(s32 handle);

/* Debug dump of the current command (output compiled out). */
void Gsc_DumpCurrent(void);

/* Debug dump of one command and its operands. The printing was compiled out: what is left is the table of
 * operand type names, the range check of the switch on the word kind, and the walk over the words. The case
 * bodies below are placeholders: any stores that are dead once the printing is gone give the original code. */
void Gsc_DumpCommand(u32 *cmd, GscChunk *data);

/* Debug dump of every command of every action of a file (output compiled out). */
void Gsc_DumpFileNode(GscFile *file);

/* Debug dump of every use of one command id in a file (output compiled out). */
void Gsc_DumpCommandsById(GscFile *file, s32 id);

/* Returns the next operand of the current command as an integer. */
s32 Gsc_GetInt(void);

/* Returns the next operand of the current command as a float. */
f32 Gsc_GetFloat(void);

/* Returns the next operand of the current command as a string (the address of its data). */
char *Gsc_GetString(void);

/* Returns the next integer operand, or def when the command has none left. */
s32 Gsc_GetIntOr(s32 def);

/* Returns the next float operand, or def when the command has none left. */
f32 Gsc_GetFloatOr(f32 def);

/* Returns the next string operand, or def when the command has none left. */
char *Gsc_GetStringOr(char *def);

/* Skips one operand of the current command; returns 0 when there was none. */
s32 Gsc_SkipOperand(void);

/* Puts the operand cursor on the word after the current command word. */
void Gsc_ResetOperands(void);

/* Puts the cursor on the operands of the first option with this letter; returns 0 if there is none. */
s32 Gsc_FindOption(s8 letter);

/* Puts the cursor on the operands of the n-th option with this letter; returns 0 if there is none. */
s32 Gsc_FindOptionN(s8 letter, s32 n);

/* Puts the cursor on the operands of the n-th option of any letter and returns its letter (0 if none). */
s32 Gsc_SeekOption(s32 n);

/* Returns the number of options of the current command. */
s32 Gsc_CountOptions(void);

/* Returns how many options of the current command have this letter. */
s32 Gsc_CountOption(s8 letter);

/* Returns 1 when the word at the operand cursor is an operand. */
s32 Gsc_HasOperand(void);

/* Makes a file handle from a serial number. */
s32 Gsc_MakeFileHandle(s32 serial);

/* Makes a task id from a file handle and the file's task serial. */
s32 Gsc_MakeTaskId(s32 handle, s32 serial);

/* Returns the file handle part of a task id. */
s32 Gsc_GetFileHandle(s32 id);

/* Returns the command word that follows a command, its operands and its options. */
u32 *Gsc_NextCommand(u32 *cmd);

/* Returns the address of the value of the operand at the cursor, or NULL if the word is not an operand. */
void *GscTask_PeekOperand(GscTask *task);

/* Returns the value address of the operand at the cursor and moves past it; NULL if there is none. */
void *GscTask_NextOperand(GscTask *task, s32 type);

/* Returns the handler of a command id, or NULL when the table does not have it. */
GscHandler Gsc_FindHandler(s32 id);

/* Returns the first unused file slot (it stays on the free list until Gsc_LinkFile). */
GscFile *Gsc_GetFreeFile(void);

/* Moves a file slot from the free list to the loaded list. */
void Gsc_LinkFile(GscFile *file);

/* Frees every task started from a file, then returns the file slot to the free list. */
void Gsc_FreeFile(GscFile *file);

/* Returns the first unused task slot (it stays on the free list until Gsc_LinkTask). */
GscTask *Gsc_GetFreeTask(void);

/* Moves a task slot from the free list to the front of the running list. */
void Gsc_LinkTask(GscTask *task);

/* Moves a task from the running list back to the free list. */
void Gsc_FreeTask(GscTask *task);

/* Returns the first command word of the action with this id, or NULL when the file has no such action. */
u32 *Gsc_FindAction(GscChunk *code, s32 action, s32 unused);
