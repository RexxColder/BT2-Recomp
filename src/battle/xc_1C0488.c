/*
 * Task callbacks of the second emitter module EftPtcl4 (file ranges in docs/agents/C_files.txt).
 * View: include/battle/xc_eft_ptcl4.h. Drawing only.
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

/* Builds the TEX0 of the emitter's texture entry the first time it is used this frame. */
void EftPtcl4_UploadTexture(XcPtcl4Work *w, XcPtcl4Arg *arg) {
    s32 i;
    s32 end;

    if (!(arg->res->uploaded & (1 << arg->texIdx))) {
        end = arg->texIdx + 1;
        for (i = arg->texIdx; i < end; i++) {
            arg->res->tex[i].tex0 = EftVram_AddTex(&arg->res->tex[i], 1, 0);
        }
        arg->res->uploaded = 1 << arg->texIdx;
    }
}

/* Init callback: clears the work, copies the argument block and sets the emitter up. */
void EftPtcl4_Init(EftTTask *task, XcPtcl4Arg *arg) {
    XcPtcl4Work *w = task->work;

    memset(w, 0, sizeof(XcPtcl4Work));
    w->arg = *arg;
    func_001BD7B8(w, arg);
}

/* Term callback: frees the nodes. */
void EftPtcl4_Term(EftTTask *task) {
    XcPtcl4Work *w = task->work;

    w->flags = 0;
    func_001BCDE8(w);
}

/* Update callback: steps the emitter unless the scene stops its effects; ends the task once it is dead. */
void EftPtcl4_Update(EftTTask *task) {
    XcPtcl4Work *w = task->work;
    XcPtcl4Arg *arg = &w->arg;

    if (!func_00126748(arg->objId, w->type)) {
        func_001BDF90(w, arg);
    }
    if (w->flags & XC_PTCL4_DEAD) {
        BtlTask_SetDead(task);
    } else {
        EftPtcl4_UploadTexture(w, arg);
    }
}
