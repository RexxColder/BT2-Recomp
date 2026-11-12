/*
 * Draw callback and manager of the ribbon (BT3 eft_ab_c.c EftRibbon_Draw, EftRibbonMgr_*; file range in
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

/* Draw callback: draws kinds 0 and 1 (kind 2 is drawn by its trail) unless the effect is hidden. */
void EftRibbon_Draw(EftTTask *task) {
    XcRibbonWork *w = task->work;
    XcRibbonArg *arg = &w->arg;
    void *tex;

    if (func_001267E8(arg->chr, arg->type)) {
        return;
    }
    if (w->kind != 2) {
        tex = arg->tex;
        func_00128EF0();
        func_00128F90((Mtx44 *)(gBtlCamView + 0x100));
        if (w->kind == 0) {
            func_001C55B8(tex, w, arg);
        } else if (w->kind == 1) {
            func_001C6278(tex, w, arg);
        }
        func_00128F08();
    }
}

/* Manager init: the manager block, the node buffer, the module's texture set (common entry 0x26) and the list of
   40 ribbon tasks. */
void EftRibbonMgr_Init(EftTTask *task) {
    XcRibbonMgr *m;

    gEftRibbonMgr = BtlPool_Alloc(BtlPool_GetCurrent(), sizeof(XcRibbonMgr));
    memset(gEftRibbonMgr, 0, sizeof(XcRibbonMgr));
    gEftRibbonMgr->nodes = BtlPool_Alloc(BtlPool_GetCurrent(), 40000);
    memset(gEftRibbonMgr->nodes, 0, 40000);
    m = gEftRibbonMgr;
    {
        XcRibbonTex *t = &m->tex;

        t->entry = func_00126460(0x26);
        EftTexSet_Load16(t->set, t->entry);
    }
    gEftRibbonList = BtlTask_CreateChildList(task, 40, sizeof(XcRibbonWork));
}

/* Manager term. */
void EftRibbonMgr_Term(EftTTask *task) {
    BtlPool_Free(BtlPool_GetCurrent(), gEftRibbonMgr->nodes);
    BtlPool_Free(BtlPool_GetCurrent(), gEftRibbonMgr);
    gEftRibbonMgr = NULL;
}

/* Manager update: the texture set is built again this frame. */
void EftRibbonMgr_Update(EftTTask *task) {
    gEftRibbonMgr->uploaded = 0;
}
