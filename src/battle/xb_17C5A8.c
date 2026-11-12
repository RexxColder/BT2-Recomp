#include "common.h"

/*
 * Aura task, 0x17C5A8..0x17C9B0 (BT3 src/battle/eft_n.c, EftAura_Setup .. EftAuraTask_Update).
 * Same code as BT3 apart from the BT2 aura work layout (include/battle/xb_eft_n.h) and EftAura_SetType, which in
 * BT2 also picks the two-texture variant and the second colour row from the character's parameter flags.
 */
#define gEftAuraCfg D_0038777C
#define gEftAuraPrm D_00387780
#define gBattleWorkB D_003876A0
#define Vec4_Scale func_00129BB8
#define Vec4_Copy func_00129C28
#define BtlCharApi_ObjGetParamFlags0 func_00207F88
#define BtlCharApi_GetAuraType func_00207FC0
#define BtlCharApi_GetHeight func_00207EE8
#define BtlCharApi_GetNodePos func_00208DE8
#define BtlCharApi_IsModelNew func_0020A5C0

#include "battle/xb_eft_n.h"

#define gPool ((EftAuraMgr *)gEftAuraPool)

/* The aura parameter file (common entry 8): the parts this file reads. */
typedef struct EftAuraDataPart {
    /* 0x0 */ s32 node;      /* model node of the part */
    /* 0x4 */ s32 nodeEnd;   /* its second node */
    /* 0x8 */ s32 nodeRef;   /* node the flame leans away from */
} EftAuraDataPart;

typedef struct EftAuraDataSpark {
    /* 0x0 */ s32 unk0;
    /* 0x4 */ s32 node;      /* model node the emitter sits on */
} EftAuraDataSpark;

typedef struct EftAuraData {
    /* 0x000 */ u8 unk0[0x410];
    /* 0x410 */ EftAuraDataPart part[EFT_AURA_PARTS];
    /* 0x488 */ s32 fadeNode[6];
    /* 0x4A0 */ EftAuraDataSpark spark[EFT_AURA_SPARKS];
    /* 0x500 */ u8 unk500[0x10];
    /* 0x510 */ Vec4 color[9][13];     /* by aura type */
    /* 0xC60 */ Vec4 colorB[5][13];    /* flag 0x80: row from the parameter flags */
} EftAuraData;

#define gData ((EftAuraData *)gEftAuraCfg)

/* The battle work, reached through a pointer in BT2 (BT3: Battle_GetWork()). */
typedef struct EftNBattleWork {
    /* 0x000 */ u8 unk0[0x4D8];
    /* 0x4D8 */ u64 flags; /* 0x100 = paused */
} EftNBattleWork;

extern EftNBattleWork *gBattleWorkB;

/* 1 / 255 (.lit4 of the original object, one word per use; all ten checked: 0x3B808080). */
extern const f32 D_00384A28, D_00384A2C, D_00384A30, D_00384A34, D_00384A38, D_00384A3C, D_00384A40, D_00384A44,
    D_00384A48, D_00384A4C;
extern const f32 D_00384A50; /* 19.35 */
extern const f32 D_00384A54; /* 0.7 */

extern void *memset(void *dst, s32 c, u32 n);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void BtlTask_SetDead(EftNTask *task);
extern u64 EftVram_AddTex(EftNTexEntry *tex, s32 a, s32 b);
extern u64 EftVram_AddImage(EftNTexEntry *tex, s32 a, s32 b);
extern u64 EftVram_AddClut(EftNTexEntry *tex);
extern void EftBolt_Enable(s32 objId);
extern void EftBolt_Disable(s32 objId);
extern s32 BtlCharApi_ObjGetParamFlags0(s32 objId);
extern s32 BtlCharApi_GetAuraType(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, Vec4 *out, s32 node); /* BT2 argument order */
extern s32 BtlCharApi_IsModelNew(s32 objId);

extern void EftAura_SetType(EftAuraWork *aura, s32 objId, s32 type, s32 paramFlags);
extern void EftAura_UpdateTextures(EftAuraWork *aura);

/* Reads the fighter's aura type and height: called at creation and again every frame. */
void EftAura_Setup(EftAuraWork *aura, s32 objId) {
    s32 flags = BtlCharApi_ObjGetParamFlags0(objId);

    EftAura_SetType(aura, objId, BtlCharApi_GetAuraType(objId), flags);
    aura->scale = BtlCharApi_GetHeight(objId) / D_00384A50;
    if (aura->scale < D_00384A54) {
        aura->scale = D_00384A54;
    }
}

/* Task init: clears the work, keeps the argument block and starts the aura with a fade-in. */
void EftAuraTask_Init(EftNTask *task, EftAuraArg *arg) {
    EftAuraWork *aura = task->work;

    memset(aura, 0, sizeof(EftAuraWork));
    aura->arg = *arg;
    aura->level = 1.0f;
    aura->alpha = 0.0f;
    aura->flags |= 8;
    aura->partsStarted = 0;
    aura->flameCount = 0;
    EftAura_Setup(aura, arg->objId);
    EftAura_Start((EftAura *)aura, (s32 *)arg, 1);
}

/* Task term: returns the fighter's flames and sparks to the pools and clears its entry of the task table. */
void EftAuraTask_Term(EftNTask *task) {
    EftAuraWork *aura = task->work;
    s32 *objId;

    aura->flags = 0;
    objId = &aura->arg.objId;
    EftAura_FreeFlames(*objId);
    EftAura_FreeSparks(*objId);
    gPool->tasks[*objId] = NULL;
}

/* Task update: samples the fighter's model nodes, steps the state machines and particles (not while paused), and
   kills the task once the aura has finished. */
void EftAuraTask_Update(EftNTask *task) {
    EftAuraWork *aura = task->work;
    s32 *objId = &aura->arg.objId;
    s32 i;

    if (BtlCharApi_IsModelNew(*objId)) {
        aura->flags |= 0x40;
    }
    EftAura_Setup(aura, *objId);
    aura->flags &= ~0x40;
    if (!(gBattleWorkB->flags & 0x100)) {
        for (i = 0; i < EFT_AURA_SPARKS; i++) {
            BtlCharApi_GetNodePos(*objId, &aura->sparkPos[i], gData->spark[i].node);
        }
        BtlCharApi_GetNodePos(*objId, &aura->pos, 3);
        BtlCharApi_GetNodePos(*objId, &aura->unk310, 0x30);
        BtlCharApi_GetNodePos(*objId, &aura->axis, 0x11);
        for (i = 0; i < EFT_AURA_PARTS; i++) {
            BtlCharApi_GetNodePos(*objId, &aura->part[i], gData->part[i].node);
        }
        for (i = 0; i < EFT_AURA_PARTS; i++) {
            BtlCharApi_GetNodePos(*objId, &aura->partEnd[i], gData->part[i].nodeEnd);
        }
        for (i = 0; i < EFT_AURA_PARTS; i++) {
            BtlCharApi_GetNodePos(*objId, &aura->partRef[i], gData->part[i].nodeRef);
        }
        if (aura->flags & 8) {
            Vec4_Copy(&aura->prevPos, &aura->pos);
            for (i = 0; i < EFT_AURA_PARTS; i++) {
                Vec4_Copy(&aura->partPrev[i], &aura->part[i]);
            }
            aura->flags &= ~8;
        }
        EftAura_UpdateState((EftAura *)aura, *objId);
        EftAura_UpdateSparks((EftAura *)aura, *objId, &aura->sparkState);
        Vec4_Copy(&aura->prevPos, &aura->pos);
        for (i = 0; i < EFT_AURA_PARTS; i++) {
            Vec4_Copy(&aura->partPrev[i], &aura->part[i]);
        }
        aura->frame++;
    }
    if (aura->flags & 2) {
        BtlTask_SetDead(task);
    } else {
        EftAura_UpdateTextures(aura);
    }
}
