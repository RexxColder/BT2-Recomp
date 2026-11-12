#define BtlObj_Get func_002B7CB8  /* fix_targets */ /* the original uses 0x2b7cb8 here */
#include "common.h"
#include "battle/eft_ad.h"

/*
 * 0x1A7608..0x1A9D90: the effect mesh (EftMesh_*), the effect model objects (EftObj_*) and the mesh's two
 * triangle writers. See include/battle/eft_ad.h.
 *
 * EftMesh_IsOffScreen is a non-static inline of the original: it is defined in the middle of the file (the
 * two fan functions after it have it inlined, the two draw loops before it call it) and the compiler emits its
 * out-of-line copy at the end of the object, 0x1A9D38. That is why the object ends at 0x1A9D90.
 */

/* The view being drawn (include/battle/btl_cam.h). */
typedef struct EftAdView {
    /* 0x000 */ u8 unk0[0x140];
    /* 0x140 */ Mtx44 world2screen;
} EftAdView;

/* A battle object as far as the wrappers reach into it (BtlObj in include/battle/btl_obj.h). */
typedef struct EftAdObj {
    /* 0x000 */ u8 unk0[0x950];
    /* 0x950 */ Vec4 pos;
    /* 0x960 */ Vec4 rot;
    /* 0x970 */ u8 unk970[0xD0];
    /* 0xA40 */ u32 flags;     /* BTL_OBJ_FLAG_*; 2 = drawn */
} EftAdObj;

/* An order table slot: two lists of packets (include/sys/gfx.h has the full description). */
typedef struct EftAdOtPrim {
    u32 tag;
    void *next;
} EftAdOtPrim;

typedef struct EftAdOtEntry {
    EftAdOtPrim *head;
    EftAdOtPrim *tail;
} EftAdOtEntry;

typedef struct EftAdOtSlot {
    EftAdOtEntry layer[2];
} EftAdOtSlot;

typedef struct EftAdXyzf {
    u64 x : 16;
    u64 y : 16;
    u64 z : 24;
    u64 f : 8;
} EftAdXyzf;

typedef struct EftAdRgbaq {
    u8 r, g, b, a;
    f32 q;
} EftAdRgbaq;

typedef struct EftAdSt {
    f32 s, t;
} EftAdSt;

/* Sets CLAMP_1 and CLAMP_2 (texture wrap modes of both GS contexts) to 0. */
typedef struct EftMeshClampPkt {
    /* 0x00 */ u32 dmaTag;     /* 0x20000003 */
    /* 0x04 */ void *next;
    /* 0x08 */ u32 vif0;       /* 0x10000000 */
    /* 0x0C */ u32 vif1;       /* 0x50000003 */
    /* 0x10 */ u64 gifTag;     /* 0x1000000000008002: PACKED, 1 register, 2 loops */
    /* 0x18 */ u64 regs;       /* A+D */
    /* 0x20 */ u64 data0;
    /* 0x28 */ u64 addr0;      /* 8: CLAMP_1 */
    /* 0x30 */ u64 data1;
    /* 0x38 */ u64 addr1;      /* 9: CLAMP_2 */
} EftMeshClampPkt; /* 0x40 */

/* Textured gouraud triangle. */
typedef struct EftMeshTexTriPkt {
    /* 0x00 */ u32 dmaTag;     /* 0x20000007 */
    /* 0x04 */ void *next;
    /* 0x08 */ u32 vif0;       /* 0x10000000 */
    /* 0x0C */ u32 vif1;       /* 0x50000007 */
    /* 0x10 */ u64 gifTag;     /* 0xC400000000008001: REGLIST, 12 registers */
    /* 0x18 */ u64 regs;       /* PRIM, TEX0_1 (TEX0_2 for layers 2 / 3), 3 x (RGBAQ, ST, XYZF2), NOP */
    /* 0x20 */ u64 prim;       /* 0x1B (gouraud textured triangle) | ABE << 6 | context << 9 */
    /* 0x28 */ u64 tex0;
    /* 0x30 */ struct {
        EftAdRgbaq rgbaq;
        EftAdSt st;
        EftAdXyzf xyz;
    } v[3];
    /* 0x78 */ u64 nop;
} EftMeshTexTriPkt; /* 0x80 */

/* Untextured gouraud triangle. */
typedef struct EftMeshTriPkt {
    /* 0x00 */ u32 dmaTag;     /* 0x20000005 */
    /* 0x04 */ void *next;
    /* 0x08 */ u32 vif0;       /* 0x10000000 */
    /* 0x0C */ u32 vif1;       /* 0x50000005 */
    /* 0x10 */ u64 gifTag;     /* 0x8400000000008001: REGLIST, 8 registers */
    /* 0x18 */ u64 regs;       /* PRIM, 3 x (RGBAQ, XYZF2), NOP */
    /* 0x20 */ u64 prim;       /* 0xB (gouraud triangle) | ABE << 6 */
    /* 0x28 */ struct {
        EftAdRgbaq rgbaq;
        EftAdXyzf xyz;
    } v[3];
    /* 0x58 */ u64 nop;
} EftMeshTriPkt; /* 0x60 */

extern u8 *gOtCur;
extern EftAdOtSlot *gOtZ;
extern void *memcpy(void *dst, const void *src, u32 n);
extern u8 *Dma_BeginDirect(void);
extern void Dma_EndDirect(u8 *end);

extern EftAdView *gBtlCamView;

extern void *memset(void *dst, s32 c, u32 n);
extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_MulVec4(Vec4 *dst, Mtx44 *m, Vec4 *v);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);          /* copies a matrix */
extern void Vu0Cur_Push(void);                            /* VU0 matrix stack push */
extern void Vu0Cur_LoadMtx(Mtx44 *m);                        /* load the matrix */
extern void Vu0Cur_Pop(void);                            /* pop */
extern void Vec4_Mul(Vec4 *dst, Vec4 *a, Vec4 *b);     /* per-component product */
extern s32 Vu0Cur_ProjectPointsStq(EftAdScr *xyz, Vec4 *stq, Vec4 *pos, Vec4 *uv, s32 n); /* projects n points with uv */
extern EftAdVec *EftGfx_GetClipPlanes(void);                 /* the five clip planes of the view */
extern s32 ClipPoly_ClipPlane(void *poly, EftAdVec *plane, s32 count); /* clips a polygon in place, new count */
extern void ClipPoly_ProjectCur(EftAdScr *scr, EftAdVec *stq, void *poly, s32 count); /* projects a polygon */
extern s32 BtlScene_IsEffectHidden(s32 objId, s32 type);
extern s32 BtlObj_Create(s32 type, void *res, s32 active);
extern s32 BtlObj_Destroy(s32 id);
extern EftAdObj *BtlObj_Get(s32 id);
extern void BtlObjXf_Update(EftAdObj *obj);                   /* rebuilds the object's matrix from pos / rot */
extern void BtlObjAnim_PlayModel(EftAdObj *obj, s32 anim, s32 mode); /* starts animation 0..7 of the model */
extern s32 BtlObjAnim_GetMode(EftAdObj *obj);                    /* the animation's play mode (0 = none) */
extern void BtlObjXf_SetMtx(EftAdObj *obj, Mtx44 *m);         /* sets the object's matrix and its inverse */

/* A vertex handed to the clipper and the triangle writers. */
typedef struct EftMeshOut {
    /* 0x00 */ Vec4 pos;
    /* 0x10 */ Vec4 uv;
    /* 0x20 */ Vec4 color;
} EftMeshOut; /* 0x30 */

s32 EftMesh_IsOffScreen(EftAdScr p);
void EftMesh_DrawTriClip(EftMeshOut *v, s32 hasTex, s32 blend, s32 flag1, s32 flag2, s32 zflip, u64 tex0, s32 zOfs);
void EftMesh_DrawNowTriClip(EftMeshOut *v, u64 tex0, s32 abe);
void EftMesh_QueueTri(EftAdScr *p0, EftAdScr *p1, EftAdScr *p2, EftAdVec *c0, EftAdVec *c1, EftAdVec *c2,
                      EftAdVec *t0, EftAdVec *t1, EftAdVec *t2, s32 flag1, s32 flag2, s32 hasTex, s32 blend, s32 z,
                      u64 tex0);
void EftMesh_SendTri(EftAdScr *p0, EftAdScr *p1, EftAdScr *p2, EftAdVec *c0, EftAdVec *c1, EftAdVec *c2,
                     EftAdVec *t0, EftAdVec *t1, EftAdVec *t2, u64 tex0, s32 abe);
void EftMesh_DrawClip(EftMesh *mesh);
void EftMesh_DrawNowClip(EftMesh *mesh, s32 abe);
void EftMesh_DrawPlain(EftMesh *mesh);
void EftMesh_DrawNowPlain(EftMesh *mesh, s32 abe);

/* Binds a mesh instance to mesh data: identity matrix, white, uv scale 1, no owner. */
void EftMesh_Init(EftMesh *mesh, EftMeshData *data);

/* Sets the texture table. */
void EftMesh_SetTex(EftMesh *mesh, EftAdTex *tex);

/* Sets the model-to-world matrix. */
void EftMesh_SetMtx(EftMesh *mesh, Mtx44 *m);

/* Copies an instance. */
void EftMesh_Copy(EftMesh *dst, EftMesh *src);

/* Sets the layer handed to the triangle writer (0 / 1: the two lists of an order table slot; 2 / 3 the same
   with the other GS context; < 0: layer 0 without alpha blending). */
void EftMesh_SetLayer(EftMesh *mesh, s32 blend);

/* Sets the texture index offset. */
void EftMesh_SetTexBase(EftMesh *mesh, s32 base);

/* Clip every triangle against the view volume (off: triangles with a vertex off screen are dropped). */
void EftMesh_SetClip(EftMesh *mesh, s32 on);

/* Sets flag 1: every triangle is preceded by a packet that sets three GS registers (see EftMesh_QueueTri). */
void EftMesh_SetRepeat(EftMesh *mesh, s32 on);

/* Sets flag 2 (handed to the triangle writer, which ignores it). No caller. */
void EftMesh_SetFlag2(EftMesh *mesh, s32 on);

/* Reverses the sort depth. No caller. */
void EftMesh_SetZFlip(EftMesh *mesh, s32 on);

/* Sets the sort depth offset. No caller. */
void EftMesh_SetZOfs(EftMesh *mesh, s32 ofs);

/* Sets the uv offset (texture scroll). */
void EftMesh_SetUvOfs(EftMesh *mesh, f32 u, f32 v);

/* Sets the uv scale. */
void EftMesh_SetUvScale(EftMesh *mesh, f32 scale);

/* Sets the colour that multiplies the vertex colours (0x80 = 1.0). */
void EftMesh_SetColor(EftMesh *mesh, u8 r, u8 g, u8 b, u8 a);

/* Sets the fighter and effect type the mesh is hidden with (BtlScene_IsEffectHidden). */
void EftMesh_SetOwner(EftMesh *mesh, s32 objId, s32 type);

/* Queues the mesh's triangles in the order table, unless its owner's effects of this type are hidden. */
void EftMesh_Draw(EftMesh *mesh);

/* Sends the mesh's triangles to the GS at once (abe: alpha blending on), with the same hidden test. */
void EftMesh_DrawNow(EftMesh *mesh, s32 abe);

/* Draws every triangle of the mesh through the clipper, queued in the order table. */
void EftMesh_DrawClip(EftMesh *mesh);

/* Draws every triangle of the mesh through the clipper, sent to the GS at once. Always textured. */
void EftMesh_DrawNowClip(EftMesh *mesh, s32 abe);

/* Draws every triangle of the mesh that is wholly on screen, queued in the order table by its first vertex's
   depth. */
void EftMesh_DrawPlain(EftMesh *mesh);

/* Draws every triangle of the mesh that is wholly on screen, sent to the GS at once. Always textured. */
void EftMesh_DrawNowPlain(EftMesh *mesh, s32 abe);

/* Whether a projected point is outside the GS drawing area or behind the camera. A non-static inline of the
   original: the two functions after it have it inlined, and its out-of-line copy is emitted at the end of the
   object (0x1A9D38), where the two draw loops above call it. */
inline s32 EftMesh_IsOffScreen(EftAdScr p);

/* Clips one triangle (v has room for the 9 vertices clipping can produce) against the five view planes,
   projects it and queues the resulting fan, each triangle at the mean depth of its three points. */
/* The fan's depth values are read through a pointer to scr[0].z plus the byte offset i << 4 (matching needs this
   form: indexing scr[i].z gives other induction variables). */
#define EFT_FAN_Z(zp, i) (*(s32 *)((u8 *)(zp) + ((i) << 4)))
void EftMesh_DrawTriClip(EftMeshOut *v, s32 hasTex, s32 blend, s32 flag1, s32 flag2, s32 zflip, u64 tex0, s32 zOfs);

/* The same, with each triangle of the fan sent to the GS at once. */
/* Note the screen tests: this variant tests points 0, 1 and 2 for every triangle of the fan, not 0, i - 1 and i
   (fixed stack offsets 0x20 / 0x30 / 0x40 in the original). */
void EftMesh_DrawNowTriClip(EftMeshOut *v, u64 tex0, s32 abe);

/* ---- effect model objects --------------------------------------------------------------------------------- */

/* Makes a battle object (type 1, active) from a model that is already in memory: fills the caller's resource
   record with the model pointer and hands it to BtlObj_Create. Returns the object id, -1 when the 12 objects
   are all in use. */
s32 EftObj_Create(EftObjRes *res, void *model);

/* Releases the battle object. */
s32 EftObj_Destroy(s32 id);

/* Writes the object's position (used by EftObj_UpdateMtx). No caller. */
void EftObj_SetPos(s32 id, Vec4 *pos);

/* Rebuilds the object's matrix from its position and rotation. No caller. */
void EftObj_UpdateMtx(s32 id);

/* Starts one of the model's animations. */
void EftObj_PlayAnim(s32 id, s32 anim, s32 mode) {
    BtlObjAnim_PlayModel(BtlObj_Get(id), anim, mode);
}

/* Whether an animation is playing. */
s32 EftObj_IsAnimPlaying(s32 id);

/* Writes the object's rotation (used by EftObj_UpdateMtx). No caller. */
void EftObj_SetRot(s32 id, Vec4 *rot);

/* Poses the object: sets its world matrix. */
void EftObj_SetMtx(s32 id, Mtx44 *m);

/* Shows or hides the object (the battle object's "drawn" flag). */
void EftObj_SetVisible(s32 id, s32 on);

/* Nothing (called right after EftObj_Create by every user). */
void EftObj_Nop(void);

/* Queues one gouraud triangle in the order table at depth z, list `layer` (0 / 1; 2 / 3 = the same lists with
   GS context 2; < 0 = list 0 without alpha blending). Nothing when all three alphas are below 0.1. With `repeat`
   a packet that sets CLAMP_1 and CLAMP_2 to 0 (texture repeat) is queued in front. Textured (hasTex) the packet
   is PRIM, TEX0, 3 x (RGBAQ, ST, XYZF2); untextured PRIM, 3 x (RGBAQ, XYZF2). flag2 is not used. */
/* Matching needs: the list index l and the entry pointer e as block-local variables of each of the three blocks
   (function-scope ones merge the three order-table tails completely), ctx as an int widened separately for PRIM
   and shifted as an int for the register list, and the header stores in this order. */
void EftMesh_QueueTri(EftAdScr *p0, EftAdScr *p1, EftAdScr *p2, EftAdVec *c0, EftAdVec *c1, EftAdVec *c2,
                      EftAdVec *t0, EftAdVec *t1, EftAdVec *t2, s32 repeat, s32 flag2, s32 hasTex, s32 layer, s32 z,
                      u64 tex0);

/* Sends one textured gouraud triangle to the GS at once (the same packet as the textured case above, built on
   the stack and copied into a direct DMA transfer). Nothing when all three alphas are below 0.1. */
/* abe goes through an s8 local (set after the DMA call) before it is widened: that gives the original's
   sll / sra ahead of the 64-bit shift pair. */
void EftMesh_SendTri(EftAdScr *p0, EftAdScr *p1, EftAdScr *p2, EftAdVec *c0, EftAdVec *c1, EftAdVec *c2,
                     EftAdVec *t0, EftAdVec *t1, EftAdVec *t2, u64 tex0, s32 abe);
