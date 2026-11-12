#include "common.h"

/*
 * Aura textures and lightning switch, 0x17C0D8..0x17C280 (BT3 src/battle/eft_n.c). The aura task continues in
 * xb_17C5A8.c after EftAura_SetType (0x17C280, not matched: see the report).
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

/* GS TEX0 values for this frame: the aura's flame sheet(s), and once per frame every entry of the spark set. */
void EftAura_UpdateTextures(EftAuraWork *aura) {
    EftNTexSet *set = &gPool->grp[0].set;
    s32 *ready;
    u64 base;
    s32 i;

    if (aura->flags & 0x80) {
        base = EftVram_AddImage(&set->entry[8], 1, 0);
        for (i = aura->texFirst; i < aura->texFirst + aura->texCount; i++) {
            ((EftAuraWork *)((u8 *)aura + 8))->tex[i - aura->texFirst] = base | ((u64)EftVram_AddClut(&set->entry[i]) << 37);
        }
    } else {
        aura->tex[0] = EftVram_AddImage(&set->entry[0], 1, 0);
        aura->tex[0] |= (u64)EftVram_AddClut(&set->entry[aura->type]) << 37;
    }
    ready = &gPool->grp[1].ready;
    if (!*ready) {
        set = &gPool->grp[1].set;
        for (i = 0; i < set->count; i++) {
            set->entry[i].tex0 = EftVram_AddTex(&set->entry[i], 1, 0);
        }
        *ready = 1;
    }
}

/* Starts the fighter's body lightning when its character parameter flags have bit 4 or 8, else stops it. */
void EftAura_UpdateLightning(s32 objId) {
    if (BtlCharApi_ObjGetParamFlags0(objId) & 0xC) {
        EftBolt_Enable(objId);
    } else {
        EftBolt_Disable(objId);
    }
}

