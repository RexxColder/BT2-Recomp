#define func_0017C280 EftAura_SetType  /* fix_targets */ /* the original uses 0x17c280 here */
#include "common.h"

/*
 * Aura entry points and the lightning joint pool, 0x17D2D8..0x17D658 (BT3 src/battle/eft_n.c, EftAura_Show ..
 * EftBolt_FreeSegs; same code apart from the BT2 aura layout, include/battle/xb_eft_n.h).
 */
#define gEftAuraCfg D_0038777C
#define gEftAuraPrm D_00387780
#define EftAura_SetType func_0017C280

#include "battle/xb_eft_n.h"

#define gPool ((EftAuraMgr *)gEftAuraPool)

/* The aura parameter file (common entry 8): only the colour tables are read here. */
typedef struct EftAuraData {
    /* 0x000 */ u8 unk0[0x510];
    /* 0x510 */ Vec4 color[9][13];     /* by aura type; each row is an EftAuraColors */
    /* 0xC60 */ Vec4 colorB[5][13];    /* parameter flags 0x5E */
} EftAuraData;

/* Colours of one aura type, 0..255 per component. */
typedef struct EftAuraColors {
    /* 0x00 */ Vec4 color;
    /* 0x10 */ Vec4 alt[4];
    /* 0x50 */ Vec4 spark[4];
    /* 0x90 */ Vec4 sparkAlt[4];
} EftAuraColors; /* size 0xD0 */

#define gData ((EftAuraData *)gEftAuraCfg)

/*
 * EftAura_ChangeType and EftAura_CommandAlt match only when their callees are DEFINED earlier in the file (with
 * prototypes only, branches come out as branch-likely / delay slots differ), as in BT3, where the whole aura module
 * is one file. EftAura_SetType (0x17C280, unmatched) and EftAura_Request / EftAura_Stop (0x17CE20, in
 * xb_17CE20.c) are compiled here between ASM_STUB_BEGIN / ASM_STUB_END: the compiler sees them, the assembler
 * skips their output. Nothing of them reaches the object.
 */
#define Vec4_Scale func_00129BB8
#define gEftAuraTaskList D_00387784
#define gEftAuraTaskClass D_00341DE0
extern void *gEftAuraTaskList;
extern void *gEftAuraTaskClass[];
extern EftNTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern const f32 D_00384A28, D_00384A2C, D_00384A30, D_00384A34, D_00384A38, D_00384A3C, D_00384A40, D_00384A44,
    D_00384A48, D_00384A4C;

ASM_STUB_BEGIN();
/* Selects the texture pair and the colours for an aura type. With any of the parameter flags 0x5E the aura uses
   two textures (pair 8, 10 or 12) and a row of the second colour table (by flag 2, 4, 8, 0x10, 0x40); otherwise
   types 8 and up use the pair 8 and the first table. */
void EftAura_SetType(EftAuraWork *aura, s32 objId, s32 type, s32 paramFlags) {
    s32 alt;
    s32 i;
    s32 j;

    aura->paramFlags = paramFlags;
    aura->flags &= ~0x80;
    if (paramFlags & 0x5E) {
        aura->flags |= 0x80;
        aura->texCount = 1;
        type = 8;
        aura->texFirst = 8;
        if (paramFlags & 0x46) {
            aura->texCount = 2;
        } else if (paramFlags & 8) {
            aura->texFirst = 10;
            aura->texCount = 2;
        } else if (paramFlags & 0x10) {
            aura->texFirst = 12;
            aura->texCount = 2;
        }
    } else if (type >= 8) {
        aura->flags |= 0x80;
        aura->texFirst = 8;
        aura->texCount = 2;
    }
    aura->unk18 = type;
    aura->colorCount = 1;
    aura->type = type;
    if (aura->flags & 0x80) {
        aura->colorCount = 2;
    }
    if (paramFlags & 2) {
        alt = 0;
    } else if (paramFlags & 4) {
        alt = 1;
    } else if (paramFlags & 8) {
        alt = 2;
    } else if (paramFlags & 0x10) {
        alt = 3;
    } else if (paramFlags & 0x40) {
        alt = 4;
    } else if (aura->flags & 0x80) {
        alt = 0;
    } else {
        alt = 0;
    }
    if (aura->flags & 0x80) {
        Vec4_Scale(&aura->colorStart, &gData->colorB[alt][0], D_00384A28);
        Vec4_Scale(&aura->colorEnd, &gData->colorB[alt][0], D_00384A2C);
        aura->colorEnd.w = 0.0f;
    } else {
        Vec4_Scale(&aura->colorStart, &gData->color[aura->type][0], D_00384A30);
        Vec4_Scale(&aura->colorEnd, &gData->color[aura->type][0], D_00384A34);
        aura->colorEnd.w = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        if (aura->flags & 0x80) {
            Vec4_Scale(&aura->colorAlt[i], &gData->colorB[alt][1 + i], D_00384A38);
            Vec4_Scale(&aura->sparkColor[i], &gData->colorB[alt][5 + i], D_00384A3C);
            Vec4_Scale(&aura->sparkColorAlt[i], &gData->colorB[alt][9 + i], D_00384A40);
        } else {
            if (aura->type < 8) {
                j = 0;
            } else {
                j = i;
            }
            Vec4_Scale(&aura->colorAlt[i], &gData->color[aura->type][1 + j], D_00384A44);
            Vec4_Scale(&aura->sparkColor[i], &gData->color[aura->type][5 + j], D_00384A48);
            Vec4_Scale(&aura->sparkColorAlt[i], &gData->color[aura->type][9 + j], D_00384A4C);
        }
    }
}

/* Creates the fighter's aura task, or restarts the aura of the existing one with the new variant (without a new
   fade-in). Returns 0 only when no task could be created. */
s32 EftAura_Request(s32 objId, s32 variant) {
    EftAuraArg arg;
    EftNTask *task;
    EftAuraWork *aura;

    if (gPool->tasks[objId] == NULL) {
        arg.objId = objId;
        arg.variant = variant;
        task = BtlTaskList_AddTail(gEftAuraTaskList, gEftAuraTaskClass, &arg);
        if (task != NULL) {
            gPool->tasks[objId] = task;
        } else {
            return 0;
        }
    } else {
        aura = gPool->tasks[objId]->work;
        aura->arg.variant = variant;
        EftAura_Start((EftAura *)aura, (s32 *)&aura->arg, 0);
    }
    return 1;
}

/* Variant 0: starts the final fade-out (the task ends with it) unless the aura is of the other variant. Other
   variants only clear flag 0x20. */
s32 EftAura_Stop(s32 objId, s32 variant) {
    EftNTask *task = gPool->tasks[objId];
    EftAuraWork *aura;

    if (task != NULL) {
        aura = task->work;
        if (!(aura->flags & 1)) {
            return 0;
        }
        if (aura->fade == 3) {
            return 0;
        }
        if (variant == 0) {
            if (!(aura->flags & 0x20)) {
                aura->fade = 3;
                aura->burst = 0;
                aura->burstTime = 0.0f;
            }
        } else {
            if (aura->flags & 0x20) {
                aura->flags &= ~0x20;
            }
        }
    }
    return 1;
}

ASM_STUB_END();


s32 EftAura_Finish(s32 objId);

/* Clears the hidden flag of the aura of fighter 0 or 1. */
void EftAura_Show(s32 objId) {
    EftNTask *task;
    EftAuraWork *aura;

    if (gEftAuraPool != NULL && objId < 2) {
        task = gPool->tasks[objId];
        if (task != NULL) {
            aura = task->work;
            if (aura->flags & 1) {
                aura->flags &= ~4;
            }
        }
    }
}

/* Sets the hidden flag: the flames keep updating but are not drawn. */
void EftAura_Hide(s32 objId) {
    EftNTask *task;
    EftAuraWork *aura;

    if (gEftAuraPool != NULL && objId < 2) {
        task = gPool->tasks[objId];
        if (task != NULL) {
            aura = task->work;
            if (aura->flags & 1) {
                aura->flags |= 4;
            }
        }
    }
}

/* Sets flag 0x40 (the update sets the same flag when the fighter's model changed, and clears it again). */
void EftAura_MarkModelNew(s32 objId) {
    EftNTask *task;
    EftAuraWork *aura;

    if (gEftAuraPool != NULL && objId < 2) {
        task = gPool->tasks[objId];
        if (task != NULL) {
            aura = task->work;
            if (aura->flags & 1) {
                aura->flags |= 0x40;
            }
        }
    }
}

/* Changes the type of the aura of fighter 0 or 1. Not void in the original (the call is not a tail call). */
s32 EftAura_ChangeType(s32 objId, s32 type, s32 paramFlags) {
    EftNTask *task;

    if (objId < 2) {
        if (gEftAuraPool != NULL && type >= 0) {
            task = gPool->tasks[objId];
            if (task != NULL) {
                EftAura_SetType(task->work, objId, type, paramFlags);
            }
        }
    }
}

/* Colour table entry of an aura type: the second table when the parameter flags have any of 0x5E. */
EftAuraColors *EftAura_GetColors(s32 type, s32 paramFlags) {
    if (gEftAuraPool == NULL) {
        return NULL;
    }
    if (type < 0) {
        return NULL;
    }
    if (!(paramFlags & 0x5E)) {
        if (type >= 9) {
            return NULL;
        }
        return (EftAuraColors *)gData->color[type];
    }
    if (type >= 5) {
        return NULL;
    }
    return (EftAuraColors *)gData->colorB[type];
}

/* Sets the finished flag: the task dies on its next update. */
s32 EftAura_Finish(s32 objId) {
    EftNTask *task = gPool->tasks[objId];

    if (task != NULL) {
        ((EftAuraWork *)task->work)->flags |= 2;
    }
    return 1;
}

/* A second dispatcher, for the variant-1 aura: 0 request, 1 stop, 2 finish. */
s32 EftAura_CommandAlt(s32 objId, s32 cmd) {
    switch (cmd) {
    case 0:
        EftAura_Request(objId, 1);
        break;
    case 1:
        EftAura_Stop(objId, cmd);
        break;
    case 2:
        EftAura_Finish(objId);
        break;
    }
    return 1;
}

/* Takes up to `count` free joints from the pool (searching once around the ring from the last position) and chains
   them into the bolt. */
s32 EftBolt_AllocSegs(EftBolt *bolt, s32 count) {
    EftBoltSeg *prev = NULL;
    s32 first = 1;
    s32 tries;
    s32 got = 0;
    s32 idx;
    EftBoltSeg *seg;

    idx = gEftBoltPool->segNext;
    for (tries = 0; tries < gEftBoltPool->segMax; tries++) {
        seg = (EftBoltSeg *)(idx * sizeof(EftBoltSeg) + (u32)gEftBoltPool->segs);
        if (seg->flags == 0) {
            seg->next = NULL;
            if (first) {
                bolt->head = seg;
                first = 0;
            } else {
                prev->next = seg;
            }
            prev = seg;
            gEftBoltPool->segNext = idx + 1;
            if (!(gEftBoltPool->segNext < gEftBoltPool->segMax)) {
                gEftBoltPool->segNext = 0;
            }
            got++;
            if (got >= count) {
                break;
            }
        }
        idx++;
        if (idx >= gEftBoltPool->segMax) {
            idx = 0;
        }
    }
    bolt->count = got;
    bolt->shown = 0;
    return 1;
}

/* Returns the bolt's joints to the pool. */
void EftBolt_FreeSegs(EftBolt *bolt) {
    EftBoltSeg *seg;
    EftBoltSeg *next;

    if (bolt->head != NULL) {
        seg = bolt->head;
        do {
            next = seg->next;
            seg->flags = 0;
            seg = next;
        } while (next != NULL);
    }
    bolt->head = NULL;
}
