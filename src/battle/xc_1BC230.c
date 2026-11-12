#define EftPtcl3_DrawAxisPolys func_001BB3D0  /* fix_targets */ /* the original uses 0x1bb3d0 here */
#define EftPtcl3_DrawAxisQuads func_001BAD80  /* fix_targets */ /* the original uses 0x1bad80 here */
#define EftPtcl3_DrawShape1 func_001BBF50  /* fix_targets */ /* the original uses 0x1bbf50 here */
#define EftPtcl3_DrawShape2 func_001BBFB0  /* fix_targets */ /* the original uses 0x1bbfb0 here */
/*
 * 0x1BC230..0x1BC430: draw callback and manager init / term of the particle emitter (BT2 counterpart of BT3
 * eft_u_b.c EftPtcl_Draw, EftPtclMgr_Init, EftPtclMgr_Term). View: include/battle/xc_eft_ptcl.h.
 */
#include "common.h"
#include "battle/xc_eft_ptcl.h"

extern XcPtclMgr *gEftPtcl3Mgr;        /* D_00387884 */
extern EftTTaskList *gEftPtcl3List;    /* D_00387888: the emitter tasks (40) */
extern void *gEftPtcl3Class[6];        /* D_003428F0 */

extern void *memset(void *dst, s32 c, u32 n);
extern void bt2_fightlog_note(const char *fmt, ...);
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

/* Draw callback: picks the draw routine for the definition's shape, unless the effect is hidden or belongs to the
   view of the other fighter. */
void EftPtcl3_Draw(EftTTask *task) {
    XcPtclWork *w = task->work;
    XcPtclArg *arg = &w->arg;
    XcPtclDef *def = arg->def;
    static unsigned nCall, nHid, nView, nOk; /* TEMP: chispas de golpe */

    if ((++nCall % 300) == 0) bt2_fightlog_note("PTCL3-DRAW llamadas %u ocultas %u fuera-de-vista %u dibujadas %u (shape %d flags %x obj %d tipo %d)",
                                                nCall, nHid, nView, nOk, def ? def->shape : -1, w->flags, arg->objId, w->type);
    if (func_001267E8(arg->objId, w->type)) {
        nHid++;
        return;
    }
    if ((w->flags & XC_PTCL_FRONT) && !func_00126598(arg->objId)) {
        nView++;
        return;
    }
    nOk++;
    func_00128EF0();
    func_00128F90((Mtx44 *)(gBtlCamView + 0x100));
    switch (def->shape) {
    case 1:
        EftPtcl3_DrawShape1(w, arg);
        break;
    case 2:
        EftPtcl3_DrawShape2(w, arg);
        break;
    case 0:
        if (w->flags & XC_PTCL_POLYS) {
            EftPtcl3_DrawAxisPolys(w, arg, def);
        } else {
            EftPtcl3_DrawAxisQuads(w, arg, def);
        }
        break;
    }
    func_00128F08();
}

/* Manager init: the manager block, the particle pool and the list of 40 emitter tasks. */
void EftPtcl3Mgr_Init(EftTTask *task) {
    gEftPtcl3Mgr = BtlPool_Alloc(BtlPool_GetCurrent(), sizeof(XcPtclMgr));
    memset(gEftPtcl3Mgr, 0, sizeof(XcPtclMgr));
    gEftPtcl3Mgr->pool = BtlPool_Alloc(BtlPool_GetCurrent(), 0x33F40);
    memset(gEftPtcl3Mgr->pool, 0, 0x33F40);
    gEftPtcl3List = BtlTask_CreateChildList(task, 40, sizeof(XcPtclWork));
}

/* Manager term: frees the pool and the manager block. */
void EftPtcl3Mgr_Term(EftTTask *task) {
    BtlPool_Free(BtlPool_GetCurrent(), gEftPtcl3Mgr->pool);
    BtlPool_Free(BtlPool_GetCurrent(), gEftPtcl3Mgr);
    gEftPtcl3Mgr = NULL;
}
