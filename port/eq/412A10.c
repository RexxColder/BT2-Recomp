#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));

/* 0x00412A10: per-index table update on G = D_0042BB7C for index i = arg0. A word at G + 0x29C + 4i gives a = w and
 * c = (a < 2) ? 1 : a; the record at R(k) = G + 0xC + 4 * k (k = 2i + c) has f230 / f240 / f250 fields. Three steps:
 * (1) T = *(G + 0x2D8 + 4i): *(T + 44V) = *(T + 44V + 4 * f250(R(2i+c)) + 8) with V = 7 * f240 + f230 of R(2i+c);
 * (2) Q = *(G + 0x28): Z = *(T + 44 * V2), V2 = 7 * f240(R(2i+c)) + f230(R(2i+c)) (c from the same word), and
 *     *(G + 4 * (20i + f230(R(2i+a))) + 0x190) = *(Q + 4Z + (*(Q + 4Z + 4) >> 2 << 2) + 0x10), a = raw word;
 * (3) *(G + 4 * (7 * f240 + 134i + f230) + 0x3304) = f250 of R(2i+c) with the same c. */
void func_00412A10(s32 arg0) {
    u8 *g;
    u8 *t3;
    u8 *t;
    u8 *p;
    u8 *q;
    s32 a;
    s32 c;
    s32 f240;
    s32 f230;
    s32 f250;
    s32 v;
    s32 z;
    s32 i;

    i = arg0;
    g = D_0042BB7C;
    t3 = g + 0xC;

    /* (1) */
    a = *(s32 *)(t3 + 4 * i + 0x290);
    t = *(u8 **)(g + 0x2D8 + 4 * i);
    c = (a < 2) ? 1 : a;
    p = t3 + 4 * (2 * i + c);
    f240 = *(s32 *)(p + 0x240);
    f230 = *(s32 *)(p + 0x230);
    v = 7 * f240 + f230;
    f250 = *(s32 *)(p + 0x250);
    *(s32 *)(t + 44 * v) = *(s32 *)(t + 44 * v + 4 * f250 + 8);

    /* (2) */
    t = *(u8 **)(g + 0x2D8 + 4 * i);
    a = *(s32 *)(t3 + 4 * i + 0x290);
    q = *(u8 **)(g + 0x28);
    c = (a < 2) ? 1 : a;
    p = t3 + 4 * (2 * i + c);
    f240 = *(s32 *)(p + 0x240);
    f230 = *(s32 *)(p + 0x230);
    v = 7 * f240 + f230;
    z = *(s32 *)(t + 44 * v);
    p = t3 + 4 * (2 * i + a);
    f230 = *(s32 *)(p + 0x230);
    *(s32 *)(g + 4 * (20 * i + f230) + 0x190) =
        *(s32 *)(q + 4 * z + ((*(u32 *)(q + 4 * z + 4) >> 2) << 2) + 0x10);

    /* (3) */
    a = *(s32 *)(t3 + 4 * i + 0x290);
    c = (a < 2) ? 1 : a;
    p = t3 + 4 * (2 * i + c);
    f240 = *(s32 *)(p + 0x240);
    f230 = *(s32 *)(p + 0x230);
    v = 7 * f240 + 134 * i + f230;
    f250 = *(s32 *)(p + 0x250);
    *(s32 *)(g + 4 * v + 0x3304) = f250;
}
