#include "common.h"
/*
 * The battle object renderer (0x1101D0..0x112A30): one object in one view. Called from the per-view loops of
 * gfxm_d_b.c; ObjDraw_DrawPartsFlat is called by the shadow code (ObjShadow_LoadProg / ObjShadow_BeginFlat).
 *
 * BtlObjDraw_DrawModel, in order:
 *   ObjDraw_UploadTextures   the model's own textures every frame (the face texture replaced by the current
 *                            expression), then the CLUT range for the object's colour flag
 *   ObjDraw_AddClutPass      draws INTO the model's CLUT (64x64 frame at block model->cbp): dimming, distance fade
 *                            colour, tint and hit flash are blended over the palette, not over the pixels
 *   ObjDraw_SetLight         light direction for the view from the colour flags (battle light, camera, rim light)
 *   ObjSeam_Transform        CPU skinning of the seam vertices (VU0 routine ObjSeam_TransformVtx in front of this file)
 *   ObjDraw_DrawParts(0)     one VU1 packet per visible part (program 0), the head (node 0x33) last
 *   ObjSeam_Draw             the seam triangles: base texture, then the shading ramp through GS context 2
 * BtlObjDraw_DrawModelFade draws the parts with flag 1 again through VU1 program 1 with the fade texture.
 * The ObjGs_* functions at the end queue fixed register packets (same family as the ones in gfxm_e.c).
 *
 * ObjSeam_TransformVtx(vtx, work, mtx, ofs) (0x10FFD0, VU0 macro code, stays assembly):
 *   lightA = work->light * mtx[0], lightB = work->light * mtx[1] (stored in work);
 *   n = lerp(lightB * normal, lightA * normal, pos.w); shade u = n.x * 0.5 + 0.5 (work->k.w);
 *   p = lerp(mtx[1] * (pos - ofs[1]), mtx[0] * (pos - ofs[0]), pos.w), projected with the screen matrix in vf24-27;
 *   vtx->xyz = ftoi4(p / p.w) with w = 0x8000 when x or y leaves 0..4096 (vf19); vtx->stBase = uv / p.w;
 *   vtx->stShade = (u, 0, 1) / p.w.
 */
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/gfxm_d_c.h"
#include "battle/btl_cam.h"

extern void Vec4_Copy(Vec4 *dst, Vec4 *src);
extern void Vec4_Add(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec4_Sub(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Cross(Vec4 *dst, Vec4 *a, Vec4 *b);
extern void Vec3_Normalize(Vec4 *dst, Vec4 *src);
extern void Vec3_Scale(Vec4 *dst, Vec4 *src, f32 s);
extern void Mtx_StoreIdentity(Mtx44 *m);
extern void Mtx_Copy(Mtx44 *dst, Mtx44 *src);
extern void Mtx_Mul(Mtx44 *dst, Mtx44 *a, Mtx44 *b);
extern void Mtx_InverseRT(Mtx44 *dst, Mtx44 *src);
extern void Mtx_MakeNormalLight(Mtx44 *dst, Vec4 *l0, Vec4 *l1, Vec4 *l2);
extern void Vu0_InitAxisRegs(void);
extern void Vu0Screen_StoreMtx(Mtx44 *dst);
extern void Vu0Clip_StoreMtx(Mtx44 *dst);
extern ObjDrawPkt *Vu1Pkt_CallProg0(u8 *chain);
extern ObjDrawPkt *Vu1Pkt_LoadProg0(void);
extern ObjDrawPkt *Vu1Pkt_CallProg1(ObjDrawPart *part);
extern ObjDrawPkt *Vu1Pkt_LoadProg1(void);
extern ObjDrawPkt *Vu1Pkt_CallProg2(ObjDrawPart *part);
extern ObjDrawNode *BtlObj_GetNode(ObjDrawObj *obj, s32 node);
extern ObjDrawPart *BtlObj_FindBound(ObjDrawObj *obj, s32 node);
extern s32 BtlObj_GetSubState(ObjDrawObj *obj);
extern TexEntry *BtlObj_GetFaceTexture(ObjDrawObj *obj);
extern void BtlObjLight_GetDir(Vec4 *out);
extern void BtlObjLight_FindRes1(s32 key);
extern s32 BtlObjFade_Get(ObjDrawObj *obj, f32 *out);
extern s32 BtlObjFlash_GetColor(ObjDrawObj *obj, Vec4 *color, f32 *alpha);
extern void ObjGs_AddFrameMaskOpaque(u32 fbmsk);
extern void ObjGs_AddFrameMaskBlend(u32 fbmsk);
extern void Dma_AddTexFlush(void);
extern void Dma_AddZbuf(s32 zbp, s32 zmsk);
/* The VU0 routine in front of this file (0x10FFD0): skins and projects one seam vertex. */
extern void ObjSeam_TransformVtx(ObjSeamVtx *vtx, ObjSeamWork *work, Mtx44 *mtx, Vec4 *ofs);

extern Vec4 D_002EC2C0; /* zero vector */
extern Vec4 D_002C3440; /* 128, 128, 128, 128 */

#define OBJ_FLAG_BITS(p) ((ObjDrawFlagBits *)&(p)->flags)
/* FRAME value for the colour buffer being drawn, with a write mask. */
#define OBJ_FRAME_REG(fbmsk) GS_SET_FRAME((gGfx.frame & 1) ? GFX_FBP_A : GFX_FBP_B, GFX_FBW, 0, fbmsk)
#define OBJ_SPRITE_TAG 0x2400000000000001 /* REGLIST, one loop of two registers */


/* Queues the default environment of the objects' pass for both GS contexts: frame, depth buffer, offset, the
   current view's scissor, blending, tests, texture filter, clamp. */
void BtlObjDraw_SetEnv(void) {
    u32 pkt[88] = {
        DMA_TAG_CNT | 21, 0, VIF_FLUSHE, VIF_DIRECT | 21,
        GIF_EOP | 20, 0x10000000, GIF_REG_AD, 0,
        GFX_FRAME_REG(), 0, GS_FRAME_1, 0,
        GFX_FRAME_REG(), 0, GS_FRAME_2, 0,
        GS_SET_ZBUF(GFX_ZBP, GS_PSMZ24, 0), 0, GS_ZBUF_1, 0,
        GS_SET_ZBUF(GFX_ZBP, GS_PSMZ24, 0), 0, GS_ZBUF_2, 0,
        GFX_OFX, GFX_OFY, GS_XYOFFSET_1, 0,
        GFX_OFX, GFX_OFY, GS_XYOFFSET_2, 0,
        GS_SET_SCISSOR(gBtlCamView->scissorX0, gBtlCamView->scissorX1, gBtlCamView->scissorY0, gBtlCamView->scissorY1),
        GS_SET_SCISSOR(gBtlCamView->scissorX0, gBtlCamView->scissorX1, gBtlCamView->scissorY0, gBtlCamView->scissorY1) >> 32,
        GS_SCISSOR_1, 0,
        GS_SET_SCISSOR(gBtlCamView->scissorX0, gBtlCamView->scissorX1, gBtlCamView->scissorY0, gBtlCamView->scissorY1),
        GS_SET_SCISSOR(gBtlCamView->scissorX0, gBtlCamView->scissorX1, gBtlCamView->scissorY0, gBtlCamView->scissorY1) >> 32,
        GS_SCISSOR_2, 0,
        0x44, 0, GS_ALPHA_1, 0,
        0x44, 0, GS_ALPHA_2, 0,
        0x50000, 0, GS_TEST_1, 0,
        0x50000, 0, GS_TEST_2, 0,
        0x60, 0, GS_TEX1_1, 0,
        0x60, 0, 0x15, 0,
        0, 0, GS_FBA_1, 0,
        0, 0, GS_FBA_2, 0,
        0, 0, GS_CLAMP_1, 0,
        0, 0, GS_CLAMP_2, 0,
        1, 0, GS_COLCLAMP, 0,
        1, 0, GS_PRMODECONT, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Queues the texturing state of the lit draw: blend, tests, bilinear filter, clamp of context 2. */
void ObjGs_AddTexEnv(void) {
    u32 pkt[48] = {
        DMA_TAG_CNT | 11, 0, VIF_FLUSHE, VIF_DIRECT | 11,
        GIF_EOP | 10, 0x10000000, GIF_REG_AD, 0,
        0x64, 0x80, GS_ALPHA_1, 0,
        0x50000, 0, GS_TEST_1, 0,
        0, 0, GS_FBA_1, 0,
        0x60, 0, GS_TEX1_1, 0,
        0, 0, GS_CLAMP_1, 0,
        0x50000, 0, GS_TEST_2, 0,
        0x60, 0, 0x15, 0,
        5, 0, GS_CLAMP_2, 0,
        1, 0, GS_COLCLAMP, 0,
        0, 0, GS_FBA_2, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}
