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


/* Boot: clears the port records, starts libmc and probes port 0. */
void McCard_Init(void) {
    memset(gMcCardPort, 0, sizeof(gMcCardPort));
    sceMcInit();
    McCard_Probe(0);
}

/* Reads type, free space and format state of a card. Step 2 = finished; the caller resets the step. */
s32 McCard_GetInfo(s32 port) {
    s32 ret;

    MCCARD_ENTER(MCCARD_CMD_INFO);
    switch (gMcCardStep) {
    case 0:
        gMcCardPort[port].result = 0;
        gMcCardCmd = MCCARD_CMD_INFO;
        ret = sceMcGetInfo(port, 0, &gMcCardPort[port].type, &gMcCardPort[port].free, &gMcCardPort[port].format);
        gMcCardPort[port].ret = ret;
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, NULL, NULL);
            }
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 1:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 1) {
            gMcCardStep++;
            return 1;
        }
        return 0;
    }
    /* Past step 1 nothing is returned (v0 still holds the 1 of the step comparison). */
}

/* The same, waiting for the result inside the call. */
s32 McCard_GetInfoSync(s32 port) {
    gMcCardPort[port].result = 0;
    gMcCardCmd = MCCARD_CMD_INFO_SYNC;
    gMcCardPort[port].ret = sceMcGetInfo(port, 0, &gMcCardPort[port].type, &gMcCardPort[port].free,
                                         &gMcCardPort[port].format);
    return sceMcSync(0, NULL, &gMcCardPort[port].result);
}

/* Asks for the card state without outputs and waits: only the result code is kept. */
s32 McCard_Probe(s32 port) {
    gMcCardCmd = MCCARD_CMD_INFO_PROBE;
    gMcCardPort[port].result = 0;
    gMcCardPort[port].ret = sceMcGetInfo(port, 0, NULL, NULL, NULL);
    return sceMcSync(0, NULL, &gMcCardPort[port].result);
}

/* The same, polled: 1 when the result is in. */
s32 McCard_CheckChange(s32 port) {
    s32 ret;

    MCCARD_ENTER(MCCARD_CMD_CHANGE);
    switch (gMcCardStep) {
    case 0:
        gMcCardPort[port].result = 0;
        gMcCardCmd = MCCARD_CMD_CHANGE;
        ret = sceMcGetInfo(port, 0, NULL, NULL, NULL);
        gMcCardPort[port].ret = ret;
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, NULL, NULL);
            }
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 1:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        gMcCardStep++;
        return 1;
    }
}

/* Formats the card: 1 when the format finished without error (or when called past its last step). */
s32 McCard_Format(s32 port) {
    s32 ret;

    MCCARD_ENTER(MCCARD_CMD_FORMAT);
    switch (gMcCardStep) {
    case 0:
        gMcCardPort[port].result = 0;
        gMcCardCmd = MCCARD_CMD_FORMAT;
        ret = sceMcFormat(port, 0);
        gMcCardPort[port].ret = ret;
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, NULL, NULL);
            }
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 1:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
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

/*
 * Creates a save: makes the directory (an existing one is fine), writes icon.sys and the icon file.
 * 1 when the last step finished. The data file is written by McCard_WriteSave.
 */
s32 McCard_CreateSave(s32 port, McCardFile *file) {
    McCardIVec bgColor[4] = {
        { 0xFF, 0x80, 0, 0 }, { 0xFF, 0x80, 0, 0 }, { 0x80, 0x80, 0x80, 0 }, { 0x80, 0x80, 0x80, 0 },
    };
    McCardFVec lightDir[3] = {
        { 0.5f, 0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.5f, 0.0f }, { 0.5f, 0.5f, 0.5f, 0.0f },
    };
    McCardFVec lightColor[3] = {
        { 0.3f, 0.3f, 0.03f, 0.0f }, { 0.3f, 0.2f, 0.2f, 0.0f }, { 0.14f, 0.14f, 0.2f, 0.0f },
    };
    McCardFVec ambient = { 0.25f, 0.25f, 0.25f, 0.0f };
    s32 ret;

    MCCARD_ENTER(MCCARD_CMD_CREATE);
    switch (gMcCardStep) {
    case 0:
        gMcCardPort[port].result = 0;
        gMcCardCmd = MCCARD_CMD_CREATE;
        ret = sceMcMkdir(port, 0, file->dir);
        gMcCardPort[port].ret = ret;
        if (ret < 0) {
            if (ret == -200) {
                sceMcSync(1, NULL, NULL);
            }
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 1:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            if (gMcCardPort[port].result != -4) {
                return 0;
            }
            gMcCardPort[port].result = 0;
        }
        gMcCardStep++;
        return 0;
    case 2:
        gMcCardPort[port].ret = sceMcOpen(port, 0, file->sysPath, 0x202);
        if (gMcCardPort[port].ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 3:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            return 0;
        }
        gMcCardPort[port].fd = gMcCardPort[port].result;
        gMcCardStep++;
        return 0;
    case 4:
        memset(&gMcCardIconSys, 0, sizeof(McCardIconSys));
        strcpy(gMcCardIconSys.head, "PS2D");
        strcpy(gMcCardIconSys.title, file->title);
        gMcCardIconSys.titleBreak = file->titleBreak;
        gMcCardIconSys.transRate = 0x60;
        memcpy(gMcCardIconSys.bgColor, bgColor, sizeof(bgColor));
        memcpy(gMcCardIconSys.lightDir, lightDir, sizeof(lightDir));
        memcpy(gMcCardIconSys.lightColor, lightColor, sizeof(lightColor));
        memcpy(gMcCardIconSys.ambient, ambient, sizeof(ambient));
        strcpy(gMcCardIconSys.viewName, file->iconName[0]);
        strcpy(gMcCardIconSys.copyName, file->iconName[1]);
        strcpy(gMcCardIconSys.delName, file->iconName[2]);
        gMcCardPort[port].ret = sceMcWrite(gMcCardPort[port].fd, &gMcCardIconSys, sizeof(McCardIconSys));
        if (gMcCardPort[port].ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 5:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 6:
        gMcCardPort[port].ret = sceMcClose(gMcCardPort[port].fd);
        if (gMcCardPort[port].ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 7:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 8:
        gMcCardPort[port].ret = sceMcOpen(port, 0, file->iconPath[0], 0x202);
        if (gMcCardPort[port].ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 9:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            return 0;
        }
        gMcCardPort[port].fd = gMcCardPort[port].result;
        gMcCardStep++;
        return 0;
    case 10:
        gMcCardPort[port].ret = sceMcWrite(gMcCardPort[port].fd, file->icon, file->iconSize);
        if (gMcCardPort[port].ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 11:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 12:
        gMcCardPort[port].ret = sceMcClose(gMcCardPort[port].fd);
        if (gMcCardPort[port].ret < 0) {
            return 0;
        }
        gMcCardStep++;
        return 0;
    case 13:
        if (sceMcSync(1, NULL, &gMcCardPort[port].result) == 0) {
            return 0;
        }
        if (gMcCardPort[port].result < 0) {
            return 0;
        }
        gMcCardStep++;
        return 1;
    default:
        gMcCardStep = 0;
        gMcCardCmd = 0;
        return 1;
    }
}
