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












/* Writes +0x58. */
s32 EftRibbon_SetUnk58(EftTTask *task, s32 value) {
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
    w->unk58 = value;
    return 1;
}
