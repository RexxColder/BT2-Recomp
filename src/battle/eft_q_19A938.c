#include "common.h"
#include "battle/eft_q.h"
#include "sys/gfx_ot.h"

/*
 * Effect tasks, 0x170A50..0x174A70. See include/battle/eft_q.h.
 */

typedef struct EftQBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 = paused */
} EftQBattleWork;

/* The view being drawn (include/battle/btl_cam.h). */
typedef struct EftQView {
    /* 0x000 */ u8 unk0[0x140];
    /* 0x140 */ Mtx44 world2screen;
    /* 0x180 */ u8 unk180[0xA0];
    /* 0x220 */ Vec4 pos;
} EftQView;

extern EftQView *gBtlCamView;

extern void *memset(void *dst, s32 c, u32 n);
extern void Vec4_Set(Vec4 *dst, f32 x, f32 y, f32 z, f32 w);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vu0Cur_Push(void);            /* VU0 matrix stack push */
extern void Vu0Cur_LoadMtx(Mtx44 *m);        /* load the matrix */
extern void Vu0Cur_Pop(void);            /* pop */
extern void Vec4_Lerp(Vec4 *dst, Vec4 *a, Vec4 *b, f32 t); /* dst = a * t + b * (1 - t) */
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Vec3_ScaleAdd(Vec4 *dst, Vec4 *dir, f32 len, Vec4 *from);     /* dst = from + dir * len */
extern f32 Vec3_Dist(Vec4 *a, Vec4 *b);                               /* distance */
extern s32 Vu0Cur_ProjectPoints(EftQScr *out, Vec4 *pos, s32 count);             /* projects count points */
extern void ClipVtx_Set(EftQVert *out, Vec4 *pos, Vec4 *uv, Vec4 *col); /* builds one vertex */
extern void EftGfx_DrawPolyAvgZ(EftQVert *verts, s32 arg1, s32 arg2, s32 arg3, s32 flip, u64 tex, s32 zOfs);
extern void EftMath_MtxFromDir(Mtx44 *out, Vec4 *dir, f32 angle);
extern void Mtx_ProjectPoints(EftQScr *out, Mtx44 *m, Vec4 *pos, s32 count);  /* projects count points */
extern s32 IVec4_InGsRange4(EftQScr *a, EftQScr *b, EftQScr *c, EftQScr *d);  /* 1 when the quad is off screen */

extern EftQBattleWork *Battle_GetWork(void);
extern s32 Battle_IsSplitScreen(void);
extern s32 BtlPool_GetCurrent(void);
extern void BtlPool_SetCurrent(s32 slot);
extern void BtlPool_Reset(s32 slot);
extern void *BtlPool_Alloc(s32 slot, s32 size);
extern void BtlPool_Free(s32 slot, void *ptr);
extern s32 BtlScene_GetCharCount(void);
extern s32 *BtlScene_GetCommonEntry(s32 idx);
extern s32 *BtlScene_GetCharPackEntry(s32 side, s32 idx);
extern s32 BtlScene_TestCharPackBit(s32 side, s32 bit);
extern s32 BtlScene_IsCharInView(s32 objId);
extern s32 BtlScene_IsEffectStopped(s32 objId, s32 kind);
extern s32 BtlScene_IsEffectHidden(s32 objId, s32 kind);
extern void BtlScene_Reset(s32 mode);
extern void *BtlTask_CreateChildList(EftQTask *task, s32 count, s32 workSize);
extern EftQTask *BtlTaskList_AddTail(void *list, void *cls, void *arg);
extern void BtlTask_Kill(EftQTask *task);
extern void BtlTask_SetDead(EftQTask *task);              /* marks the task dead */
extern void BtlTask_SetOwnerTag(EftQTask *task, s32 flag);    /* ors bits into the task's class flags */
extern EftQTask *BtlTask_GetParent(EftQTask *task);         /* parent task */
extern u64 EftVram_AddTex(EftQTex *tex, s32 a, s32 b);   /* GS TEX0 of a texture for this frame */
extern u64 EftVram_AddImage(EftQTex *tex, s32 a, s32 b);   /* the same for an image with a separate palette */
extern u64 EftVram_AddClut(EftQTex *tex);                 /* palette address of a texture */
extern void EftTexSet_Load32(EftQTexSet *set, s32 *entry); /* builds a texture set from a pack entry */

extern s32 BtlCharApi_GetChara(s32 objId);
extern f32 BtlCharApi_GetHeight(s32 objId);
extern s32 BtlCharApi_ObjGetParamFlags0(s32 objId);
extern s32 BtlCharApi_GetAuraType(s32 objId);
extern s32 BtlCharApi_HasKiBlastType2(s32 objId);
extern s32 BtlCharApi_HasKiBlastType3(s32 objId);
extern void BtlCharApi_GetNodePos(s32 objId, s32 node, Vec4 *out);
extern void BtlCharApi_GetNodeMtx(s32 objId, s32 node, Mtx44 *out);
extern s32 BtlCharApi_IsHidden(s32 objId);
extern s32 BtlCharApi_IsModelNew(s32 objId);
extern s32 BtlCharApi_ObjTestFlagBit21(s32 objId);
extern s32 BtlCharApi_IsFlag8Action104(s32 objId);
extern s32 BtlCharApi_GetMemberUnk60(s32 objId);
extern s32 BtlCharApi_TestFlag2B(s32 objId);
extern s32 BtlCharApi_IsInRushSequence(s32 objId);
extern s32 BtlCharApi_GetRushFinishPhase(s32 objId);

/* ---- 1. power-up glow: the tasks and manager of the module whose particles are in eft_p_b.c (0x16DCA0..) -- */

extern EftGlowMgr *gEftGlow;      /* 0x2FEA38 */
extern EftGlowCfg *gEftGlowCfg;   /* 0x2FEA3C */
extern EftGlowCfg *gEftGlowCfg2;  /* 0x2FEA40: the same pointer */
extern void *gEftGlowList;        /* 0x2FEA44: the manager's child list */
extern u8 gEftGlowClass[0x18];    /* 0x2C3B68 */

/* eft_p_b.c */
extern void EftGlow_BuildTables(void);                           /* builds the shape tables, links the particle pool */
extern void EftGlow_Begin(EftGlow *w, s32 *arg);                 /* starts the glow (arg[0] = object id) */
extern void EftGlow_Step(EftGlow *w, s32 objId);
extern void EftGlow_FreeParts(s32 objId);                        /* frees the fighter's glow particles */
extern void EftGlow_StepParts(EftGlow *w, s32 objId);
extern void EftGlow_DrawParts(EftGlow *w, s32 objId, f32 alpha);

/* A colour stored as bytes 0..255 to 0..1. The original has one copy of the constant per call site, which a call
 * through an inline function reproduces (a literal argument of a direct call is shared between neighbouring calls
 * and ends up in a saved register). */
static inline void EftGlow_ColorFromBytes(Vec4 *dst, Vec4 *src);

/* The two base colours of a glow, from the row of its variant. Inline in the original: the flag arrives as a byte
 * (the caller's test and this one are both kept), the constants are not shared, and `colorB.w = 0` is written in
 * both arms (the compiler merges the two tails into one call). */
static inline void EftGlow_SetBaseColors(EftGlow *w, u8 textured, s32 row);

/* Renews the GS texture words the glow draws with, and once per frame those of the second texture set. */
void EftGlow_UpdateTextures(EftGlow *w);

/* Selects the glow's variant and colours from the fighter's aura type. Types 8..10 are the textured variant; they
 * are all turned into type 8 first, so the cases 9 and 10 below never run and `row` stays 0. */
void EftGlow_SetType(EftGlow *w, s32 objId, s32 type, s32 paramFlags);

/* Reads the fighter's aura type, parameter flags and height into the glow. */
void EftGlow_Setup(EftGlow *w, s32 objId);

/* Init callback of the glow task: arg[0] is the fighter's object id. */
void EftGlowTask_Init(EftQTask *task, s32 *arg);

/* Term callback: frees the particles and the manager's task slot. */
void EftGlowTask_Term(EftQTask *task);

/* Update callback: re-reads the fighter's type every frame, steps the particles unless paused. */
void EftGlowTask_Update(EftQTask *task);

/* Post-update callback: only fetches the battle work. */
void EftGlowTask_PostUpdate(EftQTask *task);

/* Reset callback: kills the task. */
void EftGlowTask_Reset(EftQTask *task);

/* Draw callback: skipped for a hidden fighter; 30% alpha when the camera is on a fighter with object flag bit 21. */
void EftGlowTask_Draw(EftQTask *task);

/* Manager init: the 0x700-byte work, 70 particles per character, the two texture sets and the settings. */
void EftGlowMgr_Init(EftQTask *task);

/* Manager term. */
void EftGlowMgr_Term(EftQTask *task);

/* Manager update: the textures have to be renewed this frame. */
void EftGlowMgr_Update(EftQTask *task);

/* Starts the fighter's glow, or restarts the one it has. Returns 1 unless no task could be made. */
s32 EftGlow_Start(s32 objId);

/* Starts the fade-out of the fighter's glow. Returns 0 when it is not active or already fading. */
s32 EftGlow_FadeOut(s32 objId);

/* Removes the fighter's glow at its next update. */
s32 EftGlow_Kill(s32 objId);

/* Entry point of the fighter effect layer (requests 4 and 5): 0 start, 1 fade out, 2 remove. */
s32 EftGlow_Request(s32 objId, s32 cmd);

/* 1 while the fighter has an active glow. */
s32 EftGlow_IsActive(s32 objId);

/* Changes the type of a running glow (characters 0 and 1 only). No caller. */
void EftGlow_ChangeType(s32 objId, s32 type, s32 paramFlags);

/* The colour row of an aura type. No caller. */
Vec4 *EftGlow_GetColors(s32 type, s32 paramFlags) {
    if (gEftGlow == NULL) {
        return NULL;
    }
    if (type < 0) {
        return NULL;
    }
    if (!(paramFlags & 0x5E)) {
        if (type >= 9) {
            return NULL;
        }
        return &gEftGlowCfg->color[type * EFT_GLOW_ROW];
    }
    if (type >= 5) {
        return NULL;
    }
    return &gEftGlowCfg->colorTex[type * EFT_GLOW_ROW];
}

/* ---- 2. rush-finish burst: fighter effect requests 0x28 (start), 0x29 (second stage), 0x2A (end) --------- */

extern void EftEmit_LoadSet(void *arg, EftQEmitSet *set, s32 a2, s32 *pack, s32 a4, s32 a5);
extern void EftEmit_FreeSet(EftQEmitSet *set);
extern void EftEmit_BeginFrame(EftQEmitSet *set);
extern s32 EftEmit_GetEndFrames(EftQEmitSet *set);
extern void EftEmit_InitState(EftQEmitSet *set, EftQEmitState *state);
extern void EftEmit_TermState(EftQEmitSet *set, EftQEmitState *state);
extern s32 EftEmit_GetFlagsFromMask(EftQEmitSet *set, EftQEmitState *state, s32 objId, s32 group, s32 sub, s32 end,
                                    s32 fast, s32 mask);
extern void EftEmit_Spawn(EftQEmitSet *set, EftQEmitState *state, void *nodes, Vec4 *pos, Vec4 *dir, s32 objId, s32 node,
                          s32 arg7, s32 group, s32 sub, s32 flags, f32 scale);
extern void EftEmit_KillAll(EftQEmitSet *set, EftQEmitState *state);
extern s32 EftEmit_UpdateAlive(EftQEmitSet *set, EftQEmitState *state);
extern void EftEmit_SetNode(void *nodes, s32 slot, s32 node, Vec4 *pos);
extern void EftEmit_RefreshFixedNodes(s32 objId, void *nodes);

extern void EftCharSlot_Set2(s32 objId, EftQTask *task);   /* per-fighter task slot of this effect: set */
extern void EftCharSlot_Clear2(s32 objId);                   /* clear */
extern EftQTask *EftCharSlot_Get2(s32 objId);              /* get */

extern u8 gEftRushBurstClass[0x18]; /* 0x2C3B98 */

void EftChar_SetList(s32 objId, s32 kind, void *list);
void *EftChar_GetList(s32 objId, s32 kind);

/* Steps the emitters of the set and spawns their particles at the node, along the direction. */
void EftRushBurst_Emit(s32 objId, EftQTask *task, EftQEmitSet *set);

/* Init callback: copies the argument, places the burst at the fighter's node and starts the first stage. */
void EftRushBurst_Init(EftQTask *task, EftRushBurstArg *arg);

/* Term callback: releases the emitter state and the fighter's slot. */
void EftRushBurst_Term(EftQTask *task);

/* Update callback: follows the fighter's node, spawns the particles, counts down once the end was asked for. */
void EftRushBurst_Update(EftQTask *task);

/* Reset callback: destroys the particles once and kills the task. */
void EftRushBurst_Reset(EftQTask *task);

/* Post-update callback (from the second frame on): records whether a particle is alive, clears the phase mask. */
void EftRushBurst_PostUpdate(EftQTask *task);

/* Draw callback: nothing. */
void EftRushBurst_Draw(EftQTask *task);

/* Manager init (per-character kind 5): loads the emitter set from entry 7 of the character's pack, makes room
 * for four bursts and registers the list. arg = {character, kind}. */
void EftRushBurstMgr_Init(EftQTask *task, s32 *arg);

/* Manager term: releases the set and its memory. */
void EftRushBurstMgr_Term(EftQTask *task);

/* Manager update: steps the set. */
void EftRushBurstMgr_Update(EftQTask *task);

/* Fighter effect request 0x28: starts the burst and records its task in the fighter's slot. */
void EftRushBurst_Start(EftRushBurstArg *arg);

/* Fighter effect request 0x29: asks the fighter's burst for its second stage. Returns 1 when one is running. */
s32 EftRushBurst_Stage2(s32 objId);

/* Fighter effect request 0x2A: asks the fighter's burst to end. Returns 1 when one is running. */
s32 EftRushBurst_Stop(s32 objId);

/* Nothing. No caller. */
void EftRushBurst_Nop(void);

/* ---- 3. per-character effect root = scene layer 2 (btl_scene.c creates it from class 0x2C3BB0) ----------- */

extern EftCharRoot *gEftChar;        /* 0x2FEA48 */
extern u8 gEftCharClass[0x18];       /* 0x2C3BC8 */
extern void *gEftCharKindClass[11];  /* 0x2C3BE0: manager class of each kind */
extern u8 gEftKiBombMgrClass[0x18];          /* manager class used for kind 2 when the fighter has a type 3 ki blast */
extern u8 D_002C3E00[0x18];          /* manager class used for kind 1 when the fighter has a type 2 ki blast */

void EftChar_SetPool(s32 chr);
void EftChar_ResetPool(s32 chr);
void EftChar_CreateKind(s32 chr, s32 kind, s32 mode);

/* Root init: selects pool 6, makes the root's work and one task per character. */
void EftCharRoot_Init(EftQTask *task);

/* Root term: frees its work and empties pools 6, 7 and 8. */
void EftCharRoot_Term(EftQTask *task);

/* Root update: nothing. */
void EftCharRoot_Update(EftQTask *task);

/* Character task init: selects the character's pool and creates the manager of every kind the character's pack
 * has. A fighter with a type 2 / type 3 ki blast gets kind 1 / 2 with another class, whatever the pack says. */
void EftChar_Init(EftQTask *task, s32 chr);

/* Character task term: forgets the kind lists and empties the character's pool. */
void EftChar_Term(EftQTask *task);

/* Character task update: nothing. */
void EftChar_Update(EftQTask *task);

/* Makes the character's pool (7 for character 0, 8 for the others) the current one. */
void EftChar_SetPool(s32 chr);

/* Empties the character's pool. */
void EftChar_ResetPool(s32 chr);

/* Creates the manager task of one kind for a character; its init gets {character, kind}. */
void EftChar_CreateKind(s32 chr, s32 kind, s32 mode);

/* Removes a character's effects (BtlScene_FreeCharLayer2, when the character is streamed out): resets the scene
 * tasks of that character and kills its task. */
void EftChar_Kill(s32 chr);

/* Creates a character's task again (BtlScene_CreateCharLayer2, when the character is streamed in). */
void EftChar_Create(s32 chr);

/* A kind's manager registers the list its tasks go into. */
void EftChar_SetList(s32 chr, s32 kind, void *list);

/* The list of one kind of a character, or NULL when the character does not have that kind. */
void *EftChar_GetList(s32 chr, s32 kind);

/* ---- 4. placeholder kind (kinds 6, 8 and 10 of the table) ------------------------------------------------- */

extern u8 gEftCharNullClass[0x18];   /* 0x2C3C28 */

/* Adds a placeholder task to kind 0's list of a character (the task kills itself in its first update). No caller. */
EftQTask *EftCharNull_Start(s32 chr);

/* Manager init: four bytes of work from the pool, a list for one task. */
void EftCharNullMgr_Init(EftQTask *task, s32 *arg);

/* Manager term. */
void EftCharNullMgr_Term(EftQTask *task);

/* Manager update: nothing. */
void EftCharNullMgr_Update(EftQTask *task);

/* Task init. */
void EftCharNull_Init(EftQTask *task, s32 chr);

/* Task term: nothing. */
void EftCharNull_Term(EftQTask *task);

/* Task reset: kills the task. */
void EftCharNull_Reset(EftQTask *task);

/* Task update: kills the task. */
void EftCharNull_Update(EftQTask *task);

/* Task post-update: nothing. */
void EftCharNull_PostUpdate(EftQTask *task);

/* Task draw: nothing. */
void EftCharNull_Draw(EftQTask *task);

/* ---- 5. full-screen flash --------------------------------------------------------------------------------- */

extern EftFlashMgr *gEftFlash;       /* 0x2FEA4C */
extern u8 gEftFlashClass[0x18];      /* 0x2C3C58 */

void EftFlash_Update(EftQTask *task);
s32 EftFlash_GetRushState(void);

/* Starts a flash that belongs to nobody (the owner in the argument is overwritten). Technique modules call it. */
EftQTask *EftFlash_Start(EftFlashArg *arg);

/* Starts a flash and keeps the owner. No caller. */
EftQTask *EftFlash_StartOwned(EftFlashArg *arg);

/* The phase of a live flash task (1 in, 2 hold, 4 out), else 0. No caller. */
s32 EftFlash_GetPhase(EftQTask *task);

/* Freezes or releases a live flash task. No caller. */
void EftFlash_SetPause(EftQTask *task, s32 pause);

/* Manager init. */
void EftFlashMgr_Init(EftQTask *task);

/* Manager term. */
void EftFlashMgr_Term(EftQTask *task);

/* Manager update: starts the white flash of a fighter in action 0x104 with object flag 8 (one flash at a time),
 * and while a flash runs keeps the rush-finish state it waits on. */
void EftFlashMgr_Update(EftQTask *task);

/* Manager reset. */
void EftFlashMgr_Reset(EftQTask *task);

/* Task init: copies the argument and turns its three times into frames. */
void EftFlash_Init(EftQTask *task, EftFlashArg *arg);

/* Task term. */
void EftFlash_Term(EftQTask *task);

/* Task reset: kills the task. */
void EftFlash_Reset(EftQTask *task);

/* Task update: fade in, hold, fade out. The hold lasts until its time has run AND, for a flash started by the
 * manager, the fighter's member flag (BtlCharApi_GetMemberUnk60) is set and the rush finish is in state 0 or 2;
 * a waiting flash (arg.wait) ends its hold when the rush finish reaches state 2. 180 frames end it regardless. */
void EftFlash_Update(EftQTask *task);

/* Task draw: one sprite over the whole screen, queued in the slot drawn after every depth slot. The colour is the
 * argument's colour blended towards transparent white by `fade`. */
void EftFlash_Draw(EftQTask *task);

/* What the rush finish is doing, for the flash that waits on it: 0 nothing, 1 a fighter is in rush-finish phase 1,
 * 2 that fighter has flag 0x2B (when both fighters are in phase 1: both have it). Also keeps gEftFlash->rushBits. */
s32 EftFlash_GetRushState(void);

/* ---- 6. trails (no caller starts one) ------------------------------------------------------------------------ */

extern EftTrailMgr *gEftTrail;     /* 0x2FEA50 */
extern u8 gEftTrailClass[0x18];     /* 0x2C3C88 */
extern Vec4 gEftTrailOrigin;        /* 0x2C3CA0: (0, 0, 0, 1) */

void EftTrail_Update(EftQTask *task);
void EftTrail_UpdateTextures(EftTrail *w);
void EftTrail_SetTextures(EftTrail *w, EftQTex *src);
void EftTrail_DrawSprite(u8 r, u8 g, u8 b, u8 a, f32 x, f32 y, f32 z, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 scale,
                         f32 rot, s32 layer, u64 tex0);

/* Starts a trail at pos that is pulled towards *target, using the manager's own texture table. */
void EftTrail_Start(Vec4 *pos, Vec4 *dir, s32 life, Vec4 *target, f32 speed, f32 accel, f32 turn, f32 turnAccel);

/* Starts an endless trail owned by an object, with the caller's textures and colour. */
void EftTrail_StartOwned(u8 kind, s32 objId, Vec4 *pos, Vec4 *color, EftTrailTexTbl *tbl, f32 width);

/* Starts the fade-out of a trail over the given number of frames. */
void EftTrail_End(EftQTask *task, s32 frames);

/* Sets a trail's colour. */
void EftTrail_SetColor(EftQTask *task, Vec4 *color);

/* Reads a trail's head position. */
void EftTrail_GetPos(EftQTask *task, Vec4 *out);

/* Moves a trail's head. */
void EftTrail_SetPos(EftQTask *task, Vec4 *pos);

/* Sets a trail's width. */
void EftTrail_SetWidth(EftQTask *task, f32 width);

/* Manager init: room for 15 trails. */
void EftTrailMgr_Init(EftQTask *task);

/* Manager term. */
void EftTrailMgr_Term(EftQTask *task);

/* Manager update: the shared texture words have to be renewed this frame. */
void EftTrailMgr_Update(EftQTask *task);

/* Task init: the argument is the whole work. */
void EftTrail_Init(EftQTask *task, EftTrail *arg);

/* Task term: nothing. */
void EftTrail_Term(EftQTask *task);

/* Task reset: kills the task. */
void EftTrail_Reset(EftQTask *task);

/* Task update: shifts the point history and adds the head position, turns the direction towards the target, runs
 * the fade and the life. The direction and speed are computed but never move the head (EftTrail_SetPos does). */
void EftTrail_Update(EftQTask *task);

/* Task draw: the point history as a camera-facing strip (two triangles per segment; the head, middle and tail
 * segments have their own textures). Where the strip bends sharply (|cos| of the angle between the side vectors of
 * two segments below 0.82) and the points are more than 0.8 apart, three glow sprites cover the joint and the
 * segment starts transparent.
 *
 * Matched in cleanup W1. What it took:
 *   - the next point is `p + 1` / `p[1]` everywhere, not a variable;
 *   - the three glow sprites are plain calls (no inline wrapper: the scale `w->width` is loaded during the
 *     argument set-up, behind the store of the stack argument in front of it), each preceded by `sz = 9.45943f;`:
 *     a variable assigned three times is not a loop invariant, so every call loads its own copy of the constant
 *     (three .lit4 words) while the 0.0 / 1.0 literals are hoisted and shared;
 *   - the -7 added to the glow colour is an int variable that gets no register: reload replaces it by its
 *     constant and the int-to-float conversion reads it from a constant-pool word in .sdata (0x2FEA54, the former
 *     "gEftTrailGlowBias"; the same thing as the 50 in EftSmoke_Draw, eft_g.c);
 *   - declaration order `i`, `first`, `limit`, the bias, `w`, `width` (spill slots of i / first, and the order of
 *     the entry block). */
void EftTrail_Draw(EftQTask *task);

/* Fetches this frame's GS texture words: the first trail that uses a part of the shared table renews it, the
 * others copy from the table. */
void EftTrail_UpdateTextures(EftTrail *w);

/* Copies four texture entries into a trail. */
void EftTrail_SetTextures(EftTrail *w, EftQTex *src);

/* Queues a camera-facing textured quad at (x, y, z): half sizes w x h in sixteenths of a unit times scale, turned
 * by rot about the view direction. Sorted by depth; layer 2 / 3 select layer 0 / 1 of the ordering table. */
void EftTrail_DrawSprite(u8 r, u8 g, u8 b, u8 a, f32 x, f32 y, f32 z, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, f32 scale,
                         f32 rot, s32 layer, u64 tex0);


/* ---- 7. character body effect: characters 0x37, 0x98 and 0x99 (fighter effect request 0x3A) ---------------- */

extern void EftCharSlot_Set3(s32 objId, EftQTask *task);   /* per-fighter task slot of this effect: set */
extern void EftCharSlot_Clear3(s32 objId);                   /* clear */
extern EftQTask *EftCharSlot_Get3(s32 objId);              /* get */

extern u8 gEftCharaFxClass[0x18];    /* 0x2C3CC8 */

/* Steps the emitters of one state and spawns their particles at pos, along the effect's direction. */
void EftCharaFx_Emit(s32 objId, EftQTask *task, EftQEmitSet *set, EftQEmitState *state, Vec4 *pos);

/* Init callback: picks the model nodes by character id and places the effect. */
void EftCharaFx_Init(EftQTask *task, EftCharaFxArg *arg);

/* Term callback: releases both emitter states and the fighter's slot. */
void EftCharaFx_Term(EftQTask *task);

/* Update callback: follows the fighter's nodes and spawns the particles; once asked to end it destroys the
 * particles and kills the task in the same update. */
void EftCharaFx_Update(EftQTask *task);

/* Reset callback: destroys the particles once and kills the task. */
void EftCharaFx_Reset(EftQTask *task);

/* Post-update callback (from the second frame on): steps both states' particle lists, clears the phase mask. */
void EftCharaFx_PostUpdate(EftQTask *task);

/* Draw callback: nothing. */
void EftCharaFx_Draw(EftQTask *task);

/* Manager init (per-character kind 7): loads the emitter set from entry 9 of the character's pack, makes room for
 * four tasks and registers the list. arg = {character, kind}. */
void EftCharaFxMgr_Init(EftQTask *task, s32 *arg);

/* Manager term: releases the set and its memory. */
void EftCharaFxMgr_Term(EftQTask *task);

/* Manager update: steps the set. */
void EftCharaFxMgr_Update(EftQTask *task);

/* Starts the body effect unless the fighter already has one. Returns 1 when a task was created. */
s32 EftCharaFx_Start(EftCharaFxArg *arg);
