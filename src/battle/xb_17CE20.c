#include "common.h"

/*
 * Aura entry points, 0x17CE20..0x17D218 (BT3 src/battle/eft_n.c, EftAura_Request..EftAura_FadeOut; same code
 * apart from the BT2 aura work layout, include/battle/xb_eft_n.h).
 * The callers are the fighter effect layer (EftAura_Command at 0x17D218, which dispatches to all of these).
 */
#define gEftAuraCfg D_0038777C
#define gEftAuraPrm D_00387780
#define gEftAuraTaskList D_00387784
#define gEftAuraTaskClass D_00341DE0

#include "battle/xb_eft_n.h"

#define gPool ((EftAuraMgr *)gEftAuraPool)

extern void *gEftAuraTaskList;
extern void *gEftAuraTaskClass[];
extern EftNTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);

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

/* Ends the aura at once: its task dies on its next update. */
s32 EftAura_Kill(s32 objId) {
    EftNTask *task = gPool->tasks[objId];
    EftAuraWork *aura;

    if (task != NULL) {
        aura = task->work;
        if (!(aura->flags & 1)) {
            return 0;
        }
        aura->flags = 2;
    }
    return 1;
}

/* Sets the aura strength (the fighter's ki ratio). */
void EftAura_SetLevel(s32 objId, f32 level) {
    EftNTask *task;

    if (gEftAuraPool != NULL) {
        task = gPool->tasks[objId];
        if (task != NULL) {
            ((EftAuraWork *)task->work)->level = level;
        }
    }
}

/* 1 when the fighter has an active aura that is not fully faded out. */
s32 EftAura_IsVisible(s32 objId) {
    s32 ret = 0;
    EftNTask *task;
    EftAuraWork *aura;

    if (gEftAuraPool == NULL) {
        return 0;
    }
    task = gPool->tasks[objId];
    if (task != NULL) {
        aura = task->work;
        if (aura->flags & 1) {
            if (!(aura->alpha <= 0.0f)) {
                ret = 1;
            }
        }
    }
    return ret;
}

/* 1 when the fighter's visible aura is in the rising phase of a burst. */
s32 EftAura_IsBurstRising(s32 objId) {
    s32 ret = 0;
    EftNTask *task;
    EftAuraWork *aura;

    if (gEftAuraPool == NULL) {
        return 0;
    }
    task = gPool->tasks[objId];
    if (task != NULL) {
        aura = task->work;
        if (aura->flags & 1) {
            if (!(aura->alpha <= 0.0f)) {
                ret = aura->burst == 1;
            }
        }
    }
    return ret;
}

/* Starts a burst (burst state 1). */
s32 EftAura_StartBurst(s32 objId) {
    EftNTask *task = gPool->tasks[objId];
    EftAuraWork *aura;

    if (task != NULL) {
        aura = task->work;
        if (!(aura->flags & 1)) {
            return 0;
        }
        aura->burstTime = 0.0f;
        aura->burst = 1;
    }
    return 1;
}

/* Ends a burst (burst state 4). */
s32 EftAura_EndBurst(s32 objId) {
    EftNTask *task = gPool->tasks[objId];
    EftAuraWork *aura;

    if (task != NULL) {
        aura = task->work;
        if (!(aura->flags & 1)) {
            return 0;
        }
        aura->burstTime = 0.0f;
        aura->burst = 4;
    }
    return 1;
}

extern const f32 D_00384A5C; /* 1.2 (.lit4) */

/* Jumps to the peak of a burst (state 2, full burst level, flame life x 1.2). */
s32 EftAura_PeakBurst(s32 objId) {
    EftNTask *task = gPool->tasks[objId];
    EftAuraWork *aura;

    if (task != NULL) {
        aura = task->work;
        if (!(aura->flags & 1)) {
            return 0;
        }
        aura->lifeScale = D_00384A5C;
        aura->burstLevel = 1.0f;
        aura->burstTime = 0.0f;
        aura->burst = 2;
    }
    return 1;
}

/* Starts a fade-in, unless the final fade-out is running. */
s32 EftAura_FadeIn(s32 objId) {
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
        aura->fade = 1;
    }
    return 1;
}

/* Starts a fade-out that keeps the task, unless the final fade-out is running. */
s32 EftAura_FadeOut(s32 objId) {
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
        aura->fade = 2;
    }
    return 1;
}
