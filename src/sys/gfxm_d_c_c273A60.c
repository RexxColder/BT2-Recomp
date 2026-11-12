#define Mtx_StoreIdentity sceVu0UnitMatrix  /* fix_targets */ /* the original uses 0x312740 here */
#define Vec3_Cross func_00312490  /* fix_targets */ /* the original uses 0x312490 here */
#define Vec3_Normalize sceVu0Normalize  /* fix_targets */ /* the original uses 0x3124d8 here */
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

/* Skins and projects the vertices of the model's seam section for the current view. */
void ObjSeam_Transform(ObjDrawObj *obj, ObjDrawView *view);

/* Draws the seam triangles twice: base texture in the view's colour, then the shading ramp through context 2. */
void ObjSeam_Draw(ObjDrawObj *obj, ObjDrawState *state, ObjDrawView *view);

/* Builds the rotation whose third row is `dir` and whose other rows are perpendicular to it and to the vertical. */
void func_00273A60(Mtx44 *m, Vec4 *dir) {
    ObjDrawVec up = { 0.0f, -1.0f, 0.0f, 1.0f };
    Vec4 side;

    Vec3_Cross(&side, dir, (Vec4 *)&up);
    Vec3_Normalize(&side, &side);
    Vec3_Cross((Vec4 *)&up, &side, dir);
    Vec3_Normalize((Vec4 *)&up, (Vec4 *)&up);
    Mtx_StoreIdentity(m);
    m->m[0][0] = side.x;
    m->m[1][0] = up.x;
    m->m[2][0] = dir->x;
    m->m[0][1] = side.y;
    m->m[1][1] = up.y;
    m->m[2][1] = dir->y;
    m->m[0][2] = side.z;
    m->m[1][2] = up.z;
    m->m[2][2] = dir->z;
}

/* Queues the model's per-frame texture uploads: its own textures one by one (the face texture replaced by the
   current expression), then the CLUT range that matches the object's colour flag. */
void ObjDraw_UploadTextures(ObjDrawObj *obj);

/* Alpha of the dimming sprite: 0xF4 plus byte 3 of the character parameter block (inlined in the original). */
static inline s32 ObjDraw_GetDimAlpha(ObjDrawMdl *mdl);

/* Draws into the model's CLUT (a 64-pixel wide frame at block `cbp`): sets the state for the pass, then blends
   up to four 64x64 sprites over the palette: the dimming alpha, the fade colour, the object's tint, the flash. */
void ObjDraw_AddClutPass(ObjDrawObj *obj, ObjDrawState *state, ObjDrawView *view, s32 dim);

/* Queues the VU1 packets of the model's parts. mode 0: lit draw (program 0; the head, node 0x33, last and
   between two frame-mask packets unless `noMask`), 1: fade pass (program 1, parts with flag 1, texture `tex0`),
   2: flat draw (program 2). */
void ObjDraw_DrawParts(ObjDrawObj *obj, ObjDrawView *view, s32 mode, u64 tex0, u32 fbmsk, s32 noMask);

/* Chooses the light direction of the object in this view (stored in view->lightDir) from its colour flags and
   queues the frame / alpha / depth registers of the lit draw. Returns the frame mask for the head (0 or alpha). */
u32 ObjDraw_SetLight(ObjDrawObj *obj, ObjDrawView *view);

/* Draws one object in the current view: texture uploads, the CLUT pass, the lit model and its seams. */
void BtlObjDraw_DrawModel(ObjDrawObj *obj);

/* Draws the distance-fade layer of one object: its fade texture over the parts that have flag 1. */
void BtlObjDraw_DrawModelFade(ObjDrawObj *obj);

/* Queues the parts with VU1 program 2 (flat, for the shadow render). */
void ObjDraw_DrawPartsFlat(ObjDrawObj *obj);

/* End of the objects' pass: restores the default environment. */
void BtlObjDraw_End(void);

/* Queues the default environment of the objects' pass for both GS contexts: frame, depth buffer, offset, the
   current view's scissor, blending, tests, texture filter, clamp. */
void BtlObjDraw_SetEnv(void);

/* Queues the texturing state of the lit draw: blend, tests, bilinear filter, clamp of context 2. */
void ObjGs_AddTexEnv(void);

/* Queues FRAME_1 (current colour buffer, write mask `fbmsk`) with the blend, test and FBA of context 1. */
void ObjGs_AddFrame1(u32 fbmsk, s32 unused);

/* Queues ALPHA_2 = `alpha` and FRAME_2 (current colour buffer, write mask `fbmsk`). */
void ObjGs_AddFrame2Alpha(u32 fbmsk, u64 alpha);

/* Queues the environment of the fade pass: as BtlObjDraw_SetEnv, but context 1 writes alpha only (FBMSK
   0x00FFFFFF) and context 2 blends with ALPHA 0x58 and clamps. */
void ObjGs_AddFadeEnv(void);

/* Queues TEST_1 with alpha reference `aref` (pass when greater), TEX0_2 = `tex0`, TEXFLUSH. */
void ObjGs_AddFadeTex(u64 tex0, s32 aref);

/* Queues ZBUF_1 and ZBUF_2: depth buffer page (24-bit) and the "do not write depth" flag. */
void ObjGs_AddZbufBoth(s32 zbp, s32 zmsk);
