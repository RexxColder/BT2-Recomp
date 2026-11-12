#include "common.h"

extern u8 *D_0042BB74 __attribute__((section(".data")));

/* 0x00405BA0: g = D_0042BB74, o1 = 4i+0x210, o4 = 4i+0x260. t0 = *(g+o1+0xC), t2 = *(g+4+o1), t3 = *(g+o4) (pointer),
 * k = 7*t0 + t2, a1 = *(g+4+4i+0x220): *(t3+44k) = *(t3+44k+4*a1+8). Then with k2 = 7*(*(g+0xC+o1)) + *(g+4+o1+... ) as
 * the asm reads it (t0b = *(g+o1+4), t2b = *(g+0xC+o1)): k2 = 7*t2b + t0b, q = *(t3+44k2), r = *(g+0x18),
 * *(g+0xC+80i+4*t0b+0x16C) = *(r + (*(r+4q+4) & ~3) + 0x10). */
void func_00405BA0(s32 arg0) {
    u8 *g;
    u8 *p;
    u8 *t3;
    u8 *r;
    s32 o1;
    s32 o4;
    s32 t0;
    s32 t2;
    s32 k;
    s32 a1;
    s32 q;
    s32 z;
    s32 v;

    o1 = arg0 * 4 + 0x210;
    o4 = arg0 * 4 + 0x260;

    g = D_0042BB74;
    t0 = *(s32 *)(g + o1 + 0xC);
    t2 = *(s32 *)(g + 4 + o1);
    p = g + 4 + arg0 * 4;
    t3 = *(u8 **)(g + o4);
    k = t0 * 7 + t2;
    a1 = *(s32 *)(p + 0x220);
    v = *(s32 *)(t3 + k * 44 + a1 * 4 + 8);
    *(s32 *)(t3 + k * 44) = v;

    g = D_0042BB74;
    t0 = *(s32 *)(g + o1 + 4);
    t2 = *(s32 *)(g + 0xC + o1);
    t3 = *(u8 **)(g + o4);
    k = t2 * 7 + t0;
    q = *(s32 *)(t3 + k * 44);
    r = *(u8 **)(g + 0x18);
    z = (s32)((u32)*(s32 *)(r + q * 4 + 4) & ~3u);
    v = *(s32 *)(r + z + 0x10);
    *(s32 *)(g + 0xC + arg0 * 80 + t0 * 4 + 0x16C) = v;
}
