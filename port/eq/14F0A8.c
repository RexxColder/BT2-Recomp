#include "common.h"

s64 func_0014F0A8(s32 arg0, u8 **tbl, u8 *bits, s32 row, s32 col, s32 wantCheck,
                  s32 flagA, s32 mask) {
    u8 *slot;
    u8 *entry;
    u8 bitsVal;
    s32 result;
    s32 idx;

    slot = *tbl + 272 * row + 32 * col;
    entry = slot + 16;
    result = 0;

    if (flagA != 0) {
        result = 2;
    } else {
        if (mask & 2) {
            result = slot[17] == 0;
        }
        if (mask & 4) {
            if (entry[1] == 2) {
                result |= 1;
            }
            if (entry[2] == 2) {
                result |= 2;
            }
        }
        if (mask & 0x10) {
            if (entry[1] == 4) {
                result |= 1;
            }
            if (entry[2] == 4) {
                result |= 2;
            }
        }
        if (mask & 0x20) {
            if (entry[1] == 5) {
                result |= 1;
            }
            if (entry[2] == 5) {
                result |= 2;
            }
        }
        if (mask & 0x40) {
            if (entry[1] == 1) {
                result |= 1;
            }
            if (entry[2] == 1) {
                result |= 2;
            }
        }
        if (wantCheck != 0) {
            if (entry[1] == 3) {
                result |= 1;
            } else if (row != 5 || (entry[7] & 0x10) == 0) {
                result |= 2;
            }
        }
    }

    idx = 8 * row;
    bitsVal = bits[col + idx];
    if (bitsVal & 2) {
        result &= ~1;
    }
    if (bitsVal & 4) {
        result &= ~2;
    }

    if (entry[7] & 2) {
        result &= ~8;
    } else {
        if ((bitsVal & 2) == 0) {
            return result;
        }
        if (entry[1] != 3) {
            result |= 8;
        }
    }

    if ((bitsVal & 2) != 0 && (bitsVal & 4) == 0) {
        result |= 0x20;
        if (entry[0] == 2) {
            return (s64)(result | 0x40);
        }
    }

    return (s64)result;
}
