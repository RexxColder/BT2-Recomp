#include "common.h"

extern u8 *D_004263E8 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

extern void *memset(void *dst, s32 c, u32 n);

/* 0x003D84C8: table rebuild on G = D_004263E8. Phase 1 fills 4 blocks (stride 0x1B24, base 0x17C) of 0x242 + 1 entries
 * of 12 bytes with -1. Phase 2 clears G + 0x6E0C (16 bytes). Phase 3, for i in 0..0x242: finds the index idx of the
 * first entry of the table at G->0x6E1C (count G->0x6E20, 12-byte entries) whose word 0 or word 1 equals i; when idx is
 * neither the count nor 4 and a3 (word 8 of the entry at G->0x14 + 0x30 * i, flags word & 0x41 must be 0) is < 4, with
 * K = G[0x6E0C + 4 * a3] < 0x243: writes i, *(D_00387F2C + 0x1F30 + 4i) (u16) and (s16) at +0x180/+0x184 of the 12-byte
 * entry K in block a3, decrements the +0x184 cell of that entry twice over the words G[0x6E24], G[0x6E28] that equal i
 * (clamped at 0), and increments G[0x6E0C + 4 * a3]. */
void func_003D84C8(void) {
    s32 blk;
    s32 k;
    s32 i;
    s32 idx;
    s32 n;
    s32 a3;
    s32 a3p;
    s32 kk;
    s32 j;
    u8 *e;
    u8 *p;
    s32 off;

    memset(D_004263E8 + 0x17C, 0, 0x6C90);
    for (blk = 0; blk < 4; blk++) {
        for (k = 0; k <= 0x241; k++) {
            *(s32 *)(D_004263E8 + blk * 0x1B24 + 0x17C + k * 0xC) = -1;
        }
    }

    memset(D_004263E8 + 0x6E0C, 0, 0x10);

    for (i = 0; i < 0x243; i++) {
        off = 0x1F30 + 4 * i;
        e = *(u8 **)(D_004263E8 + 0x14) + 0x30 * i;
        if (*(s32 *)e & 0x41) {
            continue;
        }
        a3 = *(s32 *)(e + 8);

        idx = 0;
        n = *(s32 *)(D_004263E8 + 0x6E20);
        if (n > 0) {
            p = *(u8 **)(D_004263E8 + 0x6E1C);
            for (;;) {
                if (*(s32 *)p == i) {
                    break;
                }
                if (*(s32 *)(p + 4) == i) {
                    break;
                }
                idx++;
                p += 0xC;
                if (idx >= n) {
                    break;
                }
            }
        }

        if (idx == *(s32 *)(D_004263E8 + 0x6E20) || a3 == 4 || a3 >= 4) {
            continue;
        }

        kk = *(s32 *)(D_004263E8 + 0x6E0C + 4 * a3);
        if (kk >= 0x243) {
            continue;
        }

        a3p = a3 * 0x1B24;
        *(s32 *)(D_004263E8 + 12 * kk + a3p + 0x17C) = i;
        *(s32 *)(D_004263E8 + 12 * kk + a3p + 0x180) = *(u16 *)(D_00387F2C + off);
        *(s32 *)(D_004263E8 + 12 * kk + a3p + 0x184) = *(s16 *)(D_00387F2C + off + 2);

        for (j = 0; j < 2; j++) {
            if (*(s32 *)(D_004263E8 + 0x6E24 + 4 * j) == i) {
                *(s32 *)(D_004263E8 + 12 * kk + a3p + 0x184) -= 1;
                if (*(s32 *)(D_004263E8 + 12 * kk + a3p + 0x184) < 0) {
                    *(s32 *)(D_004263E8 + 12 * kk + a3p + 0x184) = 0;
                }
            }
        }
        *(s32 *)(D_004263E8 + 0x6E0C + 4 * a3) += 1;
    }
}
