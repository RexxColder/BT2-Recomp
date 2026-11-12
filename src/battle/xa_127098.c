#include "common.h"

/*
 * Hit record list, one function: EftHit_GetNew (0x127098..0x127124). The list is gEftHitList: 64 records of
 * 0x180 bytes each (their stride, not the 0x190 of EftHitRec in include/battle/eft_a.h) and the next free index
 * at +0x6000. The index is wrapped to 0 when it reaches 64, that record is zeroed, its float at +0x74 set to 1.0,
 * and its address returned. The index is not advanced here: EftHit_Add does that.
 */

extern void *memset(void *dst, s32 c, u32 n);
extern u8 *gEftHitList;

#define EFT_HIT_STRIDE 0x180
#define EFT_HIT_NEXT_OFF 0x6000

void *EftHit_GetNew(void) {
    if (*(s32 *)(gEftHitList + EFT_HIT_NEXT_OFF) >= 0x40) {
        *(s32 *)(gEftHitList + EFT_HIT_NEXT_OFF) = 0;
    }
    memset(gEftHitList + *(s32 *)(gEftHitList + EFT_HIT_NEXT_OFF) * EFT_HIT_STRIDE, 0, EFT_HIT_STRIDE);
    *(f32 *)(gEftHitList + *(s32 *)(gEftHitList + EFT_HIT_NEXT_OFF) * EFT_HIT_STRIDE + 0x74) = 1.0f;
    return gEftHitList + *(s32 *)(gEftHitList + EFT_HIT_NEXT_OFF) * EFT_HIT_STRIDE;
}
