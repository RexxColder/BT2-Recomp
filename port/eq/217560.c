#include "common.h"

/* 0x00217560: maps a code to a flag word built from range tests: flag 0x1 for 6 <= c < 0x1B, 0x800 for
 * 0x15 <= c < 0x1B, 0x2 for 0x49 <= c < 0x5B, 0x8 for 0xAC <= c < 0xAF, 0x4 for 0x8E <= c < 0xAA (unsigned). */
s32 func_00217560(s32 arg0) {
    s32 r = ((u32)(arg0 - 6) < 0x15) ? 1 : 0;

    if ((u32)(arg0 - 0x15) < 6) {
        r = r | 0x800;
    }
    if ((u32)(arg0 - 0x49) < 0x12) {
        r = r | 0x2;
    }
    if ((u32)(arg0 - 0xAC) < 3) {
        r = r | 0x8;
    }
    if ((u32)(arg0 - 0x8E) < 0x1C) {
        r = r | 0x4;
    }
    return r;
}
