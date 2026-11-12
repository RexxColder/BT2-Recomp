/*
 * Task callbacks of the effect module EftMod1CB (file range in docs/agents/C_files.txt).
 * View: include/battle/xc_eft_1cb.h. Drawing only.
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

/* Init callback: clears the work, copies the argument block, sets the effect up and counts it. */
void EftMod1CB_Init(EftTTask *task, XcMod1CBArg *arg) {
    XcMod1CBWork *w = task->work;
    void *prm = arg->prm;

    memset(w, 0, sizeof(XcMod1CBWork));
    w->arg = *arg;
    w->arg.unk4 = 0;
    func_001C9D50(w, arg, prm);
    gEftMod1CBMgr->count++;
}

/* Term callback: frees the nodes and uncounts the effect. */
void EftMod1CB_Term(EftTTask *task) {
    XcMod1CBWork *w = task->work;

    w->flags = 0;
    func_001C9688(w);
    gEftMod1CBMgr->count--;
}

/* Update callback: steps a live effect unless the scene stops its effects; kills the task once it is dead. */
void EftMod1CB_Update(EftTTask *task) {
    XcMod1CBWork *w = task->work;
    XcMod1CBArg *arg = &w->arg;
    void *prm = arg->prm;

    if (!func_00126748(arg->chr, w->type) && (w->flags & XC_MOD1CB_ALIVE)) {
        func_001CA428(prm, w, arg);
    }
    if (w->flags & XC_MOD1CB_DEAD) {
        BtlTask_SetDead(task);
    } else {
        func_001CADB0(w, arg);
    }
}
