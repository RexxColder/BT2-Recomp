#define Dma_AddTexFlush func_00271370  /* fix_targets */ /* the original uses 0x271370 here */
/*
 * Stage model drawing (0x115478..0x116B98), the last part of the stage model code that starts at 0x114C60
 * (src/battle/stg_d_b.c is the piece in front of this one).
 *
 * Twice per view and frame: StgModel_Cull(view) decides which meshes are visible and StgModel_Draw(view) queues
 * them. Callers: the battle draw (src/battle/battle.c, both the single view and the split-screen views) and
 * ChrView_Update pass 1 (src/battle/view_a_d.c).
 *
 * Nothing here is read by the fight simulation. What it writes: the visibility table (one byte per mesh, rebuilt
 * for every view), the cull result of each tree cell, the alpha of debris meshes, the w of an animated object's
 * position in the stage file (set to 1) and the current texture of animated materials (advanced once per DRAWN
 * view, not per simulated frame, and held while the battle is paused).
 */
#include "common.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/vu1_packet.h"
#include "battle/stgm_a.h"

/* Offset table of the stage file (StgOfsTable in battle/stg_a.h). */
typedef struct StgMOfsTable StgMOfsTable;

/* Local view of the battle work: only the flag word. */
typedef struct StgMWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags;    /* 0x100: paused; 0x2000: stage not drawn; bit 47: no scrolling stage effect */
} StgMWork;

/* Local view of the camera view (View in battle/btl_cam.h). */
typedef struct StgMView {
    /* 0x000 */ u8 unk0[0x100];
    /* 0x100 */ f32 mtx100[16]; /* the matrix VU1 program 4 is loaded with */
} StgMView;

typedef struct StgMFrustum {
    u8 unk0[0xD0];
} StgMFrustum; /* StgFrustum in battle/stg_a.h */

extern BtlStageM *gBtlStage;
extern StgMOfsTable *gStgAnimTable;

extern StgMWork *Battle_GetWork(void);
extern s32 BtlStage_IsObjBroken(s32 idx);
extern s32 BtlStage_GetId(void);
extern void *StgOfsTable_Get(StgMOfsTable *t, s32 i);
extern s32 StgOfsTable_GetCount(StgMOfsTable *t);
extern void StgFrustum_Build(void *view, StgMFrustum *fr);
extern s32 StgFrustum_TestBox(StgMFrustum *fr, f32 x, f32 y, f32 z, f32 r);
extern s32 StgFrustum_TestPart(StgMPart *part, StgMFrustum *fr);
extern f32 Stg_FadeRatio(f32 a, f32 b);
extern f32 Stg_FadeByCamDist(Vec4 *pos, f32 value);
extern void EftStageScroll_Draw(void);
extern void Vu0Screen_StoreMtx(void *m);
extern void Vu0Clip_StoreMtx(void *m);
extern void Vu0Cur_LoadIdentity(void);
extern void Vu0Cur_RotateZXY(Vec4 *angles);
extern void Vu0Cur_Translate(Vec4 *v);
extern void Vu0Cur_StoreMtx(void *m);
extern void Vu0Cur_LoadMtx(void *m);
extern void *memset(void *, s32, u32);

/* Draws the animated stage objects: for each animation, every object that plays it, posed at its frame. */
void StgModel_DrawAnims(void);

/* Culls one cell of the tree and its children. vis: 0 = the parent is wholly inside (no more tests), 1 = test. */
void StgModel_CullCell(StgMCell *cell, f32 size, s32 vis, struct StgFrustum *fr);

/* Builds the visibility table for one view: the culling tree, the always-drawn parts, then the debris. */
void StgModel_Cull(void *view);

/* Marks the pieces of falling objects visible, with an alpha that fades with age and camera distance. */
void StgModel_FadeDebris(void);

/* Uploads one texture of the stage texture file to the stage's work block and selects it. */
void StgModel_SetTexture(s32 index) {
    Dma_AddTexFlush();
    TexFile_UploadOne(gBtlStage->tex, index, 0x2A00, 0x32C0);
    Dma_AddTex0(gBtlStage->tex->ent[index].tex0 | 0x0006580400002A00);
}

/* Draws the debris group with VU1 program 7. Returns 0 when the group has materials, else `drawn` unchanged. */
s32 StgModel_DrawDebris(s32 drawn, u8 *vis);

/* The loop shared by the plain groups: every visible mesh of every material, texture set once per material. */
#define STGM_DRAW_GROUP(g)                                                      \
    for (i = 0; i < mdl->grp[g].count; i++) {                                   \
        chain = 0;                                                              \
        mesh = mats[i].meshes;                                                  \
        for (j = 0; j < mats[i].count; j++) {                                   \
            if (vis[mesh[j].visIdx] != 0) {                                     \
                if (chain == 0) {                                               \
                    StgModel_SetTexture(mats[i].tex);                           \
                }                                                               \
                chain = mesh[j].chain;                                          \
                Vu1Pkt_CallProg4(chain);                                        \
            }                                                                   \
        }                                                                       \
    }

/*
 * Draws the stage for one view. Order: group 0 (no depth writes), the scrolling stage effect, group 1, group 2
 * (the stage proper, with animated textures), the animated objects, then the blended groups 3..5 and the debris
 * (group 6). On stage 8 the debris is drawn before the blended groups; on stage 5 group 3 is skipped.
 * Not while a stage load job runs (flag 0x2000) or while the stage is not ready.
 */
void StgModel_Draw(void *view);

/* Queues the stage's GS state: frame buffer of this frame, depth buffer, blend, test, filter, clamps. */
void StgModel_SetDrawEnv(void);

/* Queues the state of the blended groups: depth buffer with writes off, test, FBA. */
void StgModel_SetBlendEnv(void);

/* Queues TEST_1 = 0x507FB (alpha >= 0x7F, depth >=): the stage proper. */
void StgModel_SetTestOpaque(void);

/* Queues TEST_1 = 0x51809 (alpha == 0x80, otherwise colour only; depth >=): the debris. */
void StgModel_SetTestDebris(void);

/* Queues TEST_1 = 0x5001B (alpha >= 1, depth >=): the default. */
void StgModel_SetTestDefault(void);

/* The same state as StgModel_SetDrawEnv with TEST_1 = 0x507FB, for the animated objects. */
void StgModel_SetAnimDrawEnv(void);
