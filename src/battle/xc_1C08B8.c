/*
 * The by-handle interface of the second emitter module EftPtcl4 (file ranges in docs/agents/C_files.txt). Every
 * function checks that the handle is a live emitter task and returns 1 if it acted.
 * View: include/battle/xc_eft_ptcl4.h.
 */
#include "common.h"
#include "battle/xc_eft_ptcl4.h"

extern XcPtcl4Mgr *gEftPtcl4Mgr;       /* D_0038788C */
extern EftTTaskList *gEftPtcl4List;    /* D_00387890: the emitter tasks (10) */
extern void *gEftPtcl4Class[6];        /* D_00342920 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 atan2f(f32 y, f32 x);
extern f32 func_0030D610(f32 x);                       /* asinf */
extern void func_00129C38(Vec4 *dst, Vec4 *src);       /* Vec3_Copy */
extern void func_00129AE8(Vec4 *dst, Vec4 *src);       /* Vec3_Normalize */
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);
extern u64 EftVram_AddTex(EftTTex *tex, s32 a, s32 b);
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

extern void EftPtcl4_Update(EftTTask *task);
extern void func_001BD7B8(XcPtcl4Work *w, XcPtcl4Arg *arg);   /* setup */
extern void func_001BCDE8(XcPtcl4Work *w);                    /* frees the node list */
extern void func_001BDF90(XcPtcl4Work *w, XcPtcl4Arg *arg);   /* step */
extern void func_001BF030(XcPtcl4Work *w, XcPtcl4Arg *arg, XcPtcl4Def *def); /* draw: axis quads */
extern void func_001BF690(XcPtcl4Work *w, XcPtcl4Arg *arg, XcPtcl4Def *def); /* draw: axis polygons */
extern void func_001C02C0(XcPtcl4Work *w, XcPtcl4Arg *arg);   /* draw: shape 1 */
extern void func_001C03F0(XcPtcl4Work *w, XcPtcl4Arg *arg);   /* draw: shape 3 */

#ifdef __mips__
#define IS_PTCL4(task) ((task)->cls[0] == (void *)EftPtcl4_Update)
#else
/* The class table holds the PS2 address of the update (0x1C05F8), not the PC one: compare against that. */
#define IS_PTCL4(task) ((u32)(unsigned long)(task)->cls[0] == 0x001C05F8u)
#endif

/* Creates an emitter task; returns the task (the effect pack's handle). */
EftTTask *EftPtcl4_Create(XcPtcl4Arg *arg) {
    XcPtcl4Arg a = *arg;

    return BtlTaskList_AddTail(gEftPtcl4List, gEftPtcl4Class, &a);
}

/* Stops the emission. */
s32 EftPtcl4_Stop(EftTTask *task) {
    XcPtcl4Work *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL4(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_PTCL4_ALIVE)) {
        return 0;
    }
    w->flags |= XC_PTCL4_STOP;
    return 1;
}

/* Kills the emitter: its task ends on the next update. */
s32 EftPtcl4_Kill(EftTTask *task) {
    XcPtcl4Work *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL4(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_PTCL4_ALIVE)) {
        return 0;
    }
    w->flags |= XC_PTCL4_DEAD;
    return 1;
}

/* Tells whether the handle is a live emitter. */
s32 EftPtcl4_IsAlive(EftTTask *task) {
    XcPtcl4Work *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL4(task)) {
        return 0;
    }
    w = task->work;
    return (w->flags & XC_PTCL4_ALIVE) && w->flags;
}

/* Moves the emitter. */
s32 EftPtcl4_SetPos(EftTTask *task, Vec4 *pos) {
    XcPtcl4Work *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_PTCL4(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_PTCL4_ALIVE)) {
        return 0;
    }
    func_00129C38((Vec4 *)&w->arg.pos, pos);
    return 1;
}







