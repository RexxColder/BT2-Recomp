#include "common.h"
#include "battle/eft_d.h"
#include "sys/dma.h"
#include "sys/gfx_ot.h"

/*
 * End of the stage surface module, 0x13A9D0..0x13C300: the triangle output routines and six parameter
 * accessors. The module starts in eft_c.c (0x138178, EftSurf_*); the two are one original source file.
 * Nothing here touches the simulation: it reads vertices, the clip planes, the split-screen layout and the
 * stage tint, and writes GS packets (ordering table or direct).
 *
 * Idioms the matching functions needed:
 * - EftSurf_DrawTriOtEx is an inline function in the original: EftSurf_DrawPolyOtClipped (once per fan
 *   triangle) and EftSurf_DrawTriOt contain its whole body. Here the body is the static inline
 *   EftSurf_QueueTri and EftSurf_DrawTriOtEx is a one-line wrapper, so the out-of-line copy keeps its place
 *   in the file (a non-static `inline` would be emitted at the end of the object). What gave it away: the
 *   callers pass `&col[0]` of the inlined local array straight into $a0 at the first Vec4_Copy and compute
 *   the same address again for the loop pointer, where a hand-written copy of the body shares one register
 *   (an inlined parameter that is frame base + constant is substituted into each use);
 * - vectors on the stack are 16-byte aligned arrays (EftFVec / EftIVec), copied with 64-bit loads;
 * - GS PRIM is built in a u64 local: constant 0x1B, then the ABE bit stored through a bit-field from an
 *   `abe` variable set at the top of the function (the compiler then keeps 0x40 and 0x1B apart). `abe` is
 *   a u64: with an s32 the loop pass hoists the 0x40 only in its second run and it lands behind the other
 *   loop constants in EftSurf_DrawPolyOtClipped (the other two functions do not care);
 * - XYZF2 is a bit-field struct (16 / 16 / 24 / 8); RGBA are float-to-u8 conversions;
 * - the ordering-table slot is `&gOtZ[z].layer[l]` with z clamped by an if / else if / else;
 * - the off-screen test is an inline function with the four bounds in local variables shifted at use.
 */

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);

/* Local vectors as plain arrays (sceVu0FVECTOR / sceVu0IVECTOR style): 16-byte aligned, so the compiler
   copies them with 64-bit loads. */
typedef f32 EftFVec[4] __attribute__((aligned(16)));
typedef s32 EftIVec[4] __attribute__((aligned(16)));

/* The same as a struct, for a vector passed by value. */
typedef struct EftVec16 {
    f32 v[4];
} __attribute__((aligned(16))) EftVec16;

extern s32 StgTint_IsOn(s32 idx);
extern s32 BtlScene_IsSingleView(void);
extern s32 BtlScene_IsSecondView(void);
extern s32 ClipPoly_ClipPlane(EftSurfVtxD *poly, Vec4 *plane, s32 count); /* clips a polygon in place, returns the new count */
extern void ClipPoly_ProjectCur(EftIVec *scr, EftFVec *st, EftSurfVtxD *poly, s32 count); /* projects; st = s/w, t/w, 1/w */
extern void Vec4_ToInt(s32 *dst, Vec4 *src); /* float vector to integer vector */

/* GS XYZF2 register. */
typedef struct EftXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftXyzf;

/* One vertex of a REGLIST triangle: RGBAQ, ST, XYZF2. */
typedef struct EftTriVtx {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 a;
    /* 0x04 */ f32 q;
    /* 0x08 */ f32 s;
    /* 0x0C */ f32 t;
    /* 0x10 */ EftXyzf xyzf;
} EftTriVtx; /* 0x18 */

/* The ordering-table packet of one fogged, textured triangle. */
typedef struct EftTriPkt {
    /* 0x00 */ u32 tag;        /* NEXT, 7 quadwords */
    /* 0x04 */ u32 next;
    /* 0x08 */ u32 vif0;
    /* 0x0C */ u32 vif1;
    /* 0x10 */ u64 giftag[2];  /* REGLIST: PRIM, TEX0_1, 3 x (RGBAQ, ST, XYZF2), NOP */
    /* 0x20 */ u64 prim;
    /* 0x28 */ u64 tex0;
    /* 0x30 */ EftTriVtx v[3];
    /* 0x78 */ u64 nop;
} EftTriPkt; /* 0x80 */

/* GS PRIM register. */
typedef struct EftPrim {
    u64 prim : 3;
    u64 iip : 1;
    u64 tme : 1;
    u64 fge : 1;
    u64 abe : 1;
    u64 aa1 : 1;
    u64 fst : 1;
    u64 ctxt : 1;
    u64 fix : 1;
    u64 pad : 53;
} EftPrim;

/* The same triangle as a direct GS packet. */
typedef struct EftTriGs {
    /* 0x00 */ u64 giftag[2];
    /* 0x10 */ u64 prim;
    /* 0x18 */ u64 tex0;
    /* 0x20 */ EftTriVtx v[3];
    /* 0x68 */ u64 nop;
} EftTriGs; /* 0x70 */

/* Fills an ordering-table packet with one triangle: header, PRIM, colours and the first two Q. */
#define EFT_SURF_FILL_PKT(pkt, c, abe, t0, t1)                                                                  \
    prim = 0x1B; /* triangle, gouraud, textured */                                                              \
    ((EftPrim *)&prim)->abe = (abe);                                                                            \
    (pkt)->prim = prim;                                                                                         \
    (pkt)->tag = 0x20000007;                                                                                    \
    (pkt)->vif0 = 0x10000000;                                                                                   \
    (pkt)->vif1 = 0x50000007;                                                                                   \
    (pkt)->giftag[0] = 0xC400000000008001;                                                                      \
    (pkt)->giftag[1] = 0xF42142142160;                                                                          \
    (pkt)->next = 0;                                                                                            \
    (pkt)->nop = 0;                                                                                             \
    (pkt)->v[0].r = (c)[0].x;                                                                                   \
    (pkt)->v[0].g = (c)[0].y;                                                                                   \
    (pkt)->v[0].b = (c)[0].z;                                                                                   \
    (pkt)->v[0].a = (c)[0].w;                                                                                   \
    (pkt)->v[0].q = (t0)[2];                                                                                    \
    (pkt)->v[1].r = (c)[1].x;                                                                                   \
    (pkt)->v[1].g = (c)[1].y;                                                                                   \
    (pkt)->v[1].b = (c)[1].z;                                                                                   \
    (pkt)->v[1].a = (c)[1].w;                                                                                   \
    (pkt)->v[1].q = (t1)[2];                                                                                    \
    (pkt)->v[2].r = (c)[2].x;                                                                                   \
    (pkt)->v[2].g = (c)[2].y;                                                                                   \
    (pkt)->v[2].b = (c)[2].z;                                                                                   \
    (pkt)->v[2].a = (c)[2].w

/* The texture coordinates and the three XYZF2 (fog coefficient 0xFF = no fog). */
#define EFT_SURF_FILL_PKT2(pkt, sc0, sc1, sc2, t0, t1, t2)                                                      \
    (pkt)->v[0].s = (t0)[0];                                                                                    \
    (pkt)->v[0].t = (t0)[1];                                                                                    \
    (pkt)->v[1].s = (t1)[0];                                                                                    \
    (pkt)->v[1].t = (t1)[1];                                                                                    \
    (pkt)->v[2].s = (t2)[0];                                                                                    \
    (pkt)->v[2].t = (t2)[1];                                                                                    \
    (pkt)->v[0].xyzf.x = (sc0)[0];                                                                              \
    (pkt)->v[0].xyzf.y = (sc0)[1];                                                                              \
    (pkt)->v[0].xyzf.z = (sc0)[2];                                                                              \
    (pkt)->v[0].xyzf.f = 0xFF;                                                                                  \
    (pkt)->v[1].xyzf.x = (sc1)[0];                                                                              \
    (pkt)->v[1].xyzf.y = (sc1)[1];                                                                              \
    (pkt)->v[1].xyzf.z = (sc1)[2];                                                                              \
    (pkt)->v[1].xyzf.f = 0xFF;                                                                                  \
    (pkt)->v[2].xyzf.x = (sc2)[0];                                                                              \
    (pkt)->v[2].xyzf.y = (sc2)[1];                                                                              \
    (pkt)->v[2].xyzf.z = (sc2)[2];                                                                              \
    (pkt)->v[2].xyzf.f = 0xFF

/* Links the packet at the tail of a chain of depth slot z (clamped to 0..0xFFF), layer l. */
#define EFT_SURF_QUEUE(pkt, z, l, entry)                                                                        \
    if ((z) < 0) {                                                                                              \
        (entry) = &gOtZ[0].layer[l];                                                                            \
    } else if ((z) >= 0x1000) {                                                                                 \
        (entry) = &gOtZ[0xFFF].layer[l];                                                                        \
    } else {                                                                                                    \
        (entry) = &gOtZ[z].layer[l];                                                                            \
    }                                                                                                           \
    (entry)->tail->next = (OtPrim *)(pkt);                                                                      \
    (entry)->tail = (OtPrim *)(pkt)

/* Queues one fogged, textured triangle in the ordering table, from separate screen positions, colours and
   texture coordinates; nothing is queued when the three alphas are 0 or less. With a fog alpha above 0.01 it
   is queued twice: plain with tex[0], then with the alpha scaled by the fog and tex[1]. This is the body of
   EftSurf_DrawTriOtEx, which the original inlines into EftSurf_DrawPolyOtClipped and EftSurf_DrawTriOt (the
   three match only that way; see the notes at the top of the file). */
static inline void EftSurf_QueueTri(EftScrPos *scr0, EftScrPos *scr1, EftScrPos *scr2, Vec4 *col0, Vec4 *col1, Vec4 *col2,
                                    Vec4 *st0, Vec4 *st1, Vec4 *st2, s32 unused, s32 z, u64 *tex, Vec4 *fog, s32 count);

/* Clips a triangle against the five planes of the surface and queues the resulting polygon as a fan
   (vertex 0, k - 1, k), each fan triangle through EftSurf_QueueTri. */
void EftSurf_DrawPolyOtClipped(EftSurfVtxD *poly, s32 unused, u64 *tex, Vec4 *fog, s32 zBias);

/* Sets colour A of the surface parameters. No caller. */
void EftSurf_SetColorA(EftVec16 v);

/* Sets colour B of the surface parameters. No caller. */
void EftSurf_SetColorB(EftVec16 v);

/* Sets the light direction of the surface parameters. No caller. */
void EftSurf_SetLightDir(EftVec16 v);

/* Sets the number of frames one animation step of the surface lasts (given as a float). No caller. */
void EftSurf_SetAnimFrames(f32 v) {
    gEftSurf->animFrames = v;
}

/* Sets the float at +0x30 of the surface parameters. No caller. */
void EftSurf_SetParam30(f32 v);

/* Returns the surface parameters (work + 0x12C0), NULL when the surface module is not running. No caller. */
Vec4 *EftSurf_GetParam(void);

/* 1 when a projected vertex is behind the camera or outside the view's rectangle (which is half as wide
   in split screen). */
static inline s32 EftSurf_IsOffScreen(s32 *xyz);

/* Queues one triangle unless all three vertices are off screen (no clipping). With a fog alpha above
   0.01 it is queued twice: plain with tex[0], then with the alpha scaled by the fog and tex[1]. No caller. */
void EftSurf_DrawTriOt(EftSurfVtxD *tri, s32 unused, u64 *tex, Vec4 *fog, s32 zBias);

/* Queues one triangle from separate screen positions, colours and texture coordinates (the out-of-line copy
   of EftSurf_QueueTri). No caller. */
void EftSurf_DrawTriOtEx(EftScrPos *scr0, EftScrPos *scr1, EftScrPos *scr2, Vec4 *col0, Vec4 *col1, Vec4 *col2,
                         Vec4 *st0, Vec4 *st1, Vec4 *st2, s32 unused, s32 z, u64 *tex, Vec4 *fog, s32 count);

/* Sends one triangle of the reflecting surface at once (not through the ordering table). With a fog alpha
   above 0.01 it is drawn twice: with tex[0] in GS context 1, then with the alpha scaled by the fog and
   tex[1] in context 2. A negative `blend` turns alpha blending off. Callers: EftSurf_DrawReflectTri,
   EftSurf_DrawReflectTriClipped.
   Matching notes: the dead `blend = 0;` is required. With a second statement in the `if` the first jump pass
   cannot turn it into a conditional move; the store is deleted as dead later and the if-conversion pass
   (after the second CSE) makes the move, so `abe` is not folded to `blend >= 0`. `p->prim` has to be the
   first of the header stores. */
void EftSurf_DrawTriDirect(EftScrPos *scr0, EftScrPos *scr1, EftScrPos *scr2, Vec4 *col0, Vec4 *col1, Vec4 *col2,
                           Vec4 *st0, Vec4 *st1, Vec4 *st2, s32 blend, u64 *tex, Vec4 *fog, s32 count);

