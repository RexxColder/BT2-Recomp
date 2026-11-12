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


/* Draws slot 2. */
void Fade_DrawSlot2(void) {
    FadeSlot_Draw(&gFade[2]);
}
