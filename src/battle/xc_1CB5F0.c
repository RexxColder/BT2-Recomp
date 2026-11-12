/*
 * Texture helpers of the effect module EftMod1CC (file range in docs/agents/C_files.txt; same code as BT3 eft_s.c
 * EftChain_SetTex / _BuildTex). View: include/battle/xc_eft_1cc.h.
 */
#include "common.h"
#include "battle/xc_eft_1cc.h"

extern s32 *gEftMod1CCMgr;             /* D_003878C0 */
extern EftTTaskList *gEftMod1CCList;   /* D_003878C4 (20 tasks) */
extern void *gEftMod1CCClass[6];       /* D_00342D98 */

extern void *memset(void *dst, s32 c, u32 n);
extern void func_00129C38(Vec4 *dst, Vec4 *src);       /* Vec3_Copy */
extern void func_00129AE8(Vec4 *dst, Vec4 *src);       /* Vec3_Normalize */
extern s32 func_00126748(s32 objId, s32 type);         /* BtlScene_IsEffectStopped */
extern s32 func_001267E8(s32 objId, s32 type);         /* BtlScene_IsEffectHidden */
extern s32 func_00126598(s32 objId);                   /* BtlScene_IsCharInView */
extern void func_00128EF0(void);                       /* Vu0Cur_Push */
extern void func_00128F08(void);                       /* Vu0Cur_Pop */
extern void func_00128F90(Mtx44 *m);                   /* Vu0Cur_LoadMtx */
extern u8 *gBtlCamView;
extern u64 EftVram_AddImage(EftTTex *tex, s32 a, s32 b);
extern u64 EftVram_AddClut(EftTTex *tex);
extern void BtlTask_SetDead(EftTTask *task);
extern EftTTask *BtlTaskList_AddTail(EftTTaskList *list, void *cls, void *arg);
extern EftTTaskList *BtlTask_CreateChildList(EftTTask *task, s32 count, s32 size);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);

extern void EftMod1CC_Update(EftTTask *task);
extern void EftMod1CC_SetTex(XcMod1CCWork *w, XcMod1CCRes *res, s32 a, s32 b);
extern void EftMod1CC_BuildTex(XcMod1CCWork *w, XcMod1CCWork *w2);
extern void func_001CB6E8(XcMod1CCWork *w);                                 /* step */
extern void func_001CBA98(EftTTask *task, Vec4 *p, u64 tex0, f32 a, f32 b); /* draw kind 0 */
extern void func_001CC0A0(EftTTask *task);                                  /* draw kind 1 */

#define IS_MOD1CC(task) ((task)->cls[0] == (void *)0x001CC770u) /* PS2 address of EftMod1CC_Update */

/* Copies entries a (image) and b (palette) of a texture set into the work and remembers b as the cache slot. */
void EftMod1CC_SetTex(XcMod1CCWork *w, XcMod1CCRes *res, s32 a, s32 b) {
    w->texA = ((EftTTex *)res)[a];
    w->texB = ((EftTTex *)res)[b];
    w->texIdx = b;
}

/* The effect's TEX0 for this frame: uploads image and palette the first time the set's entry is used this frame
   and caches the value in the set. */
void EftMod1CC_BuildTex(XcMod1CCWork *w, XcMod1CCWork *w2) {
    if (!(w2->res->uploaded & (1U << w2->texIdx))) {
        w->tex0 = EftVram_AddImage(&w->texA, 1, 0);
        w->tex0 |= (u64)EftVram_AddClut(&w->texB) << 37;
        w2->res->tex[w2->texIdx].tex0 = w->tex0;
        w2->res->uploaded |= 1U << w2->texIdx;
    } else {
        w->tex0 = w2->res->tex[w2->texIdx].tex0;
    }
}
