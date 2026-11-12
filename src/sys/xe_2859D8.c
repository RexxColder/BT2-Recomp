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


/* Sets the tint of a view's underwater wobble. */
void GfxWater_SetColor(s32 view, u8 r, u8 g, u8 b, s32 a) {
    gGfxWater[view].rgba = r | (a << 24) | ((b << 16) | (g << 8));
}

/* Fills a 256-entry CLUT (GS order) with black whose alpha falls from 255 at index 0 to 0 at index 255. */
void GfxDepthFog_BuildClut(u8 *clut) {
    s32 i;
    s32 n;

    for (i = 0; i < 256; i++) {
        n = ((i & 0xE7) | ((i & 8) << 1) | ((i & 0x10) >> 1)) * 4;
        clut[n + 0] = 0;
        clut[n + 1] = 0;
        clut[n + 2] = 0;
        clut[n + 3] = 255 - i;
    }
}

/* Moves the upper 16 bits of every pixel of the 32-bit buffer at block `tbp` into the top two bits of page `fbp`
   seen as a 16-bit buffer: 32 sprites of 8 x `h` shifted right by 8 pixels, write mask 0x3FFF.
   `w` and `tw` are two variables (both 8) and `u` is computed in front of the call: that gives the two strip
   counters their own step registers (s7, fp) in the original's order. */
void GfxPost_ShiftHighWord(s32 fbp, s32 tbp, s32 h) {
    GfxQuad q;
    u64 *p;
    u64 *tag;
    s32 i;
    s32 w = 8;
    s32 tw = 8;
    s32 n;

    p = Dma_BeginDirect();
    p[0] = GIF_TAG(11, 1, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = (s64)(fbp | 0x02080000) | 0x3FFF00000000;
    p[1] = GS_FRAME_1;
    p += 2;
    p[0] = 0x30000;
    p[1] = GS_TEST_1;
    p += 2;
    p[0] = ((u64)(h - 1) << 48) | 0x1FF0000;
    p[1] = GS_SCISSOR_1;
    p += 2;
    p[0] = 0;
    p[1] = GS_TEXFLUSH;
    p += 2;
    p[0] = 0x8000000000;
    p[1] = GS_TEXA;
    p += 2;
    p[0] = 0;
    p[1] = GS_TEX1_1;
    p += 2;
    p[0] = (s64)(tbp | 0x2B220000) | 0xE80000000;
    p[1] = GS_TEX0_1;
    p += 2;
    p[0] = 0x116;
    p[1] = GS_PRIM;
    p += 2;
    p[0] = GFX_RGBAQ_NEUTRAL;
    p[1] = GS_RGBAQ;
    p += 2;
    p[0] = 0;
    p[1] = GS_FBA_1;
    p += 2;
    p[0] = GS_SET_XYOFFSET(GFX_OFX, GFX_OFY + 8);
    p[1] = GS_XYOFFSET_1;
    p += 2;
    tag = p;
    n = 512 / w;
    p += 2;
    for (i = 0; i < n; i += 2) {
        s32 u = (i + 1) * tw;

        GfxPostQuad_Set(&q, 0x700, 0x720, i * w, 0, i * w + 8, h, u, 0, tw, h, 0);
        p[0] = (s64)q.u0 | ((s64)q.v0 << 16);
        p[1] = (s64)q.x0 | ((s64)q.y0 << 16);
        p += 2;
        p[0] = (s64)q.u1 | ((s64)q.v1 << 16);
        p[1] = (s64)q.x1 | ((s64)q.y1 << 16);
        p += 2;
    }
    tag[0] = GIF_TAG_EX(64, 1, GIF_FLG_REGLIST, 2);
    tag[1] = 0x53;
    p[0] = GIF_TAG(2, 1, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = GS_SET_SCISSOR(0, 511, 0, 447);
    p[1] = GS_SCISSOR_1;
    p += 2;
    p[0] = GS_SET_XYOFFSET(GFX_OFX, GFX_OFY);
    p[1] = GS_XYOFFSET_1;
    p += 2;
    Dma_EndDirect(p);
}
