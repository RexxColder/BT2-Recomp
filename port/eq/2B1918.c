#include "common.h"

extern u8 *D_00387A40;
extern f32 D_00387630;

/* 0x002B1918: loop over the 8 entities (idx 3..11) in the table at D_00387A40+8.
 * Each entity gets a unit push direction toward self and is pushed out of the
 * overlap band; the flag words at self+0x14 / +0x18 record what was done.
 * Always returns 0 (the asm returns the slti result of the last loop test). */
s32 func_002B1918(u8 *self)
{
    u8 *ref;
    u8 *ent;
    f32 refX;
    f32 refY;
    f32 dx;
    f32 dy;
    f32 dist;
    f32 ux;
    f32 uy;
    f32 gap;
    f32 dotRef;
    f32 dotEnt;
    u32 bit;
    s32 idx;

    *(u32 *)(self + 0x14) = 0;
    *(u32 *)(self + 0x18) = 0;
    ref = *(u8 **)self;
    refX = *(f32 *)(ref + 0xA20);
    refY = *(f32 *)(ref + 0xA28);

    idx = 3;
    do {
        ent = *(u8 **)(D_00387A40 + 8) + idx * 5408;
        if ((*(u32 *)(ent + 0xAF0) & 2) == 0 || *(u32 *)(ent + 0xC) == 0) {
            idx++;
            continue;
        }

        dx = *(f32 *)(self + 0xD0) - *(f32 *)(ent + 0x9A0);
        dy = *(f32 *)(self + 0xD8) - *(f32 *)(ent + 0x9A8);
        dist = __builtin_sqrtf(dx * dx + dy * dy);

        ux = 1.0f;
        uy = 1.0f;
        if (D_00387630 < dist) {
            ux = dx / dist;
            uy = dy / dist;
        }

        gap = (dist - 5.0f) - 5.0f;
        if (gap < 15.0f) {
            dotRef = refX * ux + refY * uy;
            dotEnt = *(f32 *)(ent + 0xA20) * ux + *(f32 *)(ent + 0xA28) * uy;
            if (0.75f < dotRef && 0.75f < -dotEnt) {
                bit = (u32)1 << (idx - 3);
                *(u32 *)(self + 0x18) |= bit;
            }
        }

        if (gap < 0.0f) {
            bit = (u32)1 << (idx - 3);
            *(f32 *)(self + 0xD0) = *(f32 *)(self + 0xD0) - ux * gap;
            *(f32 *)(self + 0xD8) = *(f32 *)(self + 0xD8) - uy * gap;
            *(u32 *)(self + 0x14) |= bit;
        }
        idx++;
    } while (idx < 12);

    return 0;
}
