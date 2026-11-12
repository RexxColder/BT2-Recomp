/*
 * The by-handle interface of the ribbon (BT3 eft_ab_c.c EftRibbon_Create .. _SetType; file range in
 * docs/agents/C_files.txt). View: include/battle/xc_eft_ribbon.h.
 */
#include "common.h"
#include "battle/xc_eft_ribbon.h"

extern XcRibbonMgr *gEftRibbonMgr;     /* D_0038789C */
extern EftTTaskList *gEftRibbonList;   /* D_003878A0: the ribbon tasks (40) */
extern void *gEftRibbonClass[6];       /* D_003429B0 */

extern void *memset(void *dst, s32 c, u32 n);
extern void func_00129C28(Vec4 *dst, Vec4 *src);       /* Vec4_Copy */
extern void func_00129C38(Vec4 *dst, Vec4 *src);       /* Vec3_Copy */
extern s32 func_00126748(s32 objId, s32 type);         /* BtlScene_IsEffectStopped */
extern s32 func_001267E8(s32 objId, s32 type);         /* BtlScene_IsEffectHidden */
extern void func_00128EF0(void);                       /* Vu0Cur_Push */
extern void func_00128F08(void);                       /* Vu0Cur_Pop */
extern void func_00128F90(Mtx44 *m);                   /* Vu0Cur_LoadMtx */
extern s32 *func_00126460(s32 idx);                    /* BtlScene_GetCommonEntry */
extern void EftTexSet_Load16(void *set, s32 *entry);
extern u8 *gBtlCamView;
extern void BtlTask_SetDead(EftTTask *task);
extern EftTTask *BtlTaskList_AddTail(EftTTaskList *list, void *cls, void *arg);
extern EftTTaskList *BtlTask_CreateChildList(EftTTask *task, s32 count, s32 size);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern void EftTrail_End(void *trail, s32 frames);
extern void EftTrail_SetPos(void *trail, Vec4 *pos);

extern void EftRibbon_Update(EftTTask *task);
extern void EftRibbon_FreeNodes(XcRibbonWork *w);
extern void EftRibbon_SetTexPair(XcRibbonWork *w, s32 slot, void *uv, s32 a, s32 b);
extern void func_001C5320(void *prm, void *tex, XcRibbonWork *w, XcRibbonArg *arg); /* step */
extern void func_001C6B28(void *prm, XcRibbonWork *w, XcRibbonArg *arg);  /* texture */
extern void func_001C55B8(void *tex, XcRibbonWork *w, XcRibbonArg *arg);  /* draw kind 0 */
extern void func_001C6278(void *tex, XcRibbonWork *w, XcRibbonArg *arg);  /* draw kind 1 */

#ifdef __mips__
#define IS_RIBBON(task) ((task)->cls[0] == (void *)EftRibbon_Update)
#else
/* The class table holds the PS2 address of the update (0x1C6E40), not the PC one: compare against that. */
#define IS_RIBBON(task) ((u32)(unsigned long)(task)->cls[0] == 0x001C6E40u)
#endif

/* Creates a ribbon task; returns it (NULL when all 40 are in use). */
EftTTask *EftRibbon_Create(XcRibbonArg *arg) {
    XcRibbonArg a = *arg;

    return BtlTaskList_AddTail(gEftRibbonList, gEftRibbonClass, &a);
}

/* Starts the fade-out. */
s32 EftRibbon_Stop(EftTTask *task) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    w->flags |= XC_RIBBON_STOP;
    return 1;
}

/* Makes the next update kill the task. */
s32 EftRibbon_Kill(EftTTask *task) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    w->flags |= XC_RIBBON_DEAD;
    return 1;
}

/* Both of the above. */
s32 EftRibbon_StopAndKill(EftTTask *task) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    w->flags |= XC_RIBBON_STOP | XC_RIBBON_DEAD;
    return 1;
}

/* True when the task is a live ribbon. */
s32 EftRibbon_IsAlive(EftTTask *task) {
    if (task == NULL) {
        return 0;
    }
    if (!IS_RIBBON(task)) {
        return 0;
    }
    if (((XcRibbonWork *)task->work)->flags & XC_RIBBON_ALIVE) {
        return 1;
    }
    return 0;
}

/* Writes the first point. */
s32 EftRibbon_SetPos(EftTTask *task, Vec4 *pos) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_RIBBON(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    func_00129C28((Vec4 *)&w->arg.pos, pos);
    return 1;
}

/* Writes the second point (kind 2: hands it to the trail); with `place`, also moves the first node there. */
s32 EftRibbon_SetEnd(EftTTask *task, Vec4 *pos, u8 place) {
    XcRibbonWork *w;
    Vec4 *end;

    if (task == NULL) {
        return 0;
    }
    if (!IS_RIBBON(task)) {
        return 0;
    }
    w = task->work;
    end = &w->end;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    func_00129C28(end, pos);
    if (w->kind == 2) {
        EftTrail_SetPos(w->trail, end);
        return 1;
    }
    if (place && w->head != NULL) {
        func_00129C38(&w->head->pos, end);
    }
    return 1;
}

/* Writes the size factor. */
s32 EftRibbon_SetSize(EftTTask *task, f32 size) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_RIBBON(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    w->arg.size = size;
    return 1;
}

/* Writes +0x5C. */
s32 EftRibbon_SetUnk5C(EftTTask *task, s32 value) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_RIBBON(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    w->unk5C = value;
    return 1;
}

/* Writes the fade-out length in frames (1 at least). */
s32 EftRibbon_SetFadeTime(EftTTask *task, s32 frames) {
    XcRibbonWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_RIBBON(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_RIBBON_ALIVE)) {
        return 0;
    }
    w->fadeTime = frames;
    if (w->fadeTime < 1.0f) {
        w->fadeTime = 1.0f;
    }
    return 1;
}


