#include "common.h"

/*
 * Aura manager, 0x17CAA8..0x17CE18 (BT3 src/battle/eft_n.c, EftAuraMgr_Init .. EftAuraMgr_Update). BT2
 * differences: the parameter file is common entry 8 and is kept at 0x498; the texture groups hold entries 2 / 3;
 * the update runs the per-character lightning check every frame (BT3: only after the stage became ready).
 */
#define gEftAuraCfg D_0038777C
#define gEftAuraPrm D_00387780
#define gEftAuraTaskList D_00387784
#define BtlScene_GetCharCount func_00126580
#define BtlScene_GetCommonEntry func_00126460


#include "battle/xb_eft_n.h"

#define gPool ((EftAuraMgr *)gEftAuraPool)

extern void *gEftAuraTaskList;

extern void *memset(void *dst, s32 c, u32 n);
extern void EftTexSet_Load32(EftNTexSet *set, s32 *data);

extern void EftAura_UpdateLightning(s32 objId);
extern s32 BtlPool_GetCurrent(void);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern s32 BtlScene_GetCharCount(void);
extern void *BtlTask_CreateChildList(EftNTask *task, s32 count, s32 workSize);

/* Manager init: the pool header, 50 flames and 18 sparks per character, the task table, the two texture sets
   (common entries 2 and 3), the parameter file (common entry 8) and the list the aura tasks live in. */
void EftAuraMgr_Init(EftNTask *task) {
    s32 i;

    gEftAuraPool = BtlPool_Alloc(BtlPool_GetCurrent(), sizeof(EftAuraMgr));
    memset(gEftAuraPool, 0, sizeof(EftAuraMgr));
    gPool->count = BtlScene_GetCharCount();
    gPool->flameMax = gPool->count * 50;
    gPool->sparkMax = gPool->count * 18;
    gPool->flameFree = NULL;
    gPool->flameUsed = NULL;
    gPool->flameNext = 0;
    gPool->flames = BtlPool_Alloc(BtlPool_GetCurrent(), gPool->flameMax * sizeof(EftAuraFlame));
    memset(gPool->flames, 0, gPool->flameMax * sizeof(EftAuraFlame));
    gPool->sparkFree = NULL;
    gPool->sparkUsed = NULL;
    gPool->sparkNext = 0;
    gPool->sparks = BtlPool_Alloc(BtlPool_GetCurrent(), gPool->sparkMax * sizeof(EftAuraSpark));
    memset(gPool->sparks, 0, gPool->sparkMax * sizeof(EftAuraSpark));
    gPool->tasks = BtlPool_Alloc(BtlPool_GetCurrent(), gPool->count * 4);
    memset(gPool->tasks, 0, gPool->count * 4);
    gPool->grp[0].data = BtlScene_GetCommonEntry(2);
    gPool->grp[1].data = BtlScene_GetCommonEntry(3);
    for (i = 0; i < 2; i++) {
        EftTexSet_Load32(&gPool->grp[i].set, gPool->grp[i].data);
    }
    gPool->data = BtlScene_GetCommonEntry(8);
    gEftAuraPrm = (EftAuraPrm *)(gEftAuraCfg = gPool->data); /* gEftAuraPrm (0x387780) is stored first */
    for (i = 0; i < gPool->count; i++) {
        gPool->tasks[i] = NULL;
    }
    gEftAuraTaskList = BtlTask_CreateChildList(task, gPool->count, sizeof(EftAuraWork));
}

/* Manager term: frees everything the init allocated. */
void EftAuraMgr_Term(void) {
    BtlPool_Free(BtlPool_GetCurrent(), gPool->tasks);
    BtlPool_Free(BtlPool_GetCurrent(), gPool->flames);
    BtlPool_Free(BtlPool_GetCurrent(), gPool->sparks);
    BtlPool_Free(BtlPool_GetCurrent(), gEftAuraPool);
    gEftAuraPool = NULL;
}

/* Manager update: marks the texture sets stale and starts or stops each character's body lightning. */
void EftAuraMgr_Update(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        gPool->grp[i].ready = 0;
    }
    for (i = 0; i < gPool->count; i++) {
        EftAura_UpdateLightning(i);
    }
    gPool->started = 1;
}
