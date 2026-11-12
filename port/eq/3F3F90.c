#include "common.h"

extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern u8 *D_0042A574 __attribute__((section(".data")));

/* Two-byte chain used by cases 2, 4, 5, 6: m = G->0x64, m0 = first state accepted (m0 or m0 + 1), b1 = byte at V + o1,
 * b2 = byte at V + o1 + 1. Needs m - m0 in {0,1}, b1 >= 0, and (b1 > 0 or m == m0); then bits when b2 > 0, or when
 * b2 == 0 and m == m0 + 1. */
#define CHAIN_BITS(m, v, m0, o1, bits) \
    ((((u32)((m) - (m0)) < 2) && (*(s8 *)((v) + (o1)) > 0 || (*(s8 *)((v) + (o1)) == 0 && (m) == (m0))) && \
      (*(s8 *)((v) + (o1) + 1) > 0 || (*(s8 *)((v) + (o1) + 1) == 0 && (m) == (m0) + 1))) ? (bits) : 0)

/* 0x003F3F90: returns 0 if the byte at V + G->0x64 + 0x2C0 is nonzero (V = D_00387F2C, G = D_003876A4). Otherwise a
 * 15-step loop over records of 56 bytes at *(D_0042A574 + 0x13C) + 56*i; each value x < 10 selects a case (jtbl_0042AB80)
 * that ORs bits into an accumulator, returned at the end. Nothing is stored. */
s32 func_003F3F90(void) {
    u8 *v;
    s32 m;
    s32 a2;
    s32 i;
    s32 x;
    u8 *tab;

    v = D_00387F2C;
    m = *(s32 *)(D_003876A4 + 0x64);
    if (*(s8 *)(v + m + 0x2C0) != 0) {
        return 0;
    }

    a2 = 0;
    for (i = 0; i < 15; i++) {
        tab = *(u8 **)(D_0042A574 + 0x13C);
        x = *(s32 *)(tab + 56 * i);
        if ((u32)x >= 0xA) {
            continue;
        }
        switch (x) {
        case 0:
            break;
        case 1:
            if (m == 0 && *(s8 *)(v + 0x2C0) >= 0) {
                a2 |= 0x6;
            }
            break;
        case 2:
            a2 |= CHAIN_BITS(m, v, 1, 0x2C1, 0x38);
            break;
        case 3:
            if (m == 3 && *(s8 *)(v + 0x2C3) >= 0) {
                a2 |= 0x40;
            }
            break;
        case 4:
            a2 |= CHAIN_BITS(m, v, 4, 0x2C4, 0x180);
            break;
        case 5:
            a2 |= CHAIN_BITS(m, v, 7, 0x2C7, 0x600);
            break;
        case 6:
            a2 |= CHAIN_BITS(m, v, 9, 0x2C9, 0x800);
            break;
        case 7:
            if (m == 0xB) {
                a2 |= 0x1000;
            }
            break;
        case 8:
            if (m == 0xC) {
                a2 |= 0x2000;
            }
            break;
        case 9:
            if (m == 0xD) {
                a2 |= 0x4000;
            }
            break;
        }
    }
    return a2;
}
