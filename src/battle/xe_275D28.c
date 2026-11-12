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


/* Queues the stage's GS state: frame buffer of this frame, depth buffer, blend, test, filter, clamps. */
void StgModel_SetDrawEnv(void) {
    u32 pkt[40] = {
        0x10000009, 0, 0x10000000, 0x50000009,                /* DMA cnt 9 / VIF direct 9 */
        0x8008, 0x10000000, 0xE, 0,                           /* GIF tag: 8 x A+D, EOP */
        !(gGfx.frame & 1) ? 0x80070 : 0x80000, 0, 0x4C, 0,     /* FRAME_1 */
        0x310000E0, 0, 0x4E, 0,                               /* ZBUF_1 */
        0x44, 0, 0x42, 0,                                     /* ALPHA_1 */
        0x5001B, 0, 0x47, 0,                                  /* TEST_1 */
        0x60, 0, 0x14, 0,                                     /* TEX1_1 */
        0, 0, 0x4A, 0,                                        /* FBA_1 */
        0, 0, 8, 0,                                           /* CLAMP_1 */
        1, 0, 0x46, 0,                                        /* COLCLAMP */
    };

    Dma_AddData(pkt, 0xA0);
}

/* Queues the state of the blended groups: depth buffer with writes off, test, FBA. */
void StgModel_SetBlendEnv(void) {
    u32 pkt[20] = {
        0x10000004, 0, 0x10000000, 0x50000004,
        0x8003, 0x10000000, 0xE, 0,
        0x310000E0, 1, 0x4E, 0,                               /* ZBUF_1, ZMSK */
        0x54000, 0, 0x47, 0,                                  /* TEST_1 */
        1, 0, 0x4A, 0,                                        /* FBA_1 */
    };

    Dma_AddData(pkt, 0x50);
}
