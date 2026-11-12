#include "common.h"
#include "sys/color_fade.h"
#include "sys/dma.h"
#include "sys/gfx.h"

extern void *memset(void *dst, s32 c, u32 n);
extern void LipSync_Clear(void); /* clears the 0x14 bytes at 0x31E570 (not decompiled) */

/* Queues the overlay as one blended 512x448 sprite, unless it is fully transparent. */
void ColorFade_Draw(void);

/* Steps the alpha ramp once; call every frame. */
void ColorFade_Update(void);

/* Starts uncovering the screen from the given colour over `frames` frames. */
void ColorFade_StartIn(s32 r, s32 g, s32 b, s32 frames);

/* Starts covering the screen with the given colour over `frames` frames. */
void ColorFade_StartOut(s32 r, s32 g, s32 b, s32 frames);

/* True once a fade in has ended. */
s32 ColorFade_IsInDone(void) {
    return (gColorFade.flags >> 2) & 1;
}

/* True once a fade out has ended. */
s32 ColorFade_IsOutDone(void) {
    return (gColorFade.flags >> 3) & 1;
}

/* True while a fade in is running. */
s32 ColorFade_IsFadingIn(void);

/* True while a fade out is running. */
s32 ColorFade_IsFadingOut(void) {
    return (gColorFade.flags >> 1) & 1;
}
