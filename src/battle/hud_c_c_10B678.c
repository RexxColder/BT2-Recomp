#include "common.h"
#include "battle/hud_c.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/sprite.h"

/*
 * Battle HUD: the sprite library, 0x224B50-0x226488 (it ends with HudSprite_Draw and the node setters of
 * src/battle/hud_d.c, 0x226488-0x226500).
 *
 * A HudCSprite is a rectangle in the coordinates of its node. Drawing transforms the four corners by the current
 * VU0 matrix (HudNode_Draw has multiplied the node's translation, rotation and mirror into it), so a sprite is
 * sent as a four-vertex triangle strip, not as a GS sprite. Screen coordinates are pixels of the 512x448 frame;
 * the GS coordinate is (x + 1792) * 16, (y + 1824) * 16. Texture coordinates are texels (sent as texel * 16 + 8).
 *
 * Textures are uploaded on first use in a frame: the image to block `tbp + imageBlock`, the palette to
 * `cbp + clutBlock` (HudSprite_Draw passes 0x2A00 / 0x2C80), and HudCTex.mark keeps a second upload away until
 * Hud_ClearTexMarks.
 *
 * Nothing here reads the pad, the clock or the camera; HudGfx_SetEnv reads the frame counter's parity to pick the
 * colour buffer. No random numbers.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern void Vu0Cur_MulVec4(f32 *out, f32 *v);

#define HUDC_BITBLTBUF(block, width) (((s64)(block) << 32) | ((u64)(width) << 48))

/* Calls fn(0). The HUD parts pass the function that queues a GS state (e.g. HudGauge_GsBeginMask) in front of a
   group of sprites. */
void HudGfx_CallBegin(void (*fn)(s32));

/* The same; the parts pass the function that restores the state after the group. */
void HudGfx_CallEnd(void (*fn)(s32));

/* Shows or hides a sprite. */
void HudSprite_Show(HudCSprite *spr, s32 show);

/* Sets whether the sprite's texture is mirrored left to right. */
void HudSprite_SetMirror(HudCSprite *spr, s32 mirror);

/* Sets the rectangle (relative to the node). */
void HudSprite_SetRect(HudCSprite *spr, s32 x0, s32 x1, s32 y0, s32 y1);

/* Sets the texel rectangle. */
void HudSprite_SetUv(HudCSprite *spr, s32 u0, s32 u1, s32 v0, s32 v1);

/* Sets the texture entry and the offset of the entry that supplies the palette. */
void HudSprite_SetTex(HudCSprite *spr, s32 tex, s32 sub);

/* Sets the colour (0x80 = neutral). */
void HudSprite_SetColor(HudCSprite *spr, s32 r, s32 g, s32 b, s32 a);

/* Makes the sprite an untextured rectangle of the given colour. */
void HudSprite_InitPlain(HudCSprite *spr, u8 r, u8 g, u8 b, u8 a);

/* Moves the rectangle. */
void HudSprite_Move(HudCSprite *spr, s32 dx, s32 dy);

/* Moves the texel rectangle. */
void HudSprite_MoveUv(HudCSprite *spr, s32 du, s32 dv);

/* Exchanges u0 and u1. */
void HudSprite_FlipU(HudCSprite *spr);

/* Exchanges v0 and v1. */
void HudSprite_FlipV(HudCSprite *spr);

/* Scales the rectangle about the node's origin. */
void HudSprite_Scale(HudCSprite *spr, f32 sx, f32 sy);

/* Moves the rectangle so that its centre is the node's origin. */
void HudSprite_Center(HudCSprite *spr);

/* Makes the sprite show the whole of texture `tex` of a sheet: rectangle and texel rectangle (0, w, 0, h) from the
   texture's size in TEX0, neutral colour. */
void HudSprite_InitTex(HudCSprite *spr, HudCRes *res, s32 tex, s32 sub);

/* Queues the upload of texture `tex` (image to block tbp + imageBlock, palette to cbp + clutBlock) and of the
   palette of texture `tex + sub`, each only if it has not been uploaded this frame. The palette of `tex + sub`
   goes to the block and width of its own entry but with the palette WIDTH of entry `tex`. */
void HudRes_UploadTex(HudCRes *res, s32 tex, s32 sub, s32 tbp, s32 cbp);

#define HUDC_XYZ(v) \
    ((((s32)(v)[0] << 4) + SPRITE_OFS_X) | ((u64)(((s32)(v)[1] << 4) + SPRITE_OFS_Y) << 16))
#define HUDC_XYZ_CONV(v) \
    ((((s32)(v)[0] << 4) + SPRITE_OFS_X) | ((u64)((Sprite_ConvY((s32)(v)[1]) << 4) + SPRITE_OFS_Y) << 16))

/* Draws the sprite's rectangle with colour 0, alpha 0 (source alpha blend, no texture, no tests): with the
   blend equation in force this leaves the picture and clears the destination alpha, which the gauge part uses as
   a mask. */
void HudSprite_DrawAlphaClear(HudCSprite *spr);

/* The same with alpha 0xFF. */
void HudSprite_DrawAlphaSet(HudCSprite *spr);

/* Fills the frame with colour 0, alpha 0 in 16 strips of 32 x 448 (blended sprites, depth writes on), then sets
   the neutral colour and turns depth writes off. Hud_Draw calls it in front of each side's gauges. */
void HudGfx_ClearAlpha(void);

#define HUDC_FRAME_WORD() (!(gGfx.frame & 1) ? 0x80070 : 0x80000)

/* Queues the HUD's drawing state, the same for GS contexts 1 and 2: the frame's colour buffer, the depth buffer
   with writes off, the full-screen offset and scissor, source alpha blending, tests that always pass, bilinear
   filtering, no FBA, repeating textures, colour clamp and PRMODECONT. Called at the top of Hud_Draw. */
void HudGfx_SetEnv(void) {
    u32 pkt[88] = {
        0x10000015, 0, 0x10000000, 0x50000015,
        0x00008014, 0x10000000, GIF_REG_AD, 0,
        HUDC_FRAME_WORD(), 0, GS_FRAME_1, 0,
        HUDC_FRAME_WORD(), 0, GS_FRAME_2, 0,
        0x310000E0, 1, GS_ZBUF_1, 0,
        0x310000E0, 1, GS_ZBUF_2, 0,
        GFX_OFX, GFX_OFY, GS_XYOFFSET_1, 0,
        GFX_OFX, GFX_OFY, GS_XYOFFSET_2, 0,
        0x01FF0000, 0x01BF0000, GS_SCISSOR_1, 0,
        0x01FF0000, 0x01BF0000, GS_SCISSOR_2, 0,
        0x44, 0, GS_ALPHA_1, 0,
        0x44, 0, GS_ALPHA_2, 0,
        0x30000, 0, GS_TEST_1, 0,
        0x30000, 0, GS_TEST_2, 0,
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

/* Draws a sprite as a four-vertex triangle strip under the current VU0 matrix. A textured sprite uploads its
   texture (HudRes_UploadTex with tbp / cbp) and sets TEX0 of both GS contexts; `ctx2` draws through context 2. */
void HudSprite_DrawAt(HudCSprite *spr, HudCRes *res, u8 ctx2, s32 tbp, s32 cbp);

#define HUDC_RGBA(c) \
    ((u64)(((c) >> 24) & 0xFF) | ((u64)(((c) >> 16) & 0xFF) << 8) | ((u64)(((c) >> 8) & 0xFF) << 16) | \
     ((u64)((c) & 0xFF) << 24))

/* Draws a sprite like HudSprite_DrawAt (textures at HUDC_GRADIENT_TBP / CBP), but with a colour per vertex instead
   of the sprite's own: colorL on the two left corners, colorR on the two right ones, each 0xRRGGBBAA. */
void HudSprite_DrawGradient(HudCSprite *spr, HudCRes *res, u8 ctx2, s32 colorL, s32 colorR);
