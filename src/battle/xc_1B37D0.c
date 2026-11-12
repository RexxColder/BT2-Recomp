#include "common.h"
#include "battle/xc_eft_chain.h"

/*
 * 0x1B3378..0x1B3E68: the by-handle interface of the "chain" effect (effect pack part kind 18) and the ray burst
 * (part kind 0): create, stop / kill / is-alive, setters, the ray manager class callbacks. Same functions as BT3's
 * eft_s.c (second part, formerly eft_t.c, 0x17CCD0..0x17D8E0), with BT2's chain work layout
 * (include/battle/xc_eft_chain.h). Drawing only.
 */

extern EftTTaskList *gEftChain2List;   /* D_00387874: the chain tasks (10) */
extern EftRayMgr *gEftRay;            /* D_00387878 */
extern void *gEftChain2Class[6];       /* D_003427E8 */
extern void *gEftRayClass[6];         /* D_00342818 */

extern void *memset(void *dst, s32 c, u32 n);
extern void func_00129C28(Vec4 *dst, Vec4 *src); /* Vec4_Copy */
extern void func_00129C38(Vec4 *dst, Vec4 *src); /* Vec3_Copy */
extern void func_0012A3A0(Vec4 *dst, Vec4 *a, Vec4 *b, Vec4 *c, Vec4 *d); /* Vec3_Add4 */
extern void func_003126C8(Vec4 *dst, Vec4 *src);
extern EftTTask *BtlTaskList_AddTail(EftTTaskList *list, void *cls, void *arg);
extern EftTTaskList *BtlTask_CreateChildList(EftTTask *task, s32 count, s32 size);
extern void func_001F3738(EftTTask *task, s32 bits); /* copy of BtlTask_SetTagBits */
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 *func_00126460(s32 idx); /* BtlScene_GetCommonEntry */
extern void EftTexSet_Load32(EftRayMgr *set, s32 *entry);
extern void EftChain2_Update(EftTTask *task);
extern void EftChain2_SetTex(XcChainWork *w, s32 a, s32 b, s32 c);
extern void EftRay_Update(EftTTask *task);
extern void EftRay_Setup(EftRayWork *w, XcRayArg *arg);
extern void EftRay_StepTexture(void);

extern const f32 D_00384FC0; /* 0.3f */
extern const f32 D_00384FC4; /* -1.2f */


#define IS_CHAIN2(task) ((task)->cls[0] == (void *)0x001B2FD0u) /* PS2 address of EftChain2_Update */





/* The strand at 0x40 past a walking pointer (as BT3: the original steps a pointer from the work's start). */
#define XC_CHAIN_STRAND(p) ((XcChainStrand *)((u8 *)(p) + 0x40))







/* Restricts drawing to the view that shows the owner. */
s32 EftChain2_SetViewOnly(EftTTask *task) {
    XcChainWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_CHAIN2(task)) {
        return 0;
    }
    w = task->work;
    if (w == NULL) {
        return 0;
    }
    if (!(w->flags & EFT_CHAIN_ALIVE)) {
        return 0;
    }
    w->flags |= EFT_CHAIN_VIEW_ONLY;
    return 1;
}

/* Stores the owner's effect type. */
s32 EftChain2_SetType(EftTTask *task, s32 type) {
    XcChainWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_CHAIN2(task)) {
        return 0;
    }
    w = task->work;
    if (w == NULL) {
        return 0;
    }
    if (!(w->flags & EFT_CHAIN_ALIVE)) {
        return 0;
    }
    w->type = type;
    return 1;
}

/* ---- ray burst -------------------------------------------------------------------------------------------- */

#define IS_RAY(task) ((task)->cls[0] == (void *)0x001B3E68u) /* PS2 address of EftRay_Update */

/* Starts a ray burst; returns its task. */
EftTTask *EftRay_Create(XcRayArg *arg) {
    XcRayArg a;

    if (gEftRay == NULL) {
        return NULL;
    }
    a = *arg;
    return BtlTaskList_AddTail(gEftRay->list, gEftRayClass, &a);
}

/* Moves the centre, unless the fade is over. */
s32 EftRay_SetPos(EftTTask *task, Vec4 *pos) {
    EftRayWork *w;

    if (gEftRay == NULL) {
        return 0;
    }
    if (task == NULL) {
        return 0;
    }
    if (task->flags & 1) {
        return 0;
    }
    if (!IS_RAY(task)) {
        return 0;
    }
    w = task->work;
    if ((w->flags & EFT_RAY_FADED) || (w->flags & EFT_RAY_DEAD)) {
        return 0;
    }
    func_00129C28((Vec4 *)&w->pos, pos);
    return 1;
}

/* Starts the fade and lets the task end itself after it. */
s32 EftRay_Kill(EftTTask *task) {
    EftRayWork *w;

    if (gEftRay == NULL) {
        return 0;
    }
    if (task == NULL) {
        return 0;
    }
    if (task->flags & 1) {
        return 0;
    }
    if (!IS_RAY(task)) {
        return 0;
    }
    w = task->work;
    w->flags |= EFT_RAY_FADING | EFT_RAY_AUTOKILL;
    return 1;
}

/* Stores the owner's effect type. */
s32 EftRay_SetType(EftTTask *task, s32 type) {
    EftRayWork *w;

    if (gEftRay == NULL) {
        return 0;
    }
    if (task == NULL) {
        return 0;
    }
    if (task->flags & 1) {
        return 0;
    }
    if (!IS_RAY(task)) {
        return 0;
    }
    w = task->work;
    w->type = type;
    return 1;
}

/* 1 while the burst runs. A burst whose fade is over is reported dead once and then ends itself. */
s32 EftRay_IsAlive(EftTTask *task) {
    EftRayWork *w;

    if (gEftRay == NULL) {
        return 0;
    }
    if (task == NULL) {
        return 0;
    }
    if (task->flags & 1) {
        return 0;
    }
    if (!IS_RAY(task)) {
        return 0;
    }
    w = task->work;
    if (w->flags & EFT_RAY_FADED) {
        w->flags |= EFT_RAY_DEAD;
        return 0;
    }
    return 1;
}

EftTTask *EftRay_StartHit(s32 objId, Vec4 *pos, s32 delay, s32 fade, s32 unused, f32 life);

/* The hit burst with its default timing: no delay, a 10-frame fade after 0.5 s. */
EftTTask *EftRay_StartHitDefault(s32 objId, Vec4 *pos) {
    return EftRay_StartHit(objId, pos, 0, 10, 0, 0.5f);
}


EftTTask *EftRay_CreateByValue(XcRayArg arg);







