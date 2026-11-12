#include "common.h"

/*
 * Body lightning manager init, 0x180088..0x180248 (BT3 src/battle/eft_o.c; BT2 reads common entries 6 / 7 for the
 * two textures and 0xA for the node pair table, BT3 5 / 6 and 4). Term and update follow in BT3 transplants.
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

/* Init callback of the manager: the joint pool (100 per fighter), the task table and the two texture sets. */
void EftBoltMgr_Init(EftOTask *task) {
    EftOBoltTex *t;
    s32 i;

    gEftBoltPool = BtlPool_Alloc(BtlPool_GetCurrent(), sizeof(EftOBoltPool));
    memset(gEftBoltPool, 0, sizeof(EftOBoltPool));
    gEftBoltPool->count = BtlScene_GetCharCount();
    gEftBoltPool->max = gEftBoltPool->count * 100;
    gEftBoltPool->pool = BtlPool_Alloc(BtlPool_GetCurrent(), gEftBoltPool->max << 6);
    memset(gEftBoltPool->pool, 0, gEftBoltPool->max << 6);
    gEftBoltPool->tasks = BtlPool_Alloc(BtlPool_GetCurrent(), gEftBoltPool->count * 4);
    memset(gEftBoltPool->tasks, 0, gEftBoltPool->count * 4);
    t = &gEftBoltPool->tex[0];
    t->pack = BtlScene_GetCommonEntry(6);
    t = &gEftBoltPool->tex[1];
    t->pack = BtlScene_GetCommonEntry(7);
    for (i = 0; i < 2; i++) {
        EftTexSet_Load32(&gEftBoltPool->tex[i].set, gEftBoltPool->tex[i].pack);
    }
    gEftBoltPool->pack4 = BtlScene_GetCommonEntry(0xA);
    for (i = 0; i < gEftBoltPool->count; i++) {
        gEftBoltPool->tasks[i] = NULL;
    }
    gEftBoltList = BtlTask_CreateChildList(task, gEftBoltPool->count, sizeof(EftOBoltWork));
}

