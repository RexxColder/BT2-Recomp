#include "common.h"

extern u8 *D_0042A570 __attribute__((section(".data")));

/* 0x003F0B00: G = D_0042A570, i = arg0. Let o1 = 4i+0x220, o3 = 4i+0x210, o5 = 4i+0x250; t6 = *(G+o5+8) (pointer).
 * k = 7*(*(G+o1+4)) + *(G+o3+0xC); *(t6+44k) = *(t6+44k+4*(*(G+o1+0xC))+8).
 * Then k' = 7*(*(G+o1+4)) + *(G+o3+0xC) again, q = *(t6+44k'), r = *(G+0x18),
 * *(G+80i+4*(*(G+o3+0xC))+0x17C) = *(r + (*(r+4q+4) & ~3) + 0x10). */
void func_003F0B00(s32 arg0) {
    u8 *g;
    s32 o1;
    s32 o3;
    s32 o5;
    s32 t0;
    s32 t2;
    s32 k;
    s32 a1;
    u8 *t6;
    u8 *r;
    u8 *p;
    s32 q;
    s32 z;
    s32 v;

    g = D_0042A570;
    o1 = arg0 * 4 + 0x220;
    o3 = arg0 * 4 + 0x210;
    o5 = arg0 * 4 + 0x250;

    t0 = *(s32 *)(g + o1 + 4);
    t2 = *(s32 *)(g + o3 + 0xC);
    t6 = *(u8 **)(g + o5 + 8);
    k = t0 * 7 + t2;
    a1 = *(s32 *)(g + o1 + 0xC);
    v = *(s32 *)(t6 + k * 44 + a1 * 4 + 8);
    *(s32 *)(t6 + k * 44) = v;

    g = D_0042A570;
    t0 = *(s32 *)(g + o1 + 4);
    t2 = *(s32 *)(g + o3 + 0xC);
    t6 = *(u8 **)(g + o5 + 8);
    k = t0 * 7 + t2;
    q = *(s32 *)(t6 + k * 44);
    r = *(u8 **)(g + 0x18);
    p = r + q * 4;
    z = (s32)((u32)*(s32 *)(p + 4) & ~3u);
    v = *(s32 *)(r + z + 0x10);
    *(s32 *)(g + arg0 * 80 + t2 * 4 + 0x17C) = v;
}
