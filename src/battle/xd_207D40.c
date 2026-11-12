/*
 * BtlPad_TestStep (0x207D40): own file because its switch compiles to a jump table (jtbl_0036F960, 10 words at
 * 0x36F960). Inferred: keys 0 / 1 are one direction, 2 / 3 the other; "press" = bit in word +0x50 and counter
 * +0x11C below 7, "hold" = bit in word +0x48 and counter exactly 6; for 2 / 3 key 7 must not be in word +0x48.
 */
#include "common.h"

typedef struct BtlPadChr BtlPadChr;

extern u32 BtlPad_Test48(BtlPadChr *chr, s32 key);
extern u32 BtlPad_Test50(BtlPadChr *chr, s32 key);
extern s32 BtlPad_GetCount11C(BtlPadChr *chr, s32 key);

/* Tests one of four key-and-counter conditions (kind 0..3); 0 for kinds 4..9 and anything else. */
s32 BtlPad_TestStep(BtlPadChr *chr, s32 kind) {
    switch (kind) {
    case 0:
        if (!BtlPad_Test50(chr, 0)) {
            return 0;
        }
        if (BtlPad_GetCount11C(chr, 0) >= 7) {
            return 0;
        }
        return 1;
    case 1:
        if (!BtlPad_Test48(chr, 0)) {
            return 0;
        }
        if (BtlPad_GetCount11C(chr, 0) != 6) {
            return 0;
        }
        return 1;
    case 2:
        if (!BtlPad_Test50(chr, 1)) {
            return 0;
        }
        if (BtlPad_GetCount11C(chr, 1) >= 7) {
            return 0;
        }
        if (BtlPad_Test48(chr, 7)) {
            return 0;
        }
        return 1;
    case 3:
        if (!BtlPad_Test48(chr, 1)) {
            return 0;
        }
        if (BtlPad_GetCount11C(chr, 1) != 6) {
            return 0;
        }
        if (BtlPad_Test48(chr, 7)) {
            return 0;
        }
        return 1;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        break;
    }
    return 0;
}
