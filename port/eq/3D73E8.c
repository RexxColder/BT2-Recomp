#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_004261F8[] __attribute__((section(".data")));
extern u8 D_00426198[] __attribute__((section(".data")));
extern u8 D_004261B8[] __attribute__((section(".data")));

/* word lookup: *(s32 *)(Q + (w & ~3) + 0x10) with w = *(u32 *)(Q + idx * 4 + 4) */
#define LOOKUP(q, idx) (*(s32 *)((q) + (*(u32 *)((q) + (idx) * 4 + 4) & ~3u) + 0x10))

/* 0x003D73E8: fills P->0x1B0 + 4 * t[i] for i < P->0x331C with LOOKUP(P->0x18, u16 at P + 0x333E + 0x20 * i), where t is
 * a table copied to the frame: D_00426198 (mode 0, 0x20 bytes), D_004261B8 (mode 1, 0x40 bytes, at fr + 0x20) or
 * D_004261F8 (mode 2 or 3, 0x34 bytes). Other modes return. */
void func_003D73E8(u8 *P) {
    u8 fr[0x60];
    u8 *tbl;
    u8 *Q;
    s32 mode;
    s32 cnt;
    s32 i;
    s32 idx;

    mode = *(s32 *)(D_3876A4 + 0x90);
    if (mode == 1) {
        cnt = *(s32 *)(P + 0x331C);
        memcpy(fr + 0x20, D_004261B8, 0x40);
        tbl = fr + 0x20;
    } else if (mode < 2) {
        if (mode != 0) {
            return;
        }
        cnt = *(s32 *)(P + 0x331C);
        memcpy(fr, D_00426198, 0x20);
        tbl = fr;
    } else if (mode < 4) {
        cnt = *(s32 *)(P + 0x331C);
        memcpy(fr, D_004261F8, 0x34);
        tbl = fr;
    } else {
        return;
    }

    Q = *(u8 **)(P + 0x18);
    for (i = 0; i < cnt; i++) {
        idx = *(u16 *)(P + 0x333E + 0x20 * i);
        *(s32 *)(P + 0x1B0 + *(s32 *)(tbl + i * 4) * 4) = LOOKUP(Q, idx);
    }
}
