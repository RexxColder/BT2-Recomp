#include "common.h"
#include "battle/battle.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/heap.h"
#include "sys/gfxm_e.h"

/*
 * Battle object model binding and ground shadow, 0x1131D8..0x114860. See include/sys/gfxm_e.h.
 *
 *   BtlObjMdl_*  what BtlObj_Setup / BtlObj_Destroy (btl_obj.c) call to bind an object to its files
 *   ObjShadow_*  the ground shadow: the model is drawn from straight above into a 256x256 work page
 *                (page 0x150 = texture block 0x2A00), and that picture is projected on the stage triangles
 *                under the object, collected by StgShadow_Collect, with VU1 program 6
 *
 * Everything here is drawing or set-up. Nothing reads a pad, the clock or a random generator.
 *
 * ObjShadow_BuildPacket is INCLUDE_ASM with a behaviourally exact attempt in `#if 0` above it; the 26 other
 * functions match. To check them with fdiff, run it on a copy of this file without the INCLUDE_ASM line (they
 * print OK with or without the attempt compiled). The constant 0.02 of ObjShadow_BuildPacket (0x2FC2CC) is the
 * word in front of this file's .lit4 (0x2FC2D0..0x2FC2FC) and stays in the assembly chunk.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern float sqrtf(float x);

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern f32 Vec3_Dot(Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void sceVu0CameraMatrix(Mtx44 *m, Vec4 *pos, Vec4 *zdir, Vec4 *ydir);
extern void Mtx_MakeViewScreen(Mtx44 *m, f32 scrz, f32 ax, f32 ay, f32 cx, f32 cy, f32 zmin, f32 zmax, f32 nearz,
                               f32 farz);
extern void Vu0Cur_LoadIdentity(void);
extern void Vu0Cur_RotateZXY(void *angles);
extern void Vu0Cur_StoreMtx(Mtx44 *m);
extern void Vu0Screen_StoreMtx(Mtx44 *m);
extern void Vu0Clip_StoreMtx(Mtx44 *m);

extern void ColBox_SetCenterHalf(ColBoxE *box, Vec4 *center, Vec4 *half);
extern void ColBox_GetCenter(ColBoxE *box, Vec4 *out);
extern void ColBox_GetHalf(ColBoxE *box, Vec4 *out);

/* btl_obj.c and the files after it. */
extern s32 BtlObjVis_AllocBit(s32 bit);
extern void BtlObjVis_FreeBit(s32 bit);
extern s32 BtlObjVis_AllocFreeBit(void);
extern void BtlObjLight_GetHalf(Vec4 *out);
extern void BtlObjLight_GetColor(Vec4 *out);
extern ObjMdlPart *BtlObjPoolE0_Alloc(void);
extern s32 BtlObjPoolE0_FreeList(SList *list);
extern ObjShadowPool *BtlObjPool3_Get(void);
extern ObjShadow *BtlObjPool3_Alloc(void);
extern s32 BtlObjPool3_Free(ObjShadow *node);
extern void BtlObj_BindTables(ObjMdlObj *obj);
extern void BtlObj_InitFlags(ObjMdlObj *obj);
extern void BtlObjXf_Reset(ObjMdlObj *obj);
extern void BtlObjBody_Init(ObjMdlObj *obj);
extern void BtlObj_CreateFace(ObjMdlObj *obj);
extern void BtlObj_FreeFace(ObjMdlObj *obj);
extern void BtlObjAnim_Init(ObjMdlObj *obj);
/* Model node: the matrix is at +0x10 (BtlObjPart). */
typedef struct ObjMdlNode {
    /* 0x00 */ u8 unk00[0x10];
    /* 0x10 */ Mtx44 mtx;
} ObjMdlNode;
extern ObjMdlNode *BtlObj_GetNode(ObjMdlObj *obj, s32 node);

/* Stage triangles under a box (eft_det_b). */
typedef struct ObjShadowOut {
    /* 0x0 */ f32 alpha;
    /* 0x4 */ s32 count;
} ObjShadowOut;
extern s32 StgShadow_Collect(s32 zone, ColBoxE *box, s32 max, ObjShadowTri *buf);
extern ObjShadowOut *StgShadow_GetOut(void);

/* VU1 packet layer (sys/vu1_packet.h). Program 2's constant block: matrices at +0xC0 and +0x100. */
typedef struct ObjVu1Prog2 {
    /* 0x000 */ u8 unk000[0xC0];
    /* 0x0C0 */ Mtx44 screen;
    /* 0x100 */ Mtx44 clip;
} ObjVu1Prog2;
extern ObjVu1Prog2 *Vu1Pkt_LoadProg2(s32 alt);
extern void Vu1Pkt_CallProg6(u32 *chain);
extern void Vu1Pkt_LoadProg6(void *view, Mtx44 *mtx, Vec4 *vec);

/* The object draw of the previous file (0x10EC18..0x112A30): queues the object's meshes. */
extern void ObjDraw_DrawPartsFlat(ObjMdlObj *obj);

void MdlTex_RebaseChain(s32 single, void *chain, s32 tbp, s32 cbp, s32 tbp2, s32 cbp2, u32 minTbp, u32 minCbp);

/* The battle view as ObjShadow_Draw reads it: its scissor rectangle. */
typedef struct ObjShadowCam {
    /* 0x000 */ u8 unk000[0x200];
    /* 0x200 */ s32 x0;
    /* 0x204 */ s32 x1;
    /* 0x208 */ s32 y0;
    /* 0x20C */ s32 y1;
} ObjShadowCam;

/* Four floats, 8-byte aligned: constant initialisers of this type are copied with ld / sd. */
typedef struct ObjVec8 {
    f32 x, y, z, w;
} __attribute__((aligned(8))) ObjVec8;

/* A plane (normal, distance) with the same layout. It has to be a type of its own: the original has two copies
   of the constant 0, -1, 0, 1 in its read-only data (0x2EB980 for the plane of ObjShadow_LoadProg, 0x2EB990 for
   the direction of ObjShadow_Update), and this compiler shares identical initialisers of one type. */
typedef struct ObjPlane8 {
    f32 a, b, c, d;
} __attribute__((aligned(8))) ObjPlane8;

#define GS_PRMODECONT 0x1A
#define GS_PRMODE 0x1B

/* Gives every material texture of the model its row of the alpha table: the alpha bytes of the first 16 CLUT
   entries become (slot + row * 15), and the slot's base alpha is copied into the model header. */
void BtlObjMdl_InitAlphaSlots(void *res, ObjMdl *mdl, s32 row);

/* Points the object at its model and texture files. The first time a model file is bound its texture
   references are moved to the object texture area and it claims an alpha row; later binds only re-claim the row. */
void BtlObjMdl_BindFiles(ObjMdlObj *obj);

/* Takes one part from the pool for every mesh record and remembers the first part of each node. */
void BtlObjMdl_AllocParts(ObjMdlObj *obj);

/* Gives the object's parts back to the pool. */
s32 BtlObjMdl_FreeParts(ObjMdlObj *obj);

/* Builds everything of an object whose type and resource slot are set. */
void BtlObjMdl_Init(ObjMdlObj *obj);

/* Clears the object and builds it from a resource slot. */
void BtlObjMdl_Create(s32 type, ObjMdlObj *obj, void *res);

/* Releases what BtlObjMdl_Init claimed and clears the object. Does nothing for an object that was never built. */
void BtlObjMdl_Destroy(ObjMdlObj *obj);

/* Size in words of the packet ObjShadow_BuildPacket makes for `count` triangles. */
s32 ObjShadow_CalcPacketWords(s32 count);

/* Builds the VU1 packet that draws the collected triangles with the shadow texture: batches of up to 18
   triangles, every vertex lifted 0.02 along the triangle's normal, with the normal and the colour. Returns 1.
   Layout: a DMA "ret" tag whose count is filled in at the end; one quadword unpacked at TOPS; per batch a
   three-quadword header at TOPS + 0 (GIF tags; the triangle count goes into the second one), 12 quadwords per
   triangle at TOPS + 3 (per vertex: x, y, z, a no-draw flag that is 1 on the first two vertices of every
   triangle but the batch's first; the normal with w = 1; the colour; 0, 0, 1, 0) and MSCNT; padding to a
   quadword and a DMA end tag. */
/* NOT MATCHING (registers only, see the note in the attempt): the hoisting of the three header constants, which
   used to be the obstacle, is reproduced by duplicating the statements behind the flag store in its three arms. */
#if 0
/* NOT MATCHING, but the code is now the original's in shape: 182 instructions against 182, and with register
   names masked only 4 of them differ (60 by name). Third cleanup:
   - The missing loop size is found without any filler. The three arms of the no-draw flag each hold the flag
     store AND the first three statements behind it (`f = (f32 *)p; f[0] = normal.x; f[1] = normal.y;`). The arms
     are merged again after register allocation, so nothing of it shows, but the batch loop is then long enough
     at the second loop pass that the three header constants (0x6C038000, 0x8001, 0x10000000) stay in the loop,
     as in the original, while 1, 1.0f and 0.02f are still hoisted. Two statements in the arms are too few
     (186 instructions), four give the same count with other differences, five are too many. (The dead `pad`
     arithmetic of the second cleanup is not needed and is gone.)
   - Header stores in this order (pkt[3] first of the last five), `pad = 4 - pad` directly, tag[0] written
     before tag[4]: unchanged from the second cleanup.
   Still different (all register choice except the last two):
   - the triangle loop: the original has the triangle base in v1, the vertex pointer in a0, k in t2, the k test
     in t3, i * 64 in t4, j in t5; here t1 / t3 / v1 / t5 / a0 / t4. A `tri` pointer with or without a walking
     vertex pointer changes the instruction count (186 / 184) and is worse.
   - the normal's three loads alternate f1 / f0 / f1 in the original, f0 / f1 / f0 here, and `f + 12` is computed
     one store earlier there.
   - `bnez` for the j < 18 test and `blez` in front of the padding loop where this has `bnezl` / `blezl`.
   Behaviour is the same. */
s32 ObjShadow_BuildPacket(u32 *pkt, s32 count, ObjShadowTri *tris, f32 *color);

#endif


/* Matrix that flattens geometry on the plane (x, y, z, w + bias) along the direction `light`
   (sceVu0DropShadowMatrix for a parallel light, with the light reversed). */
void ObjShadow_MakePlaneMtx(Mtx44 *out, Vec4 *plane, Vec4 *light, f32 bias);

/* Screen distance of a camera at distance |a - b| that makes a sphere of radius `size` fill `half` pixels. */
f32 ObjShadow_CalcScreenDist(Vec4 *a, Vec4 *b, f32 size, f32 half);

/* Non-zero when the object throws a ground shadow now: its flag is set and no stage job is running. */
s32 ObjShadow_IsEnabled(ObjMdlObj *obj);

/* Non-zero when the object has the flat shadow flag. */
s32 ObjShadow_IsFlat(ObjMdlObj *obj);

/* Points the GS at the 256x256 shadow page (0x150), clears it to black with alpha 0 and leaves it ready for
   untextured, blended drawing inside a one pixel border. */
void ObjShadow_AddTargetEnv(void) {
    u64 *p = Dma_BeginDirect();
    u64 *tag;
    s32 i;
    s32 x;

    p[0] = GIF_TAG(12, 0, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = GS_SET_SCISSOR(0, 0xFF, 0, 0xFF);
    p[1] = GS_SCISSOR_1;
    p += 2;
    p[0] = GS_SET_FRAME(0x150, 4, 0, 0);
    p[1] = GS_FRAME_1;
    p += 2;
    p[0] = GS_SET_ZBUF(0xE0, GS_PSMZ24, 1);
    p[1] = GS_ZBUF_1;
    p += 2;
    p[0] = GS_SET_XYOFFSET(0x7800, 0x7800);
    p[1] = GS_XYOFFSET_1;
    p += 2;
    p[0] = 5;
    p[1] = GS_CLAMP_1;
    p += 2;
    p[0] = 1;
    p[1] = GS_COLCLAMP;
    p += 2;
    p[0] = 0;
    p[1] = GS_FBA_1;
    p += 2;
    p[0] = 0x60;
    p[1] = GS_TEX1_1;
    p += 2;
    p[0] = 0x30000;
    p[1] = GS_TEST_1;
    p += 2;
    p[0] = ((u64)0x80 << 32) | 0x64;
    p[1] = GS_ALPHA_1;
    p += 2;
    p[0] = 6;
    p[1] = GS_PRIM;
    p += 2;
    p[0] = (u64)0x3F800000 << 32;
    p[1] = GS_RGBAQ;
    p += 2;
    tag = p;
    p += 2;
    x = 0;
    for (i = 0; i < 8; i++) {
        p[0] = ((x + 0x780) << 4) | (0x7800 << 16);
        p[1] = (s64)((x + 0x7A0) << 4) | ((u64)0x8800 << 16);
        p += 2;
        x += 32;
    }
    tag[0] = GIF_TAG_EX(8, 0, GIF_FLG_REGLIST, 2);
    tag[1] = 0x55;
    p[0] = GIF_TAG(4, 1, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = GS_SET_SCISSOR(1, 0xFE, 1, 0xFE);
    p[1] = GS_SCISSOR_1;
    p += 2;
    p[0] = 0x3F80000080808080;
    p[1] = GS_RGBAQ;
    p += 2;
    p[0] = 0;
    p[1] = GS_PRMODECONT;
    p += 2;
    p[0] = 0x48;
    p[1] = GS_PRMODE;
    p += 2;
    Dma_EndDirect(p);
}

/* Box to search for ground triangles: the object's bounds, widened in x and z. Returns 1 when the shadow is
   thrown straight down (split screen, or a body scale above 50) instead of along the light. */
s32 ObjShadow_GetBox(ColBoxE *out, ObjMdlObj *obj);

/* Picks the size of the shadow area and the texture scale from the body scale, and aims at the object. */
void ObjShadow_SetTarget(ObjMdlObj *obj, ObjShadowWork *work);

/* Puts the shadow camera 1000 above the target, looking straight down, and stores its view matrix. */
void ObjShadow_MakeLightMtx(ObjMdlObj *obj, ObjShadowWork *work);

/* Builds the world-to-shadow-texture matrix: a camera at the eye looking at the target, with a screen distance
   that makes the shadow area fill the 256x256 page (centre 2048, 2048). */
void ObjShadow_MakeProjMtx(ObjMdlObj *obj, ObjShadowWork *work);

/* Loads VU1 program 2 with the shadow camera's matrix times the flattening matrix (plane y = the target's
   height, along the shadow direction), sets the object's colour to 128 and queues its meshes. */
void ObjShadow_LoadProg(ObjMdlObj *obj, ObjShadowWork *work);

/* Takes a shadow from the pool for an object that has the shadow flag. */
void ObjShadow_Alloc(ObjMdlObj *obj);

/* Gives the object's shadow back to the pool. */
void ObjShadow_Free(ObjMdlObj *obj);

/* Restores the full-screen scissor and the renderer's normal state after the shadow passes. */
void ObjShadow_ResetEnv(void);

/* Once per frame (not while paused): collects the stage triangles under the object and the shadow's alpha,
   picks the shadow direction and flips the packet buffer. */
void ObjShadow_Update(ObjMdlObj *obj);

/* First shadow pass of an object: draws its silhouette from above into the shadow page. */
void ObjShadow_BeginRender(ObjMdlObj *obj);

/* Second shadow pass: draws the collected ground triangles in the view, textured with the shadow page. */
void ObjShadow_Draw(ObjMdlObj *obj, ObjShadowCam *view);

/* Flat shadow: draws the object's meshes squashed on the plane y = 0 along the light, in the light's colour. */
void ObjShadow_BeginFlat(ObjMdlObj *obj);

/* Clears the shadow pool and gives each of its five shadows a work block and two packet buffers. */
void ObjShadow_InitPool(void);

/* Frees the buffers of the shadow pool. */
void ObjShadow_TermPool(void);
