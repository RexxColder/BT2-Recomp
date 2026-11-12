#include "common.h"

/* Diagnostico temporal (ver EftHit_BeginFrame). */
#include <stdio.h>

/* Rewinds the shape arena (EftHitArena_Reset, 0x127F30). */
extern void EftHitArena_Reset(void);

/* Battle work block (gp-relative in the original). */
extern void *D_003876A0;

/* Hit record list (gEftHitList). */
extern u8 *gEftHitList;

/* Shape arena of this frame (gEftHitArena), same view as include/battle/eft_a.h. The header is not included here
 * because its `EftHitList *gEftHitList` would clash with the byte pointer this file uses above (and change the
 * `+ 0x6000` arithmetic). */
typedef struct EftHitArena {
    /* 0x0 */ u8 *cur;
    /* 0x4 */ u8 *base;
    /* 0x8 */ s32 size; /* 0x1800 */
} EftHitArena; /* size 0xC */

extern EftHitArena *gEftHitArena;

/* Start of a frame: empties the hit record list and rewinds the arena, unless bit 8 of the 64-bit word at +0x4D8
 * of the battle work block is set (time stopped: last frame's records stay). */
void EftHit_BeginFrame(void) {
    /* Diagnostico temporal: nada de esto cambia el comportamiento. */
    static s32 skipped = 0; /* frames consecutivos con el tiempo detenido */
    static s32 calls = 0;
    s32 used = (s32)(gEftHitArena->cur - gEftHitArena->base);
    s32 stopped = (*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 0x100) != 0;
    calls++;
    if (stopped) {
        skipped++;
    } else {
        skipped = 0;
    }
    if (used > 0x1800 && calls % 60 == 0) {
        fprintf(stderr, "EFTHIT: arena desbordada used=0x%X skipped=%d count=%d\n", used, skipped,
                *(s32 *)(gEftHitList + 0x6000));
    }
    if (skipped == 300) {
        fprintf(stderr, "EFTHIT: tiempo detenido %d frames used=0x%X\n", skipped, used);
    }
    if (!(*(s64 *)((u8 *)D_003876A0 + 0x4D8) & 0x100)) {
        EftHitArena_Reset();
        *(s32 *)(gEftHitList + 0x6000) = 0;
    }
}
