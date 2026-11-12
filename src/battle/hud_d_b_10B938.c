#include "common.h"
#include "battle/hud_d.h"
#include "sys/dma.h"
#include "sys/gfx.h"
#include "sys/mathf.h"
#include "sys/randf.h"

/*
 * Battle HUD, notice part: the animations of the full-screen announcements, 0x226500-0x22A750.
 * The part's init, term, reset and its starter HudNotice_Show(id) (0x22AB50) follow at 0x22A750 (src/battle/hud_e.c);
 * the starter hides the sprites, clears `state`, puts node 1 at (256, 224) and gives it one of the update / draw
 * pairs below, then plays the announcer's line. Ids: 0 UpdateReady, 1 UpdateFight, 2 UpdateKo, 3 UpdateBandA,
 * 4 UpdateSpinA, 5 UpdateSpinB (both drawn by DrawSpin), 6 UpdateTrail, 7 the banner of hud_e.c, 8 UpdateBandB.
 * Each update is a state machine on gHudNotice->state; its last state hides everything and stays.
 * Nothing here looks at the pause flag, the pad, the clock or the camera: an announcement keeps animating while
 * the battle is paused. The only random draws are the streak's shake (Rand_IntRange = libc rand(), one per frame
 * in one state of UpdateFight, UpdateKo and UpdateTrail).
 */

typedef f32 HudDMtx[4][4];

/* Offset of the streak: fractions of its size (float), or pixels (the shake). */
typedef union HudNoticeVec {
    f32 f[2];
    s32 i[2];
} HudNoticeVec;

/* Index of trail[0] counted in floats from offset 4 of the work (see HudNotice_UpdateKo). */
#define HUDN_TRAIL_AT4 16

#define HUDN_CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((hi) < (v) ? (hi) : (v)))
#define HUDN_CLAMP01(v) HUDN_CLAMP(v, 0.0f, 1.0f)

/* Sprite library (0x224B50..0x226488, src/battle/hud_c_c.c; names from config/symbols/hud_c.txt). */
extern void HudGfx_CallBegin(void (*fn)(void)); /* 0x224B50: calls a GS state function before masked sprites */
extern void HudGfx_CallEnd(void (*fn)(void));   /* 0x224B70: and after them */
extern void HudSprite_Show(HudDSprite *spr, s32 show);
extern void HudSprite_SetRect(HudDSprite *spr, s32 x0, s32 x1, s32 y0, s32 y1); /* screen rectangle */
extern void HudSprite_SetUv(HudDSprite *spr, s32 u0, s32 u1, s32 v0, s32 v1); /* texel rectangle */
extern void HudSprite_SetColor(HudDSprite *spr, s32 r, s32 g, s32 b, s32 a);
extern void HudSprite_InitPlain(HudDSprite *spr, s32 r, s32 g, s32 b, s32 a);     /* untextured, coloured */
extern void HudSprite_Move(HudDSprite *spr, s32 dx, s32 dy);                 /* moves the rectangle */
extern void HudSprite_Scale(HudDSprite *spr, f32 sx, f32 sy);                 /* scales the rectangle about its centre */
extern void HudSprite_Center(HudDSprite *spr);                                 /* centres the rectangle on the node */
extern void HudSprite_InitTex(HudDSprite *spr, void *res, s32 tex, s32 sub);    /* sprite of a sheet's texture */
extern void HudGfx_ClearAlpha(void);
extern void *memset(void *dst, s32 c, s32 n); /* not the built-in: the original calls it for 8 bytes */
extern f32 powf(f32 x, f32 y);
extern void Mtx_StoreIdentity(HudDMtx m);
extern void Mtx_RotateZ(HudDMtx dst, HudDMtx src, f32 angle);
extern void Vu0Cur_Push(void);
extern void Vu0Cur_Pop(void);
extern void Vu0Cur_MulMtx(HudDMtx m);

/* GS state for the glowing word: TEST_1 = 0x3301B, FRAME_2 with the alpha plane write-protected, ALPHA_2 = 0x58
   (source added to the frame buffer). */
void HudNotice_GsBeginAdd(void) {
    u32 pkt[20] = {
        DMA_TAG_CNT | 4, 0, VIF_FLUSHE, VIF_DIRECT | 4,
        GIF_EOP | 3, 0x10000000, GIF_REG_AD, 0,
        0x3301B, 0, GS_TEST_1, 0,
        GFX_FRAME_REG(), 0xFF000000, GS_FRAME_2, 0,
        0x58, 0, GS_ALPHA_2, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Leaves it: TEST_1 = 0x30000, FRAME_2 without mask, ALPHA_2 = 0x44. */
void HudNotice_GsEndAdd(void) {
    u32 pkt[20] = {
        DMA_TAG_CNT | 4, 0, VIF_FLUSHE, VIF_DIRECT | 4,
        GIF_EOP | 3, 0x10000000, GIF_REG_AD, 0,
        0x30000, 0, GS_TEST_1, 0,
        GFX_FRAME_REG(), 0, GS_FRAME_2, 0,
        0x44, 0, GS_ALPHA_2, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* The same as HudNotice_GsBeginAdd, and FRAME_1 writes only alpha. */
void HudNotice_GsBeginAddAlpha(void);

/* Leaves it. */
void HudNotice_GsEndAddAlpha(void);

/* GS state for drawing a mask into the alpha plane: FBA_1 on, FRAME_1 writes only alpha, TEST_2 = 0x3C000
   (destination alpha test), FRAME_2 without mask. */
void HudNotice_GsBeginMask(void);

/* Leaves it: FBA_1 off, FRAME_1 without mask, TEST_2 = 0x30000. */
void HudNotice_GsEndMask(void);

/* Draw callback: all sprites of the node, plain. */
void HudNotice_DrawNode(HudDNode *node);

/* Draw callback of announcements 4 and 5: sprites 0..13 under the additive state, the streak with the other
   blend. */
void HudNotice_DrawSpin(void);

/* Draw callback of announcement 0: the band (rotated by node 2's angle) is the mask of the word; the twelve
   fragments are drawn plain on top. */
void HudNotice_DrawReady(void);

/* Update of announcement 0. The band grows from a 32 x 4 line to 512 wide (0.2 s), then to 128 high while it
   turns half a turn backwards (0.36 s); after 1.1 s the word and the band swell and fade (0.43 s, cubic) while
   the twelve fragments fly outwards and fade one after another. */
void HudNotice_UpdateReady(void);

/* Draw callback of announcement 1: the word masked by the band, the twelve fragments, then the word and the
   streak added on top. */
void HudNotice_DrawFight(void);

/* Update of announcement 1. The reverse of announcement 0's ending: the word shrinks into place and fades in
   while the fragments fly in (0.43 s, cubic); it stands for 0.4 + 0.45 + 0.2 + 0.2 s, then the band closes
   (0.2 s). During the three middle waits a streak (texture 7, three frames of 42 rows) crosses the word:
   sliding in from the left, shaking by a random -16..16 pixels, sliding out to the right while fading. */
void HudNotice_UpdateFight(void);

/* Draw callback of announcement 2: as HudNotice_DrawFight with four sprites behind the word. */
void HudNotice_DrawKo(void);

/* Update of announcement 2. The word pops: its scale is 1 + 0.4 * sin(pi * v) with v going 0 -> 0.5 in 0.15 s
   and 0.5 -> 1 in 0.4 s, its alpha min(128, 256 * v); three after-images (sprites 2..4, alpha at most 48) repeat
   the scale of the last three frames and are hidden once they have caught up. Then waits of 0.2 / 0.55 / 0.4 /
   0.2 s (the streak crosses during the middle three, in red) and the band closes. */
void HudNotice_UpdateKo(void);

/* Draw callback of announcement 3: the word masked by the band, its copy plain on top. */
void HudNotice_DrawBandA(void);

/* Update of announcement 3 (texture 3, rows 64..128, 512 x 64 on screen). A 4-pixel line slides in from the
   left (0.24 s) and opens to 64 pixels (0.24 s); after 0.25 s a copy of the word swells and fades over it
   (0.64 s, cubic); 0.6 s later the band closes to the line (0.24 s), which slides out to the right (0.24 s).
   State 4 starts ramp B but state 5 steps ramp A, which has ended: the 0.6 s wait does not happen. */
void HudNotice_UpdateBandA(void);

/* Draw callback of announcement 8: the word masked by the band, its copy plain on top. */
void HudNotice_DrawBandB(void);

/* Update of announcement 8 (texture 3, rows 0..64, 512 x 64 on screen). A 4-pixel line slides in from the
   left (0.24 s) and opens to 64 pixels (0.24 s); after 0.25 s a copy of the word swells and fades over it
   (0.64 s, cubic); 0.6 s later the band closes to the line (0.24 s), which slides out to the right (0.24 s).
   State 4 starts ramp B but state 5 steps ramp A, which has ended: the 0.6 s wait does not happen. */
void HudNotice_UpdateBandB(void);

/* Update of announcement 4 (texture 4, rows 0..64). The word shrinks from double size to its own while it
   fades in and turns one and a half turns (0.83 s, cubic; the angle is brought into -pi..pi); it stands for 1 s
   and 0.23 s and then swells to double size and fades out (0.23 s). The angle goes to the node, which is the
   update callback's argument. */
void HudNotice_UpdateSpinA(HudDNode *node);

/* Update of announcement 5 (texture 4, rows 64..128). The word shrinks from double size to its own while it
   fades in and turns one and a half turns (0.83 s, cubic; the angle is brought into -pi..pi); it stands for 1 s
   and 0.23 s and then swells to double size and fades out (0.23 s). The angle goes to the node, which is the
   update callback's argument. */
void HudNotice_UpdateSpinB(HudDNode *node);

/* Draw callback of announcement 6: the word and its eight copies plain, then the word and the streak added. */
void HudNotice_DrawTrail(void);

/* Update of announcement 6 (texture 5). Eight copies of the word zoom in one frame behind each other: copy i
   shows the ramp value of i frames ago (v: 1 -> 0 in 0.93 s; scale 2 - (1 - v)^3, alpha 128 * (1 - v)^3) and is
   hidden when it has caught up with copy 0. When all have arrived the word itself replaces them; waits of 0.35 /
   0.8 / 0.35 / 0.3 s (the streak crosses during the middle three), then the word swells by 0.3 and fades
   (0.3 s, cubic). */
void HudNotice_UpdateTrail(void);
