#define FadeSlot_Draw List_GetHead  /* fix_targets */ /* the original uses 0x29fc68 here */
#define gFade D_003B0E50  /* fix_targets */ /* the original uses 0x3b0e50 here */
#include "common.h"
#include "sys/dma.h"
#include "sys/fade.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void Vec4_Copy(f32 *dst, f32 *src);
extern void Vec4_Add(f32 *dst, f32 *a, f32 *b);
extern void Vec4_Sub(f32 *dst, f32 *a, f32 *b);
extern void Vec4_Scale(f32 *dst, f32 *src, f32 scale);
extern void Gfx_PutDefaultEnv(u64 **pp);  /* appends the common 2D GS state (13 quadwords) at *pp and advances it */

/* The rectangle in GS primitive coordinates: the 512x448 screen centred on 2048,2048. */
#define FADE_X 1792
#define FADE_Y 1824
#define FADE_H 448
#define FADE_STRIPS 16

/* Queues the slot's colour as a blended 512x448 rectangle (16 sprites 32 pixels wide). */
void Fade_DrawRect(Fade *fade);

/* Turns a slot off and stops its ramp. */
void FadeSlot_Reset(Fade *fade);

/* Sets or clears the pause flag of a slot that is on. */
void FadeSlot_SetPause(Fade *fade, s32 pause);

/* color = from + delta * ramp value. */
void FadeSlot_CalcColor(Fade *fade);

/* Returns the pause flag of a slot. */
s32 FadeSlot_IsPaused(Fade *fade);

/* Returns 1 when the slot is on (fading or holding its end colour). */
s32 FadeSlot_IsActive(Fade *fade);

/* Returns 1 when the slot's ramp has ended or the slot is off. */
s32 FadeSlot_IsDone(Fade *fade);

/* One frame of a slot: recomputes the colour, steps the ramp, and turns the slot off once it has ended transparent. */
void FadeSlot_Update(Fade *fade);

/* Draws a slot if it is on. */
void FadeSlot_Draw(Fade *fade);

/* Boot-time set-up: clears the first slot and turns every slot off. */
void Fade_Init(void);

/* Empty. */
void Fade_Term(void);

/* Turns every slot off. */
void Fade_ResetAll(void);

/* Turns one slot off. */
void Fade_Reset(s32 idx);

/* Pauses or resumes every slot that is on. */
void Fade_PauseAll(s32 pause);

/* Pauses or resumes one slot. */
void Fade_Pause(s32 idx, s32 pause);

/* Returns the pause flag of one slot. */
s32 Fade_IsPaused(s32 idx);

/* Returns 1 when the slot is on. */
s32 Fade_IsActive(s32 idx);

/* Returns 1 when the slot's fade has ended or the slot is off. */
s32 Fade_IsDone(s32 idx);

/* Starts a fade of `seconds` on a slot: FADE_OUT covers the screen with the slot's colour, FADE_IN uncovers it. */
void Fade_Start(s32 idx, s32 dir, f32 seconds);

/* Steps every slot; once per frame. */
void Fade_UpdateAll(void);

/* Draws slots 0 and 1 over the finished frame. */
void Fade_DrawScreen(void);

/* Draws slot 2. */
void func_002A03F0(void) {
    FadeSlot_Draw(&gFade[2]);
}
