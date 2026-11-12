#include "common.h"

s32 func_002D5988(s32 arg0, s32 arg1, s32 arg2);

/* 0x002B5CF8(arg0): kind = word written by func_002D5988(arg0, 0xE0, &kind), which must return 1. kind 1 gives
 * 0x21, 3 gives 0x51, 6 gives 0x61; every other kind (and kind >= 9, and a failed call) gives 0x11. */
s32 func_002B5CF8(s32 arg0) {
    s32 kind;

    if (func_002D5988(arg0, 0xE0, (s32)&kind) != 1) {
        return 0x11;
    }
    if ((u32)kind >= 9) {
        return 0x11;
    }
    switch (kind) {
        case 1:
            return 0x21;
        case 3:
            return 0x51;
        case 6:
            return 0x61;
        default:
            return 0x11;
    }
}
