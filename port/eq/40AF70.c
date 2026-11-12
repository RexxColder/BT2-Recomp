#include "common.h"

extern u8 *D_0042BB78 __attribute__((section(".data")));

#define G (D_0042BB78)
#define GW(o) (*(s32 *)(G + (o)))

/* offset into G of an entry: 4 * G[0x2DC + 4i] + 20i + (bit ? a : b) */
#define ENT(i, a, b) (4 * GW(0x2DC + 4 * (i)) + 20 * (i) + ((GW(0x240) & (0x400 << (i))) ? (a) : (b)))

void func_0040AF70(s32 arg0) {
    s32 i = arg0;
    s32 X, Y, Z, W, v;
    u8 *base;
    u8 *dst;

    X = *(s32 *)(G + 4 + ENT(i, 0x23C, 0x240));
    Y = *(s32 *)(G + 0xC + ENT(i, 0x25C, 0x260));
    base = *(u8 **)(G + 0x360 + 4 * i);
    v = 7 * Y + X;
    dst = base + v * 44;

    X = *(s32 *)(G + 4 + ENT(i, 0x23C, 0x240));
    Y = *(s32 *)(G + 0xC + ENT(i, 0x25C, 0x260));
    Z = *(s32 *)(G + 4 + ENT(i, 0x28C, 0x290));
    base = *(u8 **)(G + 0x360 + 4 * i);
    v = 7 * Y + X;
    *(s32 *)dst = *(s32 *)(base + v * 44 + 4 * Z + 8);

    W = *(s32 *)(G + 4 * (5 * i + GW(0x2DC + 4 * i)) + 0x244);
    X = *(s32 *)(G + 4 + ENT(i, 0x23C, 0x240));
    Y = *(s32 *)(G + 0xC + ENT(i, 0x25C, 0x260));
    base = *(u8 **)(G + 0x360 + 4 * i);
    {
        u8 *g18 = *(u8 **)(G + 0x18);
        s32 w = *(s32 *)(base + (7 * Y + X) * 44);
        u32 o = *(u32 *)(g18 + 4 * w + 4);
        *(s32 *)(G + 4 * (20 * i + W) + 0x1A8) = *(s32 *)(g18 + ((o >> 2) << 2) + 0x10);
    }

    Y = *(s32 *)(G + 0xC + ENT(i, 0x25C, 0x260));
    X = *(s32 *)(G + 4 + ENT(i, 0x23C, 0x240));
    Z = *(s32 *)(G + 4 + ENT(i, 0x28C, 0x290));
    *(s32 *)(G + 0xC + 4 * (7 * Y + 134 * i + X) + 0x3380) = Z;
}
