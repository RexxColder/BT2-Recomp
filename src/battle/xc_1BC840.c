/*
 * Interface functions (file range in docs/agents/C_files.txt): the by-handle interface of the particle emitter (BT2 counterpart of BT3 eft_u_b.c
 * EftPtcl_Create .. _SetStopDelay). Every function checks that the handle is a live emitter task (class update ==
 * EftPtcl3_Update, flag ALIVE) and returns 1 if it acted. View: include/battle/xc_eft_ptcl.h.
 */
#include "common.h"
#include "battle/xc_eft_ptcl.h"

extern XcPtclMgr *gEftPtcl3Mgr;        /* D_00387884 */
extern EftTTaskList *gEftPtcl3List;    /* D_00387888: the emitter tasks (40) */
extern void *gEftPtcl3Class[6];        /* D_003428F0 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 atan2f(f32 y, f32 x);
extern f32 func_0030D610(f32 x);                       /* asinf */
extern void func_00129C38(Vec4 *dst, Vec4 *src);       /* Vec3_Copy */
extern void func_00129AE8(Vec4 *dst, Vec4 *src);       /* Vec3_Normalize */
extern void func_00129B70(Vec4 *dst, Vec4 *a, Vec4 *b); /* Vec3_Sub */
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);
extern u64 EftVram_AddImage(EftTTex *tex, s32 a, s32 b);
extern u64 EftVram_AddClut(EftTTex *tex);
extern s32 func_00126748(s32 objId, s32 type);         /* BtlScene_IsEffectStopped */
extern s32 func_001267E8(s32 objId, s32 type);         /* BtlScene_IsEffectHidden */
extern s32 func_00126598(s32 objId);                   /* BtlScene_IsCharInView */
extern void func_00128EF0(void);                       /* Vu0Cur_Push */
extern void func_00128F08(void);                       /* Vu0Cur_Pop */
extern void func_00128F90(Mtx44 *m);                   /* Vu0Cur_LoadMtx */
extern u8 *gBtlCamView;
extern void BtlTask_SetDead(EftTTask *task);
extern EftTTask *BtlTaskList_AddTail(EftTTaskList *list, void *cls, void *arg);
extern EftTTaskList *BtlTask_CreateChildList(EftTTask *task, s32 count, s32 size);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);

extern void EftPtcl3_Update(EftTTask *task);
extern void EftPtcl3_UploadTexture(XcPtclWork *w, XcPtclArg *arg);
extern void EftPtcl3_Setup(XcPtclWork *w, XcPtclArg *arg);        /* 0x1BA160 */
extern void EftPtcl3_FreePtcls(XcPtclWork *w);                    /* 0x1B8BC0 */
extern void EftPtcl3_Step(XcPtclWork *w, XcPtclArg *arg);         /* 0x1BAC28 */
extern void EftPtcl3_DrawAxisQuads(XcPtclWork *w, XcPtclArg *arg, XcPtclDef *def); /* 0x1BAD80 */
extern void EftPtcl3_DrawAxisPolys(XcPtclWork *w, XcPtclArg *arg, XcPtclDef *def); /* 0x1BB3D0 */
extern void EftPtcl3_DrawShape1(XcPtclWork *w, XcPtclArg *arg);   /* 0x1BBF50 */
extern void EftPtcl3_DrawShape2(XcPtclWork *w, XcPtclArg *arg);   /* 0x1BBFB0 */
extern void EftPtcl3_PickTexture(XcPtclWork *w, s32 a, s32 b, s32 c); /* 0x1B8C08 */

#ifdef __mips__
#define IS_PTCL(task) ((task)->cls[0] == (void *)EftPtcl3_Update)
#else
/* The class table holds the PS2 address of the update (0x1BC188), not the PC one: compare against that. */
#define IS_PTCL(task) ((u32)(unsigned long)(task)->cls[0] == 0x001BC188u)
#endif









/* Sets the emitter's size factor. */
s32 EftPtcl3_SetSize(EftTTask *task, f32 size) {
    XcPtclWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_PTCL_ALIVE)) {
        return 0;
    }
    w->arg.size = size;
    return 1;
}

/* Sets the frames before the emission starts. */
s32 EftPtcl3_SetStartDelay(EftTTask *task, f32 frames) {
    XcPtclWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_PTCL_ALIVE)) {
        return 0;
    }
    w->startDelay = frames;
    return 1;
}

/* Sets the frames the emission goes on after a stop. */
s32 EftPtcl3_SetStopDelay(EftTTask *task, f32 frames) {
    XcPtclWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_PTCL_ALIVE)) {
        return 0;
    }
    w->stopDelay = frames;
    return 1;
}






