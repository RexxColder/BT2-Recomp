#include "common.h"
/*
 * Screen-space passes of the battle (0x106D60..0x109938): full-screen strips that read the depth buffer through a
 * CLUT, the alpha-key overlay of the battle objects, the lens discs, the underwater wobble and the depth fog.
 * The strips rely on GfxPostQuad_Set of the neighbouring file (gfxm_a.c), so the two are probably one source.
 * Proper names: gfx_post_b.c (0x106D60..0x107730), gfx_lens.c (..0x1085E0), gfx_alpha_key.c (..0x1087A8),
 * gfx_water.c (..0x1094A8) and gfx_depth_fog.c (..0x109938) if they are split later; nothing forces a split.
 */
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/gfxm_b.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void GfxPostQuad_Set(GfxQuad *out, s32 baseX, s32 baseY, s16 u0, s16 v0, s16 u1, s16 v1, s32 dx, s32 dy, s32 w, s32 h,
                          s16 half);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 k);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Div(Vec4 *dst, Vec4 *src, f32 d);
extern void Vec4_ToFixed4(IVec4 *dst, Vec4 *src);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Mtx_Transpose(Mtx44 *dst, Mtx44 *src);
extern void Vu0Screen_StoreMtx(Mtx44 *dst);
/* gfxm_b_b.c; declared with this file's views of the structures */
void TexFile_UploadPacked(GfxTexFile *file, s32 tbp, s32 cbp);
s32 Tex_Log2Size(s32 n);
void GfxClut_InitPacket(GfxClutWork *work, u16 cbp);
extern GfxWaterStage *BtlStage_GetList90(void);
void GfxWater_SetColor(s32 view, u8 r, u8 g, u8 b, s32 a);
extern s32 BtlStage_GetWaterLevel(f32 *level);
extern s32 Battle_IsSplitScreen(void);
extern s32 DemoCam_IsActive(void);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern f32 sqrtf(f32 x);
extern f32 cosf(f32 x);

/* The part of the battle work this file reads. */
typedef struct GfxBattleWork {
    /* 0x0000 */ u8 unk0[0x19F0];
    /* 0x19F0 */ u64 flags; /* 0x100 paused, 0x2000 loading */
} GfxBattleWork;
extern GfxBattleWork *Battle_GetWork(void);

/* Stack vectors as 16-byte aligned arrays (Sony sceVu0FVECTOR style): the compiler copies them with 64-bit loads. */
typedef f32 GfxFVec[4] __attribute__((aligned(16)));
typedef s32 GfxIVec[4] __attribute__((aligned(16)));
typedef f32 GfxFMtx[4][4] __attribute__((aligned(16)));

void GfxLens_Draw(s32 split, s32 side);
void GfxLens_DrawAll(GfxLensView *view, s32 split, s32 side);
u64 *GfxLens_PutCapture(u64 *p, s32 split, s32 side);
void GfxWater_DrawView(s32 split, s32 view);
void GfxPost_ShiftHighWord(s32 fbp, s32 tbp, s32 h);

#define GFX_RGBAQ_NEUTRAL 0x3F80000080808080 /* grey 0x80, alpha 0x80, Q = 1.0f */


/* Clears the eight flare slots. */
void GfxLens_Clear(void) {
    memset(&gGfxLens, 0, sizeof(gGfxLens.slot));
}

/* Starts a flare at a world position in the first free slot; returns the slot, or -1 when all eight are busy. */
s32 GfxLens_Start(Vec4 *pos, s32 life, u32 rgba, s32 blend, f32 size) {
    s32 i;
    GfxLens *f;

    for (i = 0, f = gGfxLens.slot; i < 8; i++, f++) {
        if (f->life == 0) {
            f->lifeMax = life;
            f->life = life;
            f->rgba = rgba;
            f->blend = blend;
            f->size = size;
            Vec4_Copy(&f->pos, pos);
            return i;
        }
    }
    return -1;
}

/* Frees a flare slot. */
void GfxLens_Stop(u32 slot) {
    if (slot < 8) {
        gGfxLens.slot[slot].life = 0;
    }
}

/* Sets a slot's hold flag: while set, the flare does not age. */
void GfxLens_SetHold(u32 slot, s32 hold) {
    if (slot < 8) {
        gGfxLens.slot[slot].hold = hold;
    }
}

/* Moves a flare. */
void GfxLens_SetPos(u32 slot, Vec4 *pos) {
    if (slot < 8) {
        Vec4_Copy(&gGfxLens.slot[slot].pos, pos);
    }
}
