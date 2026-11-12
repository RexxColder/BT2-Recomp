#include "common.h"

extern u8 *D_003876A0;
extern u8 *gBtlStage;
extern f32 D_00387018;

/* 0x00276EA8: nothing when bit 8 of the 64-bit word at D_003876A0 +0x4D8 is set. Else over the stage's table
 * (count at +0x10, base = +0x5C + 4 * index at +0x14, 0x10-byte entries): the float at +8 gets + D_00387018,
 * bit 2 of the halfword at +0 is cleared, and when the float at +0xC is below the new value, bit 2 is set and
 * the +8 word is zeroed. */
void func_00276EA8(void) {
    u8 *e;
    s32 count;
    s32 idx;
    s32 i;

    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return;
    }
    count = *(s32 *)(gBtlStage + 0x10);
    if (count == 0) {
        return;
    }
    idx = *(s32 *)(gBtlStage + 0x14);
    e = *(u8 **)(gBtlStage + 0x5C) + (idx << 2);
    for (i = 0; i < count; i++) {
        f32 t = *(f32 *)(e + 8) + D_00387018;
        f32 lim = *(f32 *)(e + 0xC);
        u16 v = *(u16 *)e & 0xFFFBu;

        *(u16 *)e = v;
        *(f32 *)(e + 8) = t;
        if (lim < t) {
            *(u16 *)e = (u16)(v | 0x4u);
            *(s32 *)(e + 8) = 0;
        }
        e += 0x10;
    }
}
