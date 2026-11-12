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
extern void Mtx_MakeCamera(Mtx44 *m, Vec4 *pos, Vec4 *zdir, Vec4 *ydir);
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
