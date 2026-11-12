#include "common.h"

extern u8 *D_00387E18;
extern u8 *D_003876A0;
extern u8 D_003B0B00[];
extern f32 D_003874E4;
extern f32 D_003874E8;

s32 func_0028C520(s32 arg0, s32 arg1);
f32 Pad_StickToFloat(s32 arg0, s32 arg1);

/* byte clear of game memory (optnone: no memset intrinsic on game memory) */
__attribute__((noinline, optnone)) static void blob_clear(u8 *d, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = 0;
    }
}

/* Per-frame pad state for one controller block (arg0 + 0x80): reads the analog sticks of port
   arg0->0xC (or copies the recorded ones when it is negative), smooths them, derives the direction
   bits (up/down/left/right and stick magnitudes) and the pressed/released masks vs. the old state. */
void func_002AFFC0(u8 *arg0) {
    u8 *blk = arg0 + 0x80;
    s32 flags = 0;
    s32 useRaw;
    s32 oldFlags;
    s32 port;
    f32 old0, old1, old2, old3;
    f32 mag;
    f32 lo, hi;
    f32 a, b, c, d;
    u8 sx0, sx1, sx2, sx3;

    useRaw = D_00387E18[0xA] != 0;
    if ((*(u64 *)(D_003876A0 + 0x4D8) & 0x200) != 0) {
        useRaw = 1;
    }
    old0 = *(f32 *)(blk + 0xC);
    old1 = *(f32 *)(blk + 0x10);
    old2 = *(f32 *)(blk + 0x14);
    old3 = *(f32 *)(blk + 0x18);
    port = *(s32 *)(arg0 + 0xC);
    oldFlags = *(s32 *)blk;
    blob_clear(blk, 0x30);

    if (!useRaw) {
        if (port < 0) {
            *(f32 *)(blk + 0xC) = *(f32 *)(arg0 + 0xB4);
            *(f32 *)(blk + 0x10) = *(f32 *)(arg0 + 0xB8);
            *(f32 *)(blk + 0x14) = *(f32 *)(arg0 + 0xBC);
            *(f32 *)(blk + 0x18) = *(f32 *)(arg0 + 0xC0);
            flags = *(s32 *)(arg0 + 0xB0);
        } else if (*(s32 *)(D_003B0B00 + port * 0x180 + 0x108) != 0) {
            sx0 = (u8)func_0028C520(port, 0x40000);
            sx1 = (u8)func_0028C520(port, 0x80000);
            sx2 = (u8)func_0028C520(port, 0x10000);
            sx3 = (u8)func_0028C520(port, 0x20000);
            flags = *(s32 *)(D_003B0B00 + port * 0x180 + 0x12C);
            *(f32 *)(blk + 0xC) = Pad_StickToFloat(sx0, 0x32);
            *(f32 *)(blk + 0x10) = Pad_StickToFloat(sx1, 0x32);
            *(f32 *)(blk + 0x14) = Pad_StickToFloat(sx2, 0x32);
            d = Pad_StickToFloat(sx3, 0x32);
            *(f32 *)(blk + 0xC) = old0 + (*(f32 *)(blk + 0xC) - old0) * 0.5f;
            *(f32 *)(blk + 0x18) = old3 + (d - old3) * 0.5f;
            *(f32 *)(blk + 0x10) = old1 + (*(f32 *)(blk + 0x10) - old1) * 0.5f;
            *(f32 *)(blk + 0x14) = old2 + (*(f32 *)(blk + 0x14) - old2) * 0.5f;
        }
    }

    a = *(f32 *)(blk + 0xC);
    b = *(f32 *)(blk + 0x10);
    *(f32 *)(blk + 0x1C) = a;
    *(f32 *)(blk + 0x20) = b;
    if ((flags & 0x80) != 0) {
        *(f32 *)(blk + 0x1C) = -1.0f;
    }
    if ((flags & 0x20) != 0) {
        *(f32 *)(blk + 0x1C) = 1.0f;
    }
    if ((flags & 0x10) != 0) {
        *(f32 *)(blk + 0x20) = -1.0f;
    }
    if ((flags & 0x40) != 0) {
        *(f32 *)(blk + 0x20) = 1.0f;
    }

    mag = __builtin_sqrtf(*(f32 *)(blk + 0x1C) * *(f32 *)(blk + 0x1C) +
                          *(f32 *)(blk + 0x20) * *(f32 *)(blk + 0x20));
    *(f32 *)(blk + 0x2C) = mag;
    if (mag > 1.0f) {
        f32 x = *(f32 *)(blk + 0x1C);
        f32 y = *(f32 *)(blk + 0x20);
        *(f32 *)(blk + 0x2C) = 1.0f;
        *(f32 *)(blk + 0x1C) = x / mag;
        *(f32 *)(blk + 0x20) = y / mag;
    }

    mag = __builtin_sqrtf(a * a + b * b);
    *(f32 *)(blk + 0x24) = mag;
    if (mag > 1.0f) {
        f32 x = *(f32 *)(blk + 0xC);
        f32 y = *(f32 *)(blk + 0x10);
        *(f32 *)(blk + 0x24) = 1.0f;
        *(f32 *)(blk + 0xC) = x / mag;
        *(f32 *)(blk + 0x10) = y / mag;
    }

    c = *(f32 *)(blk + 0x14);
    d = *(f32 *)(blk + 0x18);
    mag = __builtin_sqrtf(c * c + d * d);
    *(f32 *)(blk + 0x28) = mag;
    if (mag > 1.0f) {
        *(f32 *)(blk + 0x28) = 1.0f;
        d = d / mag;
        *(f32 *)(blk + 0x18) = d;
        c = c / mag;
        *(f32 *)(blk + 0x14) = c;
    }

    a = *(f32 *)(blk + 0xC);
    lo = D_003874E4;
    if (a < lo) {
        flags |= 0x40000;
    }
    hi = D_003874E8;
    if (hi < a) {
        flags |= 0x80000;
    }
    b = *(f32 *)(blk + 0x10);
    if (b < lo) {
        flags |= 0x10000;
    }
    if (hi < b) {
        flags |= 0x20000;
    }
    if (c < lo) {
        flags |= 0x400000;
    }
    if (hi < c) {
        flags |= 0x800000;
    }
    if (d < lo) {
        flags |= 0x100000;
    }
    if (hi < d) {
        flags |= 0x200000;
    }
    if ((flags & 0xF0000) != 0) {
        flags |= 0x1000000;
    }
    if ((flags & 0xF00000) != 0) {
        flags |= 0x2000000;
    }
    if ((flags & 0xF0) != 0) {
        flags |= 0x4000000;
    }

    *(s32 *)blk = flags;
    *(s32 *)(blk + 8) = oldFlags & ~flags;
    *(s32 *)(blk + 4) = flags & ~oldFlags;
}
