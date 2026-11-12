#define EftPtcl3_FreePtcls func_001B8BC0  /* fix_targets */ /* the original uses 0x1b8bc0 here */
#define EftPtcl3_Setup func_001BA160  /* fix_targets */ /* the original uses 0x1ba160 here */
#define EftPtcl3_Step func_001BAC28  /* fix_targets */ /* the original uses 0x1bac28 here */
/*
 * 0x1BC010..0x1BC210: task callbacks of the particle emitter (BT2 counterpart of BT3 eft_u_b.c EftPtcl3_UploadTexture,
 * _Init, _Term, _Update). View: include/battle/xc_eft_ptcl.h. Drawing only.
 */
#include "common.h"
#include "battle/xc_eft_ptcl.h"

extern XcPtclMgr *gEftPtcl3Mgr;        /* D_00387884 */
extern EftTTaskList *gEftPtcl3List;    /* D_00387888: the emitter tasks (40) */
extern void *gEftPtcl3Class[6];        /* D_003428F0 */

extern void *memset(void *dst, s32 c, u32 n);
extern f32 atan2f(f32 y, f32 x);
extern f32 func_0030D610(f32 x);                       /* asinf */
extern void func_00129C38(Vec4 *dst, Vec4 *src);       /* Vec3_Copy */
extern void func_00129AE8(Vec4 *dst, Vec4 *src);       /* Vec3_Normalize */
extern void func_00129B70(Vec4 *dst, Vec4 *a, Vec4 *b); /* Vec3_Sub */
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Mtx_RotateX(Mtx44 *dst, Mtx44 *src, f32 angle);
extern void Mtx_RotateY(Mtx44 *dst, Mtx44 *src, f32 angle);
extern u64 EftVram_AddImage(EftTTex *tex, s32 a, s32 b);
extern u64 EftVram_AddClut(EftTTex *tex);
extern s32 func_00126748(s32 objId, s32 type);         /* BtlScene_IsEffectStopped */
extern s32 func_001267E8(s32 objId, s32 type);         /* BtlScene_IsEffectHidden */
extern s32 func_00126598(s32 objId);                   /* BtlScene_IsCharInView */
extern void func_00128EF0(void);                       /* Vu0Cur_Push */
extern void func_00128F08(void);                       /* Vu0Cur_Pop */
extern void func_00128F90(Mtx44 *m);                   /* Vu0Cur_LoadMtx */
extern u8 *gBtlCamView;
extern void BtlTask_SetDead(EftTTask *task);
extern EftTTask *BtlTaskList_AddTail(EftTTaskList *list, void *cls, void *arg);
extern EftTTaskList *BtlTask_CreateChildList(EftTTask *task, s32 count, s32 size);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);

extern void EftPtcl3_Update(EftTTask *task);
extern void EftPtcl3_UploadTexture(XcPtclWork *w, XcPtclArg *arg);
extern void EftPtcl3_Setup(XcPtclWork *w, XcPtclArg *arg);        /* 0x1BA160 */
extern void EftPtcl3_FreePtcls(XcPtclWork *w);                    /* 0x1B8BC0 */
extern void EftPtcl3_Step(XcPtclWork *w, XcPtclArg *arg);         /* 0x1BAC28 */
extern void EftPtcl3_DrawAxisQuads(XcPtclWork *w, XcPtclArg *arg, XcPtclDef *def); /* 0x1BAD80 */
extern void EftPtcl3_DrawAxisPolys(XcPtclWork *w, XcPtclArg *arg, XcPtclDef *def); /* 0x1BB3D0 */
extern void EftPtcl3_DrawShape1(XcPtclWork *w, XcPtclArg *arg);   /* 0x1BBF50 */
extern void EftPtcl3_DrawShape2(XcPtclWork *w, XcPtclArg *arg);   /* 0x1BBFB0 */
extern void EftPtcl3_PickTexture(XcPtclWork *w, s32 a, s32 b, s32 c); /* 0x1B8C08 */

#ifdef __mips__
#define IS_PTCL(task) ((task)->cls[0] == (void *)EftPtcl3_Update)
#else
/* The class table holds the PS2 address of the update (0x1BC188), not the PC one: compare against that. */
#define IS_PTCL(task) ((u32)(unsigned long)(task)->cls[0] == 0x001BC188u)
#endif

/* The emitter'"'"'s TEX0 for this frame: uploads image and palette the first time the set'"'"'s entry is used this frame and
   caches the value in the set; later emitters take the cached value. */
void EftPtcl3_UploadTexture(XcPtclWork *w, XcPtclArg *arg) {
    if (!(arg->res->uploaded & (1U << arg->texIdx))) {
        w->tex0 = EftVram_AddImage(&w->texA, 1, 0);
        w->tex0 |= (u64)EftVram_AddClut(&w->texB) << 37;
        arg->res->tex[arg->texIdx].tex0 = w->tex0;
        arg->res->uploaded |= 1U << arg->texIdx;
    } else {
        w->tex0 = arg->res->tex[arg->texIdx].tex0;
    }
}

/* Init callback: clears the work, copies the argument block and sets the emitter up. */
void EftPtcl3_Init(EftTTask *task, XcPtclArg *arg) {
    XcPtclWork *w = task->work;

    memset(w, 0, sizeof(XcPtclWork));
    w->arg = *arg;
    EftPtcl3_Setup(w, arg);
}

/* Term callback: frees the particles. */
void EftPtcl3_Term(EftTTask *task) {
    XcPtclWork *w = task->work;

    w->flags = 0;
    EftPtcl3_FreePtcls(w);
}

/* Update callback: steps the emitter unless the scene stops its effects; ends the task once it is dead. */
void EftPtcl3_Update(EftTTask *task) {
    XcPtclWork *w = task->work;
    XcPtclArg *arg = &w->arg;

    if (!func_00126748(arg->objId, w->type)) {
        EftPtcl3_Step(w, arg);
    }
    if (w->flags & XC_PTCL_DEAD) {
        BtlTask_SetDead(task);
    } else {
        EftPtcl3_UploadTexture(w, arg);
    }
}
