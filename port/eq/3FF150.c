#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

/* 0x003FF150: leaf routine on P = D_3876A4 and G2 = D_0042A590. idx = P->0x64 selects a 56-byte entry of G2->0x274;
 * that entry's word at +0x10 decides: 0 -> P->0x40 &= ~0x20000; bit 8 -> P->0x40 = entry & ~0x20000; idx >= 15 -> the
 * final clear. Otherwise jtbl_0042B900 (15 entries) sets G2->0x208 |= 0x200 for the cases that test the bit 0x20000
 * of P->0x40 (and G2->0x23C == 0, and P->0x58 == 2 for case 14), then the final P->0x40 &= ~0x20000. */
void func_003FF150(void) {
    u8 *g2;
    u8 *tbl;
    s32 idx;
    s32 entry;

    g2 = D_0042A590;
    idx = *(s32 *)(D_3876A4 + 0x64);
    tbl = *(u8 **)(g2 + 0x274);
    entry = *(s32 *)(tbl + idx * 56 + 0x10);
    if (entry == 0) {
        *(s32 *)(D_3876A4 + 0x40) = *(s32 *)(D_3876A4 + 0x40) & ~0x20000;
        return;
    }
    if (entry & 0x8) {
        *(s32 *)(D_3876A4 + 0x40) = entry & ~0x20000;
        return;
    }
    if ((u32)idx < 15) {
        switch (idx) {
        case 0:
        case 5:
        case 7:
        case 9:
        case 13:
            if (*(s32 *)(g2 + 0x23C) == 0 && (*(s32 *)(D_3876A4 + 0x40) & 0x20000)) {
                *(s32 *)(g2 + 0x208) = *(s32 *)(g2 + 0x208) | 0x200;
            }
            break;
        case 2:
        case 6:
            if (*(s32 *)(D_3876A4 + 0x40) & 0x20000) {
                *(s32 *)(g2 + 0x208) = *(s32 *)(g2 + 0x208) | 0x200;
            }
            break;
        case 14:
            if (*(s32 *)(g2 + 0x23C) == 0 && *(s32 *)(D_3876A4 + 0x58) == 2) {
                *(s32 *)(g2 + 0x208) = *(s32 *)(g2 + 0x208) | 0x200;
            }
            break;
        default:
            break;
        }
    }
    *(s32 *)(D_3876A4 + 0x40) = *(s32 *)(D_3876A4 + 0x40) & ~0x20000;
}
