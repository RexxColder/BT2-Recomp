#include "common.h"

/*
 * Body lightning task reset, 0x17FFC0..0x17FFF0 (BT3 src/battle/eft_o.c, same code). Cut off from xb_17FC00.c by
 * the src/auto/ stub at 0x17FFB8; the draw that follows (0x17FFF0) is not C yet (it needs its .lit4 literal).
 */
#define BtlScene_GetCharCount func_00126580
#define BtlScene_GetCommonEntry func_00126460

#include "battle/eft_o.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void *BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(void *pool, s32 size);
extern s32 BtlScene_GetCharCount(void);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern void *BtlTask_CreateChildList(EftOTask *task, s32 count, s32 workSize);
extern void BtlTask_SetDead(EftOTask *task);
extern void EftTexSet_Load32(void *set, s32 *pack);

/* Reset callback: the task dies. */
void EftBoltTask_Reset(EftOTask *task) {
    EftOBoltWork *w = task->work;

    gEftBoltPool->tasks[w->objId] = NULL;
    BtlTask_SetDead(task);
}

