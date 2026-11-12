#include "common.h"
#include "battle/hud_a.h"
#include "battle/battle.h"
#include "sys/heap.h"
#include "sys/dma.h"
#include "sys/gfx.h"

/*
 * HUD team panel. Source range 0x219EB0-0x21BCA0.
 *
 * Shows, for each side that has members in reserve, the face of the member that a switch would bring in, that
 * member's health bar and the switch gauge. One set of nodes and sprites serves both sides: Hud_Draw calls
 * HudTeam_SelectSide(side) and then updates / draws the tree, mirrored for side 1.
 *
 * Node tree (gHudTeam->nodes[]):
 *   0 root (12, 66)            update HudTeam_UpdateRoot (slide, flip)
 *     1 current face group     pos = flipA
 *       3 face A (14, 0)       sprites 0 (frame), 8 (face of target[0])
 *         5 health bar A       sprites 1 (bar), 3 (mask)
 *         7 switch gauge       sprites 5 (bar), 6 (mask), 7 ("full" marker)
 *       8 plate                sprites 10, 11
 *     2 previous face group    pos = flipB; shown until its flip ends
 *       4 face B (14, 0)       sprites 0, 9 (face of target[1])
 *         6 health bar B       sprites 2, 4
 *         7 switch gauge
 *       8 plate
 */

/* Local view of BattleMember: the member's face sprite sheet. */
typedef struct HudTeamMember {
    /* 0x00 */ u8 unk0[0x58];
    /* 0x58 */ HudRes *faceRes;
} HudTeamMember;

extern void *memset(void *dst, s32 c, u32 n);
extern HudTeamMember *BattleSide_GetMember(s32 side, s32 idx);

/* The team panel work. Defined here: this object's .sdata (0x2FEB40). */
extern HudTeam *gHudTeam;

/* Sprite / node helpers (0x224B50..0x2264C8, not decompiled yet). */
extern void HudGfx_CallBegin(void (*gsBegin)(void));     /* calls it */
extern void HudGfx_CallEnd(void (*gsEnd)(void));       /* calls it */
extern void HudSprite_Show(HudSprite *spr, s32 show);
extern void HudSprite_SetMirror(HudSprite *spr, s32 mirror);
extern void HudSprite_SetRect(HudSprite *spr, s32 x0, s32 x1, s32 y0, s32 y1);
extern void HudSprite_SetUv(HudSprite *spr, s32 u0, s32 u1, s32 v0, s32 v1);
extern void HudSprite_SetColor(HudSprite *spr, s32 r, s32 g, s32 b, s32 a);
extern void HudSprite_InitPlain(HudSprite *spr, s32 r, s32 g, s32 b, s32 a); /* untextured, colour */
extern void HudSprite_Move(HudSprite *spr, s32 dx, s32 dy);            /* moves the screen rectangle */
extern void HudSprite_InitTex(HudSprite *spr, HudRes *res, s32 tex, s32 sub); /* texture, full size, neutral colour */
extern void HudSprite_DrawAlphaClear(HudSprite *spr);                            /* draws the rectangle as the mask */
extern void HudSprite_DrawAt(HudSprite *spr, HudRes *res, s32 additive, s32 tbp, s32 cbp);
extern void HudSprite_Draw(HudSprite *spr, HudRes *res, s32 additive);  /* 0x225A50 with blocks 0x2A00 / 0x2C80 */
extern void HudNode_Show(HudNode *node, s32 show);
extern void HudNode_SetPos(HudNode *node, s32 x, s32 y);

/* GS state before a mask is drawn: context 2 writes only the alpha channel of the frame buffer (FBMSK
   0x00FFFFFF) with FBA on, always passing. */
void HudTeam_GsBeginMask(void) {
    u32 pkt[24] = {
        DMA_TAG_CNT | 5, 0, VIF_FLUSHE, VIF_DIRECT | 5,
        GIF_EOP | 4, 0x10000000, GIF_REG_AD, 0,
        0x34000, 0, GS_TEST_1, 0,
        GFX_FRAME_REG(), 0xFFFFFF, GS_FRAME_2, 0,
        1, 0, GS_FBA_2, 0,
        0x3000F, 0, GS_TEST_2, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* GS state after the masked sprite: context 2 writes all channels again, FBA off, normal test. */
void HudTeam_GsEndMask(void) {
    u32 pkt[24] = {
        DMA_TAG_CNT | 5, 0, VIF_FLUSHE, VIF_DIRECT | 5,
        GIF_EOP | 4, 0x10000000, GIF_REG_AD, 0,
        0x30000, 0, GS_TEST_1, 0,
        GFX_FRAME_REG(), 0, GS_FRAME_2, 0,
        0, 0, GS_FBA_2, 0,
        0x30000, 0, GS_TEST_2, 0,
    };

    Dma_AddData(pkt, sizeof(pkt));
}

/* Root node: steps the slide and flip ramps (not while paused) and places the root and the two face groups.
   The root moves by (-256, -224) * (slide + hide). A face group is at (-|v| * 128, v * 32) for its flip value v. */
void HudTeam_UpdateRoot(HudNode *node);

/* Face A node: with two or more members in reserve the face sits 14 to the right and the plate shows. */
void HudTeam_UpdateFaceA(void);

/* Face B node: the same for the outgoing face. */
void HudTeam_UpdateFaceB(void);

/* Health bar A: the 32-wide bar is shifted right by 30 * health / maximum. */
void HudTeam_UpdateHpA(void);

/* Health bar B: the same from the values saved when the flip started. */
void HudTeam_UpdateHpB(void);

/* Draws health bar A through its mask. */
void HudTeam_DrawHpA(void);

/* Draws health bar B through its mask. */
void HudTeam_DrawHpB(void);

/* Switch gauge: bar shifted by 30 * gauge / 100000; at 100000 the "full" marker shows and its alpha runs
   0 -> 128 -> 0 over two seconds (not while paused). */
void HudTeam_UpdateGauge(void);

/* Draws the switch gauge through its mask, then the "full" marker. */
void HudTeam_DrawGauge(void);

/* Generic draw callback: the node's sprites from the panel's sheet. */
void HudTeam_DrawSprites(HudNode *node);

/* Clears the mark of the first texture of a side's face sheet. */
void HudTeam_ClearFaceTexMark(s32 side);

/* Face A: the frame, then texture 0 of the stand-by member's face sheet (uploaded to blocks 0x2C00 / 0x2CD0).
   Declared with a return type and no return statement: the last call is a plain `jal`, not a tail call. */
s32 HudTeam_DrawFaceA(void);

/* Face B: the same for the member shown before the flip. */
s32 HudTeam_DrawFaceB(void);

/* Makes `side` the side shown by the next update / draw: side 1 is mirrored (with the faces mirrored back),
   and the panel is hidden for a side without reserve members. */
void HudTeam_SelectSide(s32 side);

/* Health of the member a switch would bring in. */
void HudTeam_SetTargetHp(s32 side, s32 hp);

/* Its maximum health. */
void HudTeam_SetTargetHpMax(s32 side, s32 hpMax);

/* Switch gauge; on the frame it becomes full the marker's blink starts (1 -> 0 over a second). */
void HudTeam_SetSwitchGauge(s32 side, s32 gauge);

/* Member index of the member a switch would bring in. */
void HudTeam_SetTarget(s32 side, s32 member);

/* Number of members in reserve; the panel shows when it is not zero. */
void HudTeam_SetReserveCount(s32 side, s32 count);

/* Slides both panels off the screen. */
void HudTeam_SlideOut(f32 seconds);

/* Slides them back. */
void HudTeam_SlideIn(f32 seconds);

/* While a side is switching its panel slides away, and back afterwards, over 0.3 s. */
void HudTeam_SetSwitching(s32 side, s32 on);

/* Starts the face change animation (0.25 s): the new face comes in from one side while the old one, with the
   health it had, leaves to the other. */
void HudTeam_StartFlipNext(s32 side);

/* The same in the other direction. */
void HudTeam_StartFlipPrev(s32 side);

/* Builds the panel: work, 12 sprites, 9 nodes; *out receives the root node. */
void HudTeam_Init(HudNode **out, HudRes *res);

/* Frees the sprites, every node's lists, the nodes and the work. */
void HudTeam_Term(void);

/* Round reset: zeroes the values and ramps of both sides. */
void HudTeam_Reset(void);
