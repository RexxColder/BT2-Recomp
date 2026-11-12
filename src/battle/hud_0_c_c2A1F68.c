#include "common.h"
#include "battle/hud_0.h"

/*
 * Battle pause menu, part 3: head of the skill-list text module. Source range 0x215010-0x215420.
 *
 * These seven functions belong with the BtlText_* code that starts src/battle/btl_seq.c at 0x215420 (same
 * sprite sheet, same callers). Unlike the menu engine before them they reach the menu work through
 * BtlMenu_GetWork() and never through the global, which is the evidence for a file boundary at 0x215010.
 *
 * Presentation only: no simulation state, no pad, no random numbers.
 */

/* Local view of the 0x7FC-byte progress block: only the control configuration is used. */
typedef struct BtlTextProgress {
    /* 0x000 */ u8 unk0[0x7F4];
    /* 0x7F4 */ s32 controlType;
} BtlTextProgress;

extern BtlTextProgress *gProgress;

extern void Font_PushStyle(void);
extern void Font_PopStyle(void);
extern void Font_SetScale(f32 scale);
extern void Font_SetSpacing(s32 x, s32 y);
extern void Font_SetShadowMode(s32 mode);
extern void Font_SetColorRGBA(s32 r, s32 g, s32 b, s32 a);
extern void Font_SetShadowColorRGBA(s32 r, s32 g, s32 b, s32 a);
extern void Font_PrintAt(s32 x, s32 y, u16 *str);

/* Draws the controls page inside a box: the title (sheet entry 0, row 4) centred at the top and the text for
   the pad type and the control configuration (gProgress + 0x7F4) below it. */
void BtlText_DrawControls(u64 **pkt, s32 x0, s32 x1, s32 y0, s32 y1);

/* 1 when a box in GS coordinates lies inside the drawing area. */
s32 BtlText_IsOnScreen(s32 x0, s32 y0, s32 x1, s32 y1);

/*
 * Writes one sprite of sheet entry `part`: corners in screen pixels, UV in texels. Nothing is written when
 * the box is off screen. The packet is the same as BtlMenu_PutSprite's: a REGLIST GIF tag with 8 registers
 * (PRIM, NOP, TEX0_1, RGBAQ, UV, XYZ2, UV, XYZ2), PRIM 0x156 (sprite, textured, blended, UV coordinates),
 * TEX0, the colour with Q = 1.0f, then the two corners with Z = 0xFFFFFFF0. Screen offset: x + 0x700,
 * y + 0x720 (in 1/16 pixel after the shift by 4).
 *
 * FAKE MATCH (permuter): `y0++; y0--;` between the two calls. The pair combines to a self-move of y0 that is
 * deleted after register allocation; its only effect is that the live ranges crossing it are one instruction
 * longer (and y0 has two more references). Without it the code is the same with two saved registers exchanged
 * (7 of 108 instructions): the allocator orders x0 and u0 by uses / live length, 3 / 49 against 2 / 33, so x0
 * comes first and takes s3; with x0 at 50 instructions (3 / 50 < 2 / 33) u0 comes first, the original's s3 for
 * u0 and s4 for x0. The dummy works anywhere between the on-screen test and the BtlText_GetTex0 call and
 * nowhere else, and only on y0. It stands in for a source form that is one instruction longer there before
 * register allocation (or leaves u0 one shorter) yet emits the same code; that form was not found: the
 * statement order of the four offset additions (all 24), the operand order of the ORs, locals for the corners /
 * the UVs / the Z constant / the texture word / the test result, helper functions, an early return and the
 * offsets added in the call were tried (`((s64)v0 << 20) | ((s64)u0 << 4)` puts x0 in s4 but exchanges u0 and
 * v0). The forms that made the similar FontIcon_PutSprite (col_c_b.c) match (separate locals for the corners,
 * (u64) casts, the Z and Q constants written as shifts) leave the same 7 here; the same dummy on u0, x0, y1,
 * u1 or v1 does not work.
 */
void BtlText_PutSprite(u64 **pkt, s32 x0, s32 y0, s32 x1, s32 y1, s32 u0, s32 v0, s32 u1, s32 v1, u32 color,
                       s32 part);

/* TEX0 of sheet entry `part` (its own pixels and CLUT, TCC on). */
u64 BtlText_GetTex0(s32 part);

/* Writes SCISSOR_1 for a clip rectangle (inclusive pixel bounds). */
void BtlText_PutScissor(u64 **pkt, s32 x0, s32 y0, s32 x1, s32 y1);

/* 1 for a line feed or a carriage return. */
s32 Font_IsNewline(u16 c) {
    s32 result = 0;

    if (c == 10 || c == 13) {
        result = 1;
    }
    return result;
}

/* Returns the pointer behind the next newline character, or to the terminator when the text ends first. */
u16 *BtlText_NextLine(u16 *p);
