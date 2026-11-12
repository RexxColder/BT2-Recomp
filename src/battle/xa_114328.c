#include "common.h"
/* BT2 targets of these calls / globals (checked against the original relocations). */
#define Dma_EndDirect func_0028B1C0
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
void HudGfx_ClearAlpha(void) {
    u64 *p = Dma_BeginDirect();
    s32 i;
    s32 n;
    u64 *tag;

    p[0] = GIF_TAG(3, 0, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = GFX_CLEAR_RGBAQ;
    p[1] = GS_RGBAQ;
    p += 2;
    p[0] = GS_SET_ZBUF(GFX_ZBP, GS_PSMZ24, 0);
    p[1] = GS_ZBUF_1;
    p += 2;
    p[0] = 0x46; /* sprite, alpha blended */
    p[1] = GS_PRIM;
    p += 2;
    tag = p;
    p += 2;
    i = 0;
    for (n = 0; n < 16; n++) {
        p[0] = ((i * 32 + 1792) << 4) | ((1824 << 4) << 16);
        p[1] = GS_SET_XYZ((i * 32 + 1792 + 32) << 4, (1824 + 448) << 4, 0);
        p += 2;
        i++;
    }
    tag[0] = GIF_TAG_EX(16, 1, GIF_FLG_REGLIST, 2);
    tag[1] = GS_REG_XYZ2 | (GS_REG_XYZ2 << 4);
    p[0] = GIF_TAG(2, 0, 1);
    p[1] = GIF_REG_AD;
    p += 2;
    p[0] = 0x3F80000080808080;
    p[1] = GS_RGBAQ;
    p += 2;
    p[0] = GS_SET_ZBUF(GFX_ZBP, GS_PSMZ24, 1);
    p[1] = GS_ZBUF_1;
    p += 2;
    Dma_EndDirect(p);
}

#define HUDC_FRAME_WORD() (!(gGfx.frame & 1) ? 0x80070 : 0x80000)

/* Queues the HUD's drawing state, the same for GS contexts 1 and 2: the frame's colour buffer, the depth buffer
   with writes off, the full-screen offset and scissor, source alpha blending, tests that always pass, bilinear
   filtering, no FBA, repeating textures, colour clamp and PRMODECONT. Called at the top of Hud_Draw. */
void HudGfx_SetEnv(void);

/* Draws a sprite as a four-vertex triangle strip under the current VU0 matrix. A textured sprite uploads its
   texture (HudRes_UploadTex with tbp / cbp) and sets TEX0 of both GS contexts; `ctx2` draws through context 2. */
void HudSprite_DrawAt(HudCSprite *spr, HudCRes *res, u8 ctx2, s32 tbp, s32 cbp);

#define HUDC_RGBA(c) \
    ((u64)(((c) >> 24) & 0xFF) | ((u64)(((c) >> 16) & 0xFF) << 8) | ((u64)(((c) >> 8) & 0xFF) << 16) | \
     ((u64)((c) & 0xFF) << 24))

/* Draws a sprite like HudSprite_DrawAt (textures at HUDC_GRADIENT_TBP / CBP), but with a colour per vertex instead
   of the sprite's own: colorL on the two left corners, colorR on the two right ones, each 0xRRGGBBAA. */
void HudSprite_DrawGradient(HudCSprite *spr, HudCRes *res, u8 ctx2, s32 colorL, s32 colorR);
