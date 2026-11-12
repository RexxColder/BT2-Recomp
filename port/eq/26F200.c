#include "common.h"

#define PF32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PS32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define PS16(p, o) (*(s16 *)((u8 *)(p) + (o)))

static s32 clamp8(s32 v) {
    if (v < 0) {
        return 0;
    }
    if (v < 0x100) {
        return v;
    }
    return 0xFF;
}

/* 0x0026F200: transforms the three (a0+4, a0+8) pairs (stride 8) by the 2x3 matrix a1; when a3 is null the pairs
   also get the integer offsets t0/t1. Then the bounds at a0+0x1C/0x20 are recomputed and the four s32 fields
   a0+0x38..0x44 are scaled by a2 and clamped to 0..255. When a3 is set, the same is repeated with a3 as the
   transform and flags (a3[0]) selecting the optional steps. */
void func_0026F200(u8 *a0, u8 *a1, u8 *a2, u8 *a3, s32 t0, s32 t1) {
    s32 k;
    u8 *p;
    u8 *q;
    f32 x;
    f32 y;
    f32 f6;
    f32 f7;
    s32 flags;

    for (k = 0; k < 3; k++) {
        p = a0 + 4 + 8 * k;
        q = a0 + 8 + 8 * k;
        x = PF32(p, 0);
        y = PF32(q, 0);
        PF32(p, 0) = x * PF32(a1, 0) + y * PF32(a1, 0xC) + PF32(a1, 0x8);
        PF32(q, 0) = x * PF32(a1, 0x4) + y * PF32(a1, 0x10) + PF32(a1, 0x14);
        if (a3 == 0) {
            PF32(p, 0) += (f32)t0;
            PF32(q, 0) += (f32)t1;
        }
    }

    PF32(a0, 0x1C) = PF32(a0, 0xC) + PF32(a0, 0x14) - PF32(a0, 0x4);
    PF32(a0, 0x20) = PF32(a0, 0x10) + PF32(a0, 0x18) - PF32(a0, 0x8);
    PS32(a0, 0x38) = clamp8((s32)((f32)PS32(a0, 0x38) * PF32(a2, 0x0)) + PS16(a2, 0x10));
    PS32(a0, 0x3C) = clamp8((s32)((f32)PS32(a0, 0x3C) * PF32(a2, 0x4)) + PS16(a2, 0x12));
    PS32(a0, 0x40) = clamp8((s32)((f32)PS32(a0, 0x40) * PF32(a2, 0x8)) + PS16(a2, 0x14));
    PS32(a0, 0x44) = clamp8((s32)((f32)PS32(a0, 0x44) * PF32(a2, 0xC)) + PS16(a2, 0x16));

    if (a3 == 0) {
        return;
    }

    f7 = PF32(a3, 0x30);
    f6 = PF32(a3, 0x40);
    if (PS32(a3, 0) & 0x10) {
        f7 = f7 * PF32(a3, 0x10);
        f6 = f6 * PF32(a3, 0x14);
    }

    for (k = 0; k < 3; k++) {
        p = a0 + 4 + 8 * k;
        q = a0 + 8 + 8 * k;
        x = PF32(p, 0);
        y = PF32(q, 0);
        PF32(p, 0) = x * f7 + y * PF32(a3, 0x3C) + PF32(a3, 0x38);
        PF32(q, 0) = x * PF32(a3, 0x34) + y * f6 + PF32(a3, 0x44);
        flags = PS32(a3, 0);
        if (flags & 0x2) {
            PF32(p, 0) += PF32(a3, 0x4);
            PF32(q, 0) += PF32(a3, 0x8);
        }
        if (!(flags & 0x200)) {
            PF32(p, 0) += (f32)t0;
            PF32(q, 0) += (f32)t1;
        }
    }

    PF32(a0, 0x1C) = PF32(a0, 0xC) + PF32(a0, 0x14) - PF32(a0, 0x4);
    PF32(a0, 0x20) = PF32(a0, 0x10) + PF32(a0, 0x18) - PF32(a0, 0x8);
    PS32(a0, 0x38) = clamp8((s32)((f32)PS32(a0, 0x38) * PF32(a3, 0x48)) + PS16(a3, 0x58));
    PS32(a0, 0x3C) = clamp8((s32)((f32)PS32(a0, 0x3C) * PF32(a3, 0x4C)) + PS16(a3, 0x5A));
    PS32(a0, 0x40) = clamp8((s32)((f32)PS32(a0, 0x40) * PF32(a3, 0x50)) + PS16(a3, 0x5C));
    PS32(a0, 0x44) = clamp8((s32)((f32)PS32(a0, 0x44) * PF32(a3, 0x54)) + PS16(a3, 0x5E));

    flags = PS32(a3, 0);
    if (flags & 0x20) {
        PS32(a0, 0x38) = (s32)((f32)PS32(a0, 0x38) * PF32(a3, 0x18));
        PS32(a0, 0x3C) = (s32)((f32)PS32(a0, 0x3C) * PF32(a3, 0x18));
        PS32(a0, 0x40) = (s32)((f32)PS32(a0, 0x40) * PF32(a3, 0x18));
    }
    if (flags & 0x8) {
        PS32(a0, 0x44) = (s32)((f32)PS32(a0, 0x44) * PF32(a3, 0xC));
    }
}
