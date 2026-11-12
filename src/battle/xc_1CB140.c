/*
 * Draw callback and manager of the effect module EftMod1CB (file range in docs/agents/C_files.txt).
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

/* Draw callback: draws a live effect unless the scene hides its effects. */
void EftMod1CB_Draw(EftTTask *task) {
    XcMod1CBWork *w = task->work;
    XcMod1CBArg *arg = &w->arg;

    if (func_001267E8(arg->chr, w->type)) {
        return;
    }
    if (w->flags & XC_MOD1CB_ALIVE) {
        func_001CAD68(w, arg);
    }
}

/* Manager init: the manager block, the node pool, the two texture sets and the list of 20 tasks. */
void EftMod1CBMgr_Init(EftTTask *task) {
    XcMod1CBTex *t;
    s32 i;

    gEftMod1CBMgr = BtlPool_Alloc(BtlPool_GetCurrent(), sizeof(XcMod1CBMgr));
    memset(gEftMod1CBMgr, 0, sizeof(XcMod1CBMgr));
    gEftMod1CBMgr->pool = BtlPool_Alloc(BtlPool_GetCurrent(), 0x17700);
    memset(gEftMod1CBMgr->pool, 0, 0x17700);
    t = &gEftMod1CBMgr->tex[0];
    t->entry = func_00126460(0x20);
    t = &gEftMod1CBMgr->tex[1];
    t->entry = func_00126460(0x21);
    for (i = 0; i < 2; i++) {
        EftTexSet_Load16(gEftMod1CBMgr->tex[i].set, gEftMod1CBMgr->tex[i].entry);
    }
    gEftMod1CBMgr->table = D_00342C80;
    gEftMod1CBList = BtlTask_CreateChildList(task, 20, sizeof(XcMod1CBWork));
}

/* Manager term. */
void EftMod1CBMgr_Term(EftTTask *task) {
    BtlPool_Free(BtlPool_GetCurrent(), gEftMod1CBMgr->pool);
    BtlPool_Free(BtlPool_GetCurrent(), gEftMod1CBMgr);
    gEftMod1CBMgr = NULL;
}

/* Manager update: while effects exist, both texture sets are built again this frame. */
void EftMod1CBMgr_Update(EftTTask *task) {
    s32 i;

    if (gEftMod1CBMgr->count > 0) {
        for (i = 0; i < 2; i++) {
            gEftMod1CBMgr->tex[i].uploaded = 0;
        }
    }
}
