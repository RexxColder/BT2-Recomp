#include "common.h"

extern u8 *D_0042732C __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

void *memset(void *arg0, s32 arg1, u32 arg2);

/* 0x003DC998: G = D_0042732C. G->0x730 = 0, G->0x114 = 0, memset(G+0x118, 0, 0x618). Then for t0 = 0..0x81 with
 * o = 0, 0xC, ...: idx = G->0x1C[t0]; skip idx < 0; p = *D_00387F2C + (idx < 0x62 ? idx*4+0x25E8 : idx*4+0x25E4);
 * skip when *(s16*)(p+2) <= 0; break when t0 >= G->0x18. Otherwise: if G->0x114 == 0, G->0x114 = G+o+0x118;
 * record at G+o+0x118 links the previous one (s1), G+o+0x11C = idx, G->0x730++, previous record's +8 = G+o+0x118,
 * s1 = G+o+0x118. Finally G->0x110 = 0. */
void func_003DC998(void) {
    u8 *g = D_0042732C;
    u8 *s1 = 0;
    s32 t0;
    s32 o;

    *(s32 *)(g + 0x730) = 0;
    *(s32 *)(g + 0x114) = 0;
    memset(g + 0x118, 0, 0x618);

    o = 0;
    for (t0 = 0; t0 < 0x82; t0++, o += 0xC) {
        s32 idx = *(s32 *)(*(u8 **)(g + 0x1C) + t0 * 4);
        u8 *p;

        if (idx < 0) {
            continue;
        }
        if (idx < 0x62) {
            p = D_00387F2C + idx * 4 + 0x25E8;
        } else {
            p = D_00387F2C + idx * 4 + 0x25E4;
        }
        if (*(s16 *)(p + 2) <= 0) {
            continue;
        }
        if (t0 >= *(s32 *)(g + 0x18)) {
            break;
        }
        if (*(s32 *)(g + 0x114) == 0) {
            *(u8 **)(g + 0x114) = g + o + 0x118;
        }
        *(u8 **)(g + o + 0x118) = s1;
        *(s32 *)(g + o + 0x11C) = idx;
        *(s32 *)(g + 0x730) = *(s32 *)(g + 0x730) + 1;
        if (s1 != 0) {
            *(u8 **)(s1 + 8) = g + o + 0x118;
        }
        s1 = g + o + 0x118;
    }
    *(s32 *)(g + 0x110) = 0;
}
