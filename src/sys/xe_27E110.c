#include "common.h"
#include "battle/battle.h"
#include "battle/btl_cam.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/math3d.h"
#include "sys/gfxm_a.h"

/*
 * Full-screen post effects, 0x102F28..0x106D60. See include/sys/gfxm_a.h for the overview.
 * Everything here is drawing: nothing reads a pad, the clock or a random generator.
 *
 * One function is INCLUDE_ASM with a behaviourally exact attempt in `#if 0` above it: StgDepthTint_Draw.
 * StgPanBlur_UpdateView matches since cleanup 4 (with two stand-in constructs, see its note) and emits the
 * file's .lit4 (0x2FC280..0x2FC290).
 */

extern void *memset(void *dst, s32 c, u32 n);
extern void *memcpy(void *dst, const void *src, u32 n);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Length(Vec4 *v);
extern void Vu0Screen_StoreMtx(Mtx44 *dst);              /* the current world-to-screen matrix */
extern void Mtx_ProjectInt(s32 *dst, Mtx44 *m, Vec4 *v); /* v through m, perspective divide, to integers */

extern void GfxClut_InitPacket(GfxPostClut *blk, u16 cbp); /* creates a CLUT texture block */
extern s32 Tex_Log2Size(s32 size);                   /* log2 of a texture size */
extern void GfxPost_DrawDepthClut(s32 mode, s32 tbp, s32 cbp, u64 alpha); /* 0x106D60, next file */

/* Stage parameter file readers (stg_a). */
extern void BtlStage_GetLightVecA(Vec4 *out);
extern s32 BtlStage_GetWaterLevel(f32 *level);
extern StgDepthTintParam *BtlStage_GetList40(s32 index);
extern StgGlareParam *BtlStage_GetList48(void);

/* GS registers the shared headers do not define. */
#define GS_TEX0_2 0x07
#define GS_TEX1_2 0x15
#define GS_SET_TEXA(ta0, aem, ta1) ((u64)(ta0) | ((u64)(aem) << 15) | ((u64)(ta1) << 32))
/* The engine's ready-made textured sprite packet (DMA tag, GIF tag, 8 registers in REGLIST form). */
typedef struct GfxPostSpritePkt {
    /* 0x00 */ union {
        u32 w; /* 0x20000005 */
        struct {
            u16 qwc;
            u16 id;
        } h;
    } tag;
    /* 0x04 */ void *next;
    /* 0x08 */ u32 vif0;   /* 0x10000000 */
    /* 0x0C */ u32 vif1;   /* 0x50000005 */
    /* 0x10 */ u64 gifTag; /* 0x8400000000008001: REGLIST, 8 registers */
    /* 0x18 */ u64 regs;   /* PRIM, TEX0_1, RGBAQ, UV, XYZF2, UV, XYZF2, NOP */
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ struct {
        u8 r, g, b, a;
        f32 q;
    } rgbaq;
    /* 0x38 */ struct {
        u16 u, v;
        u32 pad;
    } uv0;
    /* 0x40 */ struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } xyz0;
    /* 0x48 */ struct {
        u16 u, v;
        u32 pad;
    } uv1;
    /* 0x50 */ struct {
        u64 x : 16;
        u64 y : 16;
        u64 z : 24;
        u64 f : 8;
    } xyz1;
    /* 0x58 */ u64 nop;
} GfxPostSpritePkt; /* size 0x60 */

#define GFX_RGBAQ_NEUTRAL 0x3F80000080808080 /* grey 0x80, alpha 0x80, Q = 1.0f */


/* Draws a 16-bit texture over the screen, one line up, bilinear, skipping texels of alpha 0 (TEST 0x3000F);
   `ta0` is the alpha given to texels whose alpha bit is clear (TEXA). */
void GfxPost_DrawTex16Texa(s32 tbp, u64 alpha, u8 ta0) {
    GfxPostQuad q;
    u64 *p;
    u64 *tag;
    s32 i;
    s32 u1;
    s32 step = 32;
    s32 u = 0;
    s32 x = 0;
    s32 half = 1;
    s32 w = 32;
    s32 h = 448;
    s32 n = 512 / step;

    p = Dma_BeginDirect();
    p[0] = GIF_TAG(8, 1, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = 0x3000F;
    p[1] = GS_TEST_1;
    p += 2;
    p[0] = alpha;
    p[1] = GS_ALPHA_1;
    p += 2;
    p[0] = 0;
    p[1] = GS_TEXFLUSH;
    p += 2;
    p[0] = GS_SET_TEXA(ta0, 1, 0);
    p[1] = GS_TEXA;
    p += 2;
    p[0] = 0x60;
    p[1] = GS_TEX1_1;
    p += 2;
    p[0] = (u32)(tbp | 0x24220000) | 0xE40000000;
    p[1] = GS_TEX0_1;
    p += 2;
    p[0] = 0x156;
    p[1] = GS_PRIM;
    p += 2;
    p[0] = GFX_RGBAQ_NEUTRAL;
    p[1] = GS_RGBAQ;
    p += 2;
    tag = p;
    p += 2;
    for (i = 0; i < n; i++) {
        u1 = u + step;
        GfxPostQuad_Set(&q, 0x700, 0x720, u, 0, u1, h, x, 0, w, h, half);
        p[0] = (s64)q.u0 | ((s64)q.v0 << 16);
        p[1] = (s64)q.x0 | ((s64)(q.y0 - 0x10) << 16);
        p += 2;
        p[0] = (s64)q.u1 | ((s64)q.v1 << 16);
        p[1] = (s64)q.x1 | ((s64)(q.y1 - 0x10) << 16);
        p += 2;
        u = u1;
        x += step;
    }
    tag[0] = GIF_TAG_EX(16, 1, GIF_FLG_REGLIST, 4);
    tag[1] = 0x5353;
    Dma_EndDirect(p);
}

/* Blends an untextured rectangle over the screen. */
void GfxPost_FillBlend(u64 alpha, u64 rgbaq) {
    u64 *p;
    u64 *tag;
    s32 i;
    s32 x0;

    p = Dma_BeginDirect();
    p[0] = GIF_TAG(6, 0, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = 1;
    p[1] = GS_COLCLAMP;
    p += 2;
    p[0] = alpha;
    p[1] = GS_ALPHA_1;
    p += 2;
    p[0] = 0x30000;
    p[1] = GS_TEST_1;
    p += 2;
    p[0] = 0;
    p[1] = GS_FBA_1;
    p += 2;
    p[0] = 0x46;
    p[1] = GS_PRIM;
    p += 2;
    p[0] = rgbaq;
    p[1] = GS_RGBAQ;
    p += 2;
    tag = p;
    p += 2;
    x0 = 0;
    for (i = 0; i < 16; i++) {
        p[0] = ((x0 + 0x700) << 4) | (0x7200 << 16);
        p[1] = (s64)((x0 + 0x720) << 4) | ((u64)0x8E00 << 16);
        p += 2;
        x0 += 32;
    }
    tag[0] = GIF_TAG_EX(16, 1, GIF_FLG_REGLIST, 2);
    tag[1] = 0x55;
    Dma_EndDirect(p);
}

/* Points FRAME_1 at a 16-bit page, clears it to black and then sets its write mask. */
void GfxPost_ClearWork(s32 fbp, s32 fbmsk) {
    u64 *p;
    u64 *tag;
    s32 i;
    s32 x0;

    p = Dma_BeginDirect();
    p[0] = GIF_TAG(8, 0, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = fbp | 0x2080000;
    p[1] = GS_FRAME_1;
    p += 2;
    p[0] = GS_SET_ZBUF(0xE0, GS_PSMZ24, 1);
    p[1] = GS_ZBUF_1;
    p += 2;
    p[0] = GS_SET_XYOFFSET(0x7000, 0x7200);
    p[1] = GS_XYOFFSET_1;
    p += 2;
    p[0] = 0x8000000064;
    p[1] = GS_ALPHA_1;
    p += 2;
    p[0] = 0x30000;
    p[1] = GS_TEST_1;
    p += 2;
    p[0] = 0;
    p[1] = GS_FBA_1;
    p += 2;
    p[0] = 0x46;
    p[1] = GS_PRIM;
    p += 2;
    p[0] = GFX_CLEAR_RGBAQ;
    p[1] = GS_RGBAQ;
    p += 2;
    tag = p;
    p += 2;
    x0 = 0;
    for (i = 0; i < 16; i++) {
        p[0] = ((x0 + 0x700) << 4) | (0x7200 << 16);
        p[1] = (s64)((x0 + 0x720) << 4) | ((u64)0x8E00 << 16);
        p += 2;
        x0 += 32;
    }
    tag[0] = GIF_TAG_EX(16, 1, GIF_FLG_REGLIST, 2);
    tag[1] = 0x55;
    p[0] = GIF_TAG(1, 0, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = (fbp | 0x2080000) | ((s64)fbmsk << 32);
    p[1] = GS_FRAME_1;
    p += 2;
    Dma_EndDirect(p);
}

/* Queues XYOFFSET_1. */
void GfxPost_AddXyOffset(s32 x, s32 y) {
    u32 pkt[12] = {
        DMA_TAG_CNT | 2, 0, VIF_FLUSHE, VIF_DIRECT | 2,
        GIF_EOP | 1, 0x10000000, GIF_REG_AD, 0,
        x, (s64)(x | ((s64)y << 32)) >> 32, GS_XYOFFSET_1, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}
