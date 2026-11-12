#include "common.h"
#include "main.h"
#include "sys/heap.h"
#include "sys/file.h"
#include "sys/dma.h"

/* Sony kernel / libkernl */
extern s32 GetThreadId(void);
extern s32 ChangeThreadPriority(s32 tid, s32 prio);
extern void FlushCache(s32 mode);

/* Sony SIF / file I/O / loadfile */
extern void sceSifInitRpc(u32 mode);
extern s32 sceSifRebootIop(char *img);
extern s32 sceSifSyncIop(void);
extern s32 sceSifLoadModule(char *name, s32 argLen, char *args);
extern s32 sceFsReset(void);
extern s32 sceOpen(char *name, s32 flags);
extern s32 sceClose(s32 fd);
extern s32 sceLseek(s32 fd, s32 offset, s32 whence);
extern s32 sceRead(s32 fd, void *buf, s32 size);

/* Sony libcdvd */
extern s32 sceCdInit(s32 mode);
extern s32 sceCdMmode(s32 media);

#define SCE_RDONLY 1
#define SCE_SEEK_SET 0
#define SCE_SEEK_END 2
#define SCECdINIT 0
#define SCECdDVD 2

/* Subsystem set-up called once from Game_Main. */
extern void Gfx_Init(void);
extern void Snd_Init(void);
extern void Movie_Init(void);
extern void Common_Init(void);
extern void Common_LoadBoot(void);
extern void Common_Reload(void);
extern void Progress_Init(void);
extern void Save_Init(void);
extern void Job_Init(void);
extern void Vu0_Init(void);
extern void Dbg_Init(void);
extern void Pad_Init(void);
extern void McCard_Init(void);
extern void Font_Init(s32);
extern void FontIcon_Init(void);
extern void Fade_Init(void);
extern void PadWatch_Init(void);
extern void Sys_InitIopHeap(void);

extern void Progress_Main(s32); /* DBZP.BIN entry: menu / mode dispatcher */
extern void Battle_Main(s32);

extern OverlayEntry gOverlayTbl[];
extern u8 MainMenu_StartBallLoops[]; /* overlay load address */

/* Program entry called by crt0: runs the game, which never returns. (The compiler adds the call to __main, the static
 * constructor runner, by itself.) */
s32 main(void);

/* Reads overlay `idx` from disc to its fixed address, retrying until the open and the read succeed. */
s32 Overlay_Load(s32 idx) {
    s32 fd;
    s32 size;

    do {
        fd = sceOpen(gOverlayTbl[idx].path, SCE_RDONLY);
    } while (fd < 0);
    size = sceLseek(fd, 0, SCE_SEEK_END);
    sceLseek(fd, 0, SCE_SEEK_SET);
    FlushCache(0);
    while (sceRead(fd, MainMenu_StartBallLoops, size) != size) {
    }
    FlushCache(2);
    sceClose(fd);
    return 0;
}

/* Reboots the IOP with the IOPRP300 image from disc and brings SIF RPC, the CD drive and file I/O back up. */
void Sys_RebootIop(void);

/* Loads the 13 IOP modules from disc (each retried until it loads), then binds the IOP heap service. */
void Sys_LoadIopModules(void);

/* Initialises every subsystem in order, then alternates forever between the menu overlay and a battle. */
void Game_Main(void);

/* Queues a GS scissor packet for the view's scissor rectangle. */
void View_ApplyScissor(ViewScissor *view);
