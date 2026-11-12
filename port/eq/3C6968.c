#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));

/* 0x003C6968 (arg0 = i, o = 4i): chain 1: p = G[o+0x198], u = G[o+0x190], T = G[o+0x1CC] (pointer), k = 7p + u,
 * w = G[o+0x1A0]; *(T+44k) = *(T+44k+4w+8). Chain 2: u2 = G[o+0x190], p2 = G[o+0x198], T2 = G[o+0x1CC], k2 = 7p2 + u2,
 * q = *(T2+44k2), R = G->0x10, z = *(R+4q+4) & ~3, G[8+4*u2+0x13C] = *(R+z+0x10). Chain 3: u3 = G[o+0x190],
 * p3 = G[o+0x198], w3 = G[o+0x1A0]; G[8 + 4*(7p3 + 134i + u3) + 0x31F0] = w3. G = D_00423114. */
void func_003C6968(s32 arg0) {
    u8 *g;
    s32 o;
    s32 p;
    s32 u;
    s32 w;
    s32 k;
    s32 x;
    u8 *t;
    u8 *r;
    s32 q;
    s32 z;
    s32 y;

    o = arg0 * 4;

    g = D_00423114;
    p = *(s32 *)(g + o + 0x198);
    u = *(s32 *)(g + o + 0x190);
    t = *(u8 **)(g + o + 0x1CC);
    w = *(s32 *)(g + o + 0x1A0);
    k = p * 7 + u;
    x = *(s32 *)(t + k * 44 + w * 4 + 8);
    *(s32 *)(t + k * 44) = x;

    g = D_00423114;
    u = *(s32 *)(g + o + 0x190);
    p = *(s32 *)(g + o + 0x198);
    t = *(u8 **)(g + o + 0x1CC);
    k = p * 7 + u;
    q = *(s32 *)(t + k * 44);
    r = *(u8 **)(g + 0x10);
    z = (s32)((u32)*(s32 *)(r + q * 4 + 4) & ~3u);
    y = *(s32 *)(r + z + 0x10);
    *(s32 *)(g + 8 + u * 4 + 0x13C) = y;

    g = D_00423114;
    u = *(s32 *)(g + o + 0x190);
    p = *(s32 *)(g + o + 0x198);
    w = *(s32 *)(g + o + 0x1A0);
    *(s32 *)(g + 8 + (p * 7 + arg0 * 134 + u) * 4 + 0x31F0) = w;
}
