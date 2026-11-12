/*
 * Memory card operations (0x116B98..0x1198D8). The file stem is a placeholder: this is system code
 * (proper home src/sys/mcard.c), unrelated to the stage drawing in front of it.
 *
 * Every operation is polled: the caller invokes it once per frame until it returns 1. gMcCardCmd names the
 * operation that owns the step counter gMcCardStep; an operation entered while another one's command is set
 * restarts from step 0. Each step issues one libmc call or polls sceMcSync once. On an error the step simply
 * does not advance and the function keeps returning 0: the caller looks at the port record (ret / result),
 * classifies the code with McCard_IsFatalError and resets the step with McCard_ResetStep.
 * A library call that returns -200 (the library is still busy) is answered with sceMcSync(1, NULL, NULL).
 * sceMcSync(1, ...) returns 0 while the pending call runs; most steps go on for any other value, the steps
 * written `!= 1` only for "finished".
 *
 * Library functions (Sony libmc, not named yet; identified by their arguments):
 *   func_002A1A48 sceMcInit()                         func_002A1E58 sceMcOpen(port, slot, name, mode)
 *   func_002A1F80 sceMcMkdir(port, slot, name)        func_002A1FB8 sceMcClose(fd)
 *   func_002A2078 sceMcSeek(fd, offset, origin)       func_002A2208 sceMcRead(fd, buf, size)
 *   func_002A2320 sceMcWrite(fd, buf, size)           func_002A2498 sceMcSync(mode, cmd, result)
 *   func_002A25B8 sceMcGetInfo(port, slot, type, free, format)
 *   func_002A27A8 sceMcGetDir(port, slot, name, mode, maxent, table)
 *   func_002A2AC8 sceMcFormat(port, slot)
 */
#include "common.h"
#include "sys/heap.h"
#include "battle/stgm_a_b.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern char *strcpy(char *dst, const char *src);
extern s32 sprintf(char *dst, const char *fmt, ...);

extern s32 func_002A1A48(void);
extern s32 func_002A1E58(s32 port, s32 slot, char *name, s32 mode);
extern s32 func_002A1F80(s32 port, s32 slot, char *name);
extern s32 func_002A1FB8(s32 fd);
extern s32 func_002A2078(s32 fd, s32 offset, s32 origin);
extern s32 func_002A2208(s32 fd, void *buf, s32 size);
extern s32 func_002A2320(s32 fd, void *buf, s32 size);
extern s32 func_002A2498(s32 mode, s32 *cmd, s32 *result);
extern s32 func_002A25B8(s32 port, s32 slot, s32 *type, s32 *free, s32 *format);
extern s32 func_002A27A8(s32 port, s32 slot, char *name, s32 mode, s32 maxent, void *table);
extern s32 func_002A2AC8(s32 port, s32 slot);

#define sceMcInit func_002A1A48
#define sceMcOpen func_002A1E58
#define sceMcMkdir func_002A1F80
#define sceMcClose func_002A1FB8
#define sceMcSeek func_002A2078
#define sceMcRead func_002A2208
#define sceMcWrite func_002A2320
#define sceMcSync func_002A2498
#define sceMcGetInfo func_002A25B8
#define sceMcGetDir func_002A27A8
#define sceMcFormat func_002A2AC8

/* 0x2FE918 / 0x2FE91C: the head of this object's .sdata, in front of its strings. */
s32 gMcCardStep = 0;
s32 gMcCardCmd = 0;
extern McCardPort gMcCardPort[2];
extern McCardIconSys gMcCardIconSys;

/* Sony's 16-byte aligned vectors (sceVu0IVECTOR / sceVu0FVECTOR): the icon.sys constants are locals of these
 * types (they are initialised with aligned 64-bit copies), the fields of icon.sys itself are not aligned. */
typedef s32 McCardIVec[4] __attribute__((aligned(16)));
typedef f32 McCardFVec[4] __attribute__((aligned(16)));

/* An operation entered while another operation's command is set starts over. */
#define MCCARD_ENTER(cmd) \
    if (gMcCardCmd != 0) { \
        gMcCardStep = (gMcCardCmd == (cmd)) ? gMcCardStep : 0; \
    }


/* Tells the result codes the caller gives up on: -19..-11, -49..-40, -59..-50 and -79..-70. */
s32 McCard_IsFatalError(s32 code) {
    if (code >= -19 && code <= -11) {
        return 1;
    }
    if (code >= -49 && code <= -40) {
        return 1;
    }
    if (code >= -59 && code <= -50) {
        return 1;
    }
    if (code >= -79 && code <= -70) {
        return 1;
    }
    return 0;
}

/* Lists the card's root directory into `table`. 1 when finished. Nothing calls it. */
s32 McCard_ReadDir(s32 port, s32 maxEntries, void *table) {
    s32 ret;

    MCCARD_ENTER(MCCARD_CMD_DIR);
    switch (gMcCardStep) {
    case 0:
        gMcCardPort[port].result = 0;
        gMcCardCmd = MCCARD_CMD_DIR;
        ret = sceMcGetDir(port, 0, "*", 0, maxEntries, table);
        gMcCardPort[port].ret = ret;
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, NULL, NULL);
                return 0;
            }
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 1:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        gMcCardStep = 0;
        gMcCardCmd = 0;
        return 1;
    default:
        gMcCardStep = 0;
        gMcCardCmd = 0;
        return 1;
    }
}
