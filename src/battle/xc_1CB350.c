/*
 * The by-handle interface of the effect module EftMod1CB (file range in docs/agents/C_files.txt).
 * View: include/battle/xc_eft_1cb.h.
 */
#include "common.h"
#include "battle/xc_eft_1cb.h"

extern XcMod1CBMgr *gEftMod1CBMgr;     /* D_003878B8 */
extern EftTTaskList *gEftMod1CBList;   /* D_003878BC (20 tasks) */
extern void *gEftMod1CBClass[6];       /* D_00342C68 */
extern u8 D_00342C80[];

extern void *memset(void *dst, s32 c, u32 n);
extern void func_00129C38(Vec4 *dst, Vec4 *src);       /* Vec3_Copy */
extern s32 func_00126748(s32 objId, s32 type);         /* BtlScene_IsEffectStopped */
extern s32 func_001267E8(s32 objId, s32 type);         /* BtlScene_IsEffectHidden */
extern s32 *func_00126460(s32 idx);                    /* BtlScene_GetCommonEntry */
extern void EftTexSet_Load16(void *set, s32 *entry);
extern void BtlTask_SetDead(EftTTask *task);
extern EftTTask *BtlTaskList_AddTail(EftTTaskList *list, void *cls, void *arg);
extern EftTTaskList *BtlTask_CreateChildList(EftTTask *task, s32 count, s32 size);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);

extern void EftMod1CB_Update(EftTTask *task);
extern void func_001C9D50(XcMod1CBWork *w, XcMod1CBArg *arg, void *prm);   /* setup */
extern void func_001C9688(XcMod1CBWork *w);                                /* frees the nodes */
extern void func_001CA428(void *prm, XcMod1CBWork *w, XcMod1CBArg *arg);   /* step */
extern void func_001CADB0(XcMod1CBWork *w, XcMod1CBArg *arg);              /* texture */
extern void func_001CAD68(XcMod1CBWork *w, XcMod1CBArg *arg);              /* draw */

#define IS_MOD1CB(task) ((task)->cls[0] == (void *)0x001CB078u) /* PS2 address of EftMod1CB_Update */

/* Creates a task; returns it (NULL when all 20 are in use). */
EftTTask *EftMod1CB_Create(XcMod1CBArg *arg) {
    XcMod1CBArg a = *arg;

    return BtlTaskList_AddTail(gEftMod1CBList, gEftMod1CBClass, &a);
}

/* Lets the effect finish. */
s32 EftMod1CB_Stop(EftTTask *task) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    w = task->work;
    if (w == NULL) {
        return 0;
    }
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    w->flags |= XC_MOD1CB_STOP;
    return 1;
}

/* Makes the next update kill the task. */
s32 EftMod1CB_Kill(EftTTask *task) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    w = task->work;
    if (w == NULL) {
        return 0;
    }
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    w->flags |= XC_MOD1CB_DEAD;
    return 1;
}

/* True when the task is a live effect of this module. */
s32 EftMod1CB_IsAlive(EftTTask *task) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_MOD1CB(task)) {
        return 0;
    }
    w = task->work;
    return (w->flags & XC_MOD1CB_ALIVE) && w->flags;
}

/* Moves the effect. */
s32 EftMod1CB_SetPos(EftTTask *task, Vec4 *pos) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_MOD1CB(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    func_00129C38((Vec4 *)&w->arg.pos, pos);
    return 1;
}

/* Writes the size factor. */
s32 EftMod1CB_SetSize(EftTTask *task, f32 size) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_MOD1CB(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    w->arg.size = size;
    return 1;
}

/* Writes +0x64. */
s32 EftMod1CB_SetUnk64(EftTTask *task, f32 v) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_MOD1CB(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    w->unk64 = v;
    return 1;
}

/* Writes +0x68. */
s32 EftMod1CB_SetUnk68(EftTTask *task, f32 v) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_MOD1CB(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    w->unk68 = v;
    return 1;
}

/* Stores the effect pack type the stop / hide tests use. */
s32 EftMod1CB_SetType(EftTTask *task, s32 type) {
    XcMod1CBWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_MOD1CB(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & XC_MOD1CB_ALIVE)) {
        return 0;
    }
    w->type = type;
    return 1;
}
