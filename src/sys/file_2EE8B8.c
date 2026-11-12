#include "common.h"
#include "sys/file.h"
#include "sys/heap.h"

/* libc */
extern void *memset(void *dst, s32 value, u32 size);

/* Sony libgraph / libcdvd */
extern void *sceGsSyncVCallback(s32 (*handler)(s32));
extern s32 sceCdGetDiskTypeSafe(void);
extern s32 sceCdStatus(void);
extern s32 sceCdSearchFile(void *file, char *name);

/* CRI ADX */
extern void ADXPS2_ExecVint(s32 mode);
extern void ADXPS2_SetupDvdFs(AdxDvdFsParam *param);
extern void ADXPS2_LoadFcacheDvd(AdxFcacheParam *param);
extern void ADXPS2_SetupThrd(void *param, s32 unk);
extern void ADXM_ExecMain(void);
extern void ADXM_WaitVsync(void);
extern void ADXERR_EntryErrFunc(void (*func)(void *obj, char *msg), void *obj);
extern s32 ADXF_LoadPartitionNw(s32 ptid, char *fname, void *dir, void *ptinfo);
extern s32 ADXF_GetPtStat(s32 ptid);
extern ADXF ADXF_Open(char *fname, void *atr);
extern ADXF ADXF_OpenAfs(s32 ptid, s32 flid);
extern void ADXF_Close(ADXF adxf);
extern s32 ADXF_ReadNw(ADXF adxf, s32 nsct, void *buf);
extern s32 ADXF_Stop(ADXF adxf);
extern s32 ADXF_GetFsizeSct(ADXF adxf);
extern s32 ADXF_GetStat(ADXF adxf);
extern void ADXT_Init(void);
extern ADXT_HN ADXT_Create(s32 maxnch, void *work, s32 worksize);
extern void ADXT_SetReloadSct(ADXT_HN adxt, s32 nsct);
extern void ADXT_SetSvrFreq(ADXT_HN adxt, s32 freq);
extern void ADXT_StartAfs(ADXT_HN adxt, s32 patid, s32 fid);

extern u32 gVsyncCount;
extern AfsPartition gAfsPartitionTbl[];
extern AdxPlayer gAdxPlayerTbl[];
extern char *gDiscExeNameTbl[];
extern AdxDvdFsParam gAdxDvdFsParam;
extern AdxFcacheParam gAdxFcacheParam;
extern FileReqQueue gFileReq;
extern char gFileRootDir[];
extern char gFileDirName[];

/* Unused stub that returns 0. */
s32 File_Stub264A50(void);

/* VBlank interrupt handler: counts the frame and runs the CRI vsync work. */
s32 Vsync_Handler(s32 cause);

/* Registers Vsync_Handler as the VBlank callback. */
void Vsync_InstallHandler(void);

/* CRI error callback: does nothing (the message printing was stripped). */
void File_AdxErrorCallback(void *obj, char *msg);

/* Starts loading the directory of AFS partition `pt` without blocking. */
s32 File_LoadPartitionNw(s32 pt);

/* Returns 1 once the partition directory has been read. */
s32 File_IsPartitionLoaded(s32 pt);

/* Blocks until the partition directory has been read. */
s32 File_WaitPartition(s32 pt);

/* Like File_WaitPartition, but gives up after 2400 polls. */
void File_WaitPartitionTimeout(s32 pt);

/* Brings up the whole file layer: CRI, partitions 0 and 1, the request queue. */
void File_Init(void);

/* Sets up the CRI file system and players, loads partition 0 and resets the request queue. */
void File_InitAdx(void);

/* Loads the directory of partition 1 and waits for it. */
void File_LoadPartition1(void);

/* Empty stub called once per frame by three frame loops. */
void File_Stub264D90(void);

/* Waits until `count` vblanks have passed since the last call (always at least one), then restarts the count. */
void Vsync_Wait(u32 count);

/* Identifies the inserted disc by its boot file: 0..2 = Tenkaichi 1/2/3, -1 other PS2 DVD, -2 still detecting, -3 not a PS2 DVD. */
s32 Disc_Identify(void);

/* Maps the drive status to 0..6 (stop, tray open, spin, read, pause, seek, other) and returns 7 when there is no disc. */
s32 Disc_GetDriveState(void);

/* Unused stub that returns 0. */
s32 File_Stub264F70(void);

/* Empties the request queue: every entry goes to the free list. */
void File_InitRequests(void);

/* Reads a whole file and waits for it; opens by name when id < 0, allocates the buffer when buf is NULL. */
void *File_LoadSyncEx(s32 id, char *name, void *buf, s32 unused);

/* Returns 1 while the request queue is working on a batch. */
s32 File_IsBusy(void) {
    return gFileReq.state != FILE_QUEUE_IDLE;
}

/* Number of requests not finished yet. */
s32 File_GetPendingCount(void);

/* Aborts the batch in progress: stops the read, frees the buffers the queue allocated, drops every pending request. */
void File_CancelRequests(void);

/* Queues an asynchronous read of file `id`; allocates the buffer when buf is NULL. Returns the buffer. */
void *File_Request(s32 id, void *buf);

/* Advances the request queue by one step; returns 1 when every request has been read. */
s32 File_UpdateRequests(void);

/* Size of file `id` in bytes, rounded up to whole sectors. */
s32 File_GetSize(s32 id);

/* Blocking read of a file given by path instead of id. */
void *File_LoadSyncByName(char *name, void *buf, s32 unused);

/* Blocking read of file `id`; allocates the buffer when buf is NULL. */
void *File_LoadSync(s32 id, void *buf, s32 unused);

/* Returns the request queue. */
FileReqQueue *File_GetRequestQueue(void);

/* Opens file `id`, translating the global id into (partition, index). */
ADXF File_OpenById(s32 id);

/* Starts streaming file `id` on an ADXT player, with the same id translation as File_OpenById. */
void File_StartAdxById(ADXT_HN adxt, s32 id);
