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


/* Sets the size. */
s32 EftChain2_SetSize(EftTTask *task, f32 size) {
    XcChainWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_CHAIN2(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & EFT_CHAIN_ALIVE)) {
        return 0;
    }
    w->arg.size = size;
    return 1;
}

/* Sets the module's parameter 3, clamped to 3..7. */
s32 EftChain2_SetParam3(EftTTask *task, s32 v) {
    XcChainWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_CHAIN2(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & EFT_CHAIN_ALIVE)) {
        return 0;
    }
    w->param3 = v;
    if (v < 3) {
        w->param3 = 3;
    } else if (v >= 8) {
        w->param3 = 7;
    }
    return 1;
}

/* Sets the module's parameter 5. */
s32 EftChain2_SetParam5(EftTTask *task, f32 v) {
    XcChainWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_CHAIN2(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & EFT_CHAIN_ALIVE)) {
        return 0;
    }
    w->param5 = v;
    return 1;
}

/* Sets the module's parameter 6. */
s32 EftChain2_SetParam6(EftTTask *task, f32 v) {
    XcChainWork *w;

    if (task == NULL) {
        return 0;
    }
    if (!IS_CHAIN2(task)) {
        return 0;
    }
    w = task->work;
    if (!(w->flags & EFT_CHAIN_ALIVE)) {
        return 0;
    }
    w->param6 = v;
    return 1;
}




/* ---- ray burst -------------------------------------------------------------------------------------------- */

#define IS_RAY(task) ((task)->cls[0] == (void *)0x001B3E68u) /* PS2 address of EftRay_Update */






EftTTask *EftRay_StartHit(s32 objId, Vec4 *pos, s32 delay, s32 fade, s32 unused, f32 life);



EftTTask *EftRay_CreateByValue(XcRayArg arg);







