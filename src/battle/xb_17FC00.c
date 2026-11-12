#include "common.h"

/*
 * Body lightning task, 0x17FC00..0x17FFB8 (BT3 src/battle/eft_o.c, EftBolt_UpdateTex .. EftBoltTask_Update; the
 * same code, apart from the battle work being read through a pointer in BT2). 0x17FFB8 (EftBoltTask_PostUpdate,
 * empty) is src/auto/; EftBoltTask_Reset is xb_17FFC0.c.
 */
#define gBattleWorkB D_003876A0
#define BtlCharApi_ObjGetParamFlags0 func_00207F88
#define BtlCharApi_GetHeight func_00207EE8
#define BtlCharApi_IsModelNew func_0020A5C0
#define BtlCharApi_IsHidden func_0020A508
#define BtlCharApi_ObjTestFlagBit21 func_0020A490
#define BtlScene_IsCharInView func_00209888
#define EftBolt_Spawn func_0017F370
#define EftBolt_UpdateAll func_0017EBE8
#define EftBolt_UpdateFlashes func_0017EFF0
#define EftBolt_DrawAll func_0017EDD0

#include "battle/eft_o.h"

typedef struct EftOBattleWorkB {
    /* 0x000 */ u8 unk0[0x4D8];
    /* 0x4D8 */ u64 flags; /* 0x100 = paused */
} EftOBattleWorkB;

extern EftOBattleWorkB *gBattleWorkB;
extern const f32 D_00384B54; /* 19.35 */
extern const f32 D_00384B58; /* 0.3 */

extern void *memset(void *dst, s32 c, u32 n);
extern u64 EftVram_AddImage(void *set, s32 a, s32 b);
extern u64 EftVram_AddClut(void *entry);
extern void BtlTask_SetDead(EftOTask *task);
extern s32 BtlCharApi_ObjGetParamFlags0(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_IsHidden(s32 objId);
extern s32 BtlCharApi_IsModelNew(s32 objId);
extern s32 BtlCharApi_ObjTestFlagBit21(s32 objId);
extern s32 BtlScene_IsCharInView(s32 objId);
extern void EftBolt_FreeSegs(EftOBolt *bolt);
extern void EftBolt_UpdateAll(EftOBoltWork *work, s32 objId);
extern void EftBolt_DrawAll(EftOBoltWork *work, f32 alpha);
extern void EftBolt_UpdateFlashes(EftOBoltWork *work, s32 objId);
extern void EftBolt_DrawFlashes(EftOBoltWork *work, f32 alpha);
extern void EftBolt_Spawn(EftOBoltWork *work, s32 objId);

/* Advances the two shared textures once per frame and gives the work block this frame's TEX0. */
/* (`one` is needed: with the literal 1 in both stores the first branch is scheduled differently.) */
void EftBolt_UpdateTex(EftOBoltWork *w) {
    EftOTexSet *set = &gEftBoltPool->tex[0].set;
    EftOBoltTex *t = &gEftBoltPool->tex[0];
    u64 frame;

    if (!t->ready) {
        u64 base;
        s32 i;
        s32 one;

        t->tex0 = EftVram_AddImage(set, 1, 0);
        frame = EftVram_AddClut(set);
        one = 1;
        w->tex0 = t->tex0 | (frame << 37);
        t->flags = one;
        t->ready = one;
        t->frame = frame;
        set = &gEftBoltPool->tex[1].set;
        base = EftVram_AddImage(set, 1, 0);
        for (i = 0; i < set->count; i++) {
            set->entry[i].tex0 = base | ((u64)EftVram_AddClut(&set->entry[i]) << 37);
        }
    } else {
        if (!(t->flags & 1)) {
            frame = EftVram_AddClut(set);
        } else {
            frame = t->frame;
        }
        w->tex0 = t->tex0 | (frame << 37);
    }
}

/* Reads what the task needs from the fighter: parameter flags and body scale. */
void EftBolt_ReadChar(EftOBoltWork *w, s32 objId) {
    w->paramFlags = BtlCharApi_ObjGetParamFlags0(objId);
    w->scale = BtlCharApi_GetHeight(objId) / D_00384B54;
}

/* Init callback of the per-fighter task. */
void EftBoltTask_Init(EftOTask *task, s32 *arg) {
    EftOBoltWork *w = task->work;

    memset(w, 0, sizeof(EftOBoltWork));
    w->objId = *arg;
    w->flags |= 1;
    EftBolt_ReadChar(w, *arg);
}

/* Term callback: frees the first bolt's joints and clears the fighter's entry. */
void EftBoltTask_Term(EftOTask *task) {
    EftOBoltWork *w = task->work;
    EftOBolt *bolt = w->a;
    s32 *objId = &w->objId;

    EftBolt_FreeSegs(bolt);
    bolt->active = 0;
    gEftBoltPool->tasks[*objId] = NULL;
}

/* Update callback: bolts and flashes unless paused; once stopped, dies when the last bolt and flash are gone. */
void EftBoltTask_Update(EftOTask *task) {
    s32 busy = 0;
    EftOBoltWork *w = task->work;
    s32 *objId = &w->objId;
    s32 i;

    if (BtlCharApi_IsModelNew(*objId)) {
        w->flags |= 8;
    }
    if (w->flags & 8) {
        EftBolt_ReadChar(w, *objId);
        w->flags &= ~8;
    }
    if (!(gBattleWorkB->flags & 0x100)) {
        if (!(w->flags & 2)) {
            EftBolt_Spawn(w, *objId);
        }
        EftBolt_UpdateAll(w, *objId);
        EftBolt_UpdateFlashes(w, *objId);
        if (w->flags & 2) {
            for (i = 0; i < 10; i++) {
                if (w->a[i].active) {
                    busy = 1;
                    break;
                }
            }
            for (i = 0; i < 20; i++) {
                if (w->b[i].active) {
                    busy = 1;
                    break;
                }
            }
            if (!busy) {
                w->flags |= 4;
            }
        }
    }
    if (w->flags & 4) {
        BtlTask_SetDead(task);
    } else {
        EftBolt_UpdateTex(w);
    }
}

