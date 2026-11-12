/*
 * Task callbacks of the effect module EftMod1CC (file range in docs/agents/C_files.txt).
 * View: include/battle/xc_eft_1cc.h. Drawing only.
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
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void func_001CBA98(EftTTask *task, Vec4 *p, u64 tex0, f32 a, f32 b); /* draw kind 0 */
extern void func_001CC0A0(EftTTask *task);                                  /* draw kind 1 */

#define IS_MOD1CC(task) ((task)->cls[0] == (void *)0x001CC770u) /* PS2 address of EftMod1CC_Update */

/* Init callback: copies the argument block, converts the timings (seconds to frames at 30 fps), sets up the
   texture animation grid and picks the texture. */
void EftMod1CC_Init(EftTTask *task, XcMod1CCWork *arg) {
    XcMod1CCWork *w = task->work;
    Vec4 *v = arg->unk38;
    XcMod1CCPrm *prm = arg->prm;

    memset(w, 0, sizeof(XcMod1CCWork));
    *(XcMod1CCArgBlock *)w = *(XcMod1CCArgBlock *)arg;
    w->flags |= XC_MOD1CC_ALIVE;
    if (arg->life <= 0.0f) {
        w->flags |= XC_MOD1CC_ENDLESS;
    } else {
        w->lifeFrames = arg->life * 30.0f;
    }
    w->unk64 = prm->unk8;
    w->unk74 = 0;
    w->unk68 = prm->unkC;
    w->unk78 = prm->unk18 * 30.0f;
    w->unk7C = prm->unk14 - prm->unk10;
    func_00129C38(&w->unk80, v);
    w->unk80.w = 0.0f;
    w->unk70 = v->w / prm->unk1C;
    Vec4_Set(&w->unk90, w->unk80.w, 1.0f, w->unk80.w, 1.0f);
    w->frames = prm->cols * prm->rows;
    if (w->frames >= 2) {
        w->flags |= XC_MOD1CC_ANIM;
        w->du = 1.0f / prm->cols;
        w->dv = 1.0f / prm->rows;
    } else {
        w->dv = 1.0f;
        w->du = 1.0f;
    }
    EftMod1CC_SetTex(w, arg->res, arg->texIdx, arg->texIdx);
}

/* Term callback. */
void EftMod1CC_Term(EftTTask *task) {
    XcMod1CCWork *w = task->work;

    w->flags = 0;
}

/* Update callback: steps the effect unless the scene stops its effects; kills the task once it is dead, else
   builds its TEX0. */
void EftMod1CC_Update(EftTTask *task) {
    XcMod1CCWork *w = task->work;

    if (!func_00126748(w->chr, w->type)) {
        func_001CB6E8(w);
    }
    if (w->flags & XC_MOD1CC_DEAD) {
        BtlTask_SetDead(task);
    } else {
        EftMod1CC_BuildTex(w, w);
    }
}
