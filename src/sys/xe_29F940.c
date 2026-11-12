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


/* Debug dump of the current command (output compiled out). */
void Gsc_DumpCurrent(void) {
    GscChunk *data = gGscCurTask->data;

    Gsc_DumpCommand(gGscCurTask->pc, (GscChunk *)((u8 *)data + data->headSize));
}

/* Debug dump of one command and its operands. The printing was compiled out: what is left is the table of
 * operand type names, the range check of the switch on the word kind, and the walk over the words. The case
 * bodies below are placeholders: any stores that are dead once the printing is gone give the original code. */
void Gsc_DumpCommand(u32 *cmd, GscChunk *data) {
    char *typeNames[5] = { "int   ", "float ", "string" };
    s32 kind;

    do {
        kind = *cmd & 0xF;
        switch (kind) {
        case GSC_WORD_COMMAND:
            kind = ((u8 *)cmd)[1];
            break;
        case GSC_WORD_CALL:
            kind = ((s16 *)cmd)[1];
            break;
        case GSC_WORD_CALL_WAIT:
            kind = ((s16 *)cmd)[1];
            break;
        case GSC_WORD_OPTION:
            kind = ((u8 *)cmd)[2];
            break;
        case GSC_WORD_OPERAND:
            kind = (*cmd >> 4) & 0xF;
            break;
        }
        cmd++;
    } while (*cmd & GSC_WORD_ARG);
}

/* Debug dump of every command of every action of a file (output compiled out). */
void Gsc_DumpFileNode(GscFile *file) {
    GscChunk *action;
    u32 *data;
    u32 *cmd;

    action = (GscChunk *)((u8 *)file->code + file->code->headSize);
    data = (u32 *)((u8 *)file->data + file->data->headSize);
    while (GSC_SWAP(action->tag) == GSC_TAG_GSAC) {
        cmd = (u32 *)((u8 *)action + action->headSize);
        while ((*cmd & 0xF) != GSC_WORD_END) {
            Gsc_DumpCommand(cmd, (GscChunk *)data);
            cmd = Gsc_NextCommand(cmd);
        }
        action = GSC_NEXT_CHUNK(action);
    }
}

/* Debug dump of every use of one command id in a file (output compiled out). */
void Gsc_DumpCommandsById(GscFile *file, s32 id) {
    GscChunk *action;
    u32 *data;
    u32 *cmd;

    action = (GscChunk *)((u8 *)file->code + file->code->headSize);
    data = (u32 *)((u8 *)file->data + file->data->headSize);
    while (GSC_SWAP(action->tag) == GSC_TAG_GSAC) {
        cmd = (u32 *)((u8 *)action + action->headSize);
        while ((*cmd & 0xF) != GSC_WORD_END) {
            if ((*cmd & 0xF) == GSC_WORD_COMMAND && ((u16 *)cmd)[1] == id) {
                Gsc_DumpCommand(cmd, (GscChunk *)data);
            }
            cmd = Gsc_NextCommand(cmd);
        }
        action = GSC_NEXT_CHUNK(action);
    }
}
