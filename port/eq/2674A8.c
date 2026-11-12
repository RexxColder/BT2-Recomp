#include "common.h"

/* 0x002674A8: if (arg0->0xAF0 & 0x2000000): return arg0->0x768 == 0 ? -1 : 5. Otherwise -1 when any of +0x754,
 * +0x758, +0x75C is zero, else (word at arg0 + 0xDF0 + 0x14) - 1. */
s32 func_002674A8(u8 *arg0) {
    if ((*(s32 *)(arg0 + 0xAF0) & 0x2000000) != 0) {
        if (*(s32 *)(arg0 + 0x768) == 0) {
            return -1;
        }
        return 5;
    }
    if (*(s32 *)(arg0 + 0x754) == 0) {
        return -1;
    }
    if (*(s32 *)(arg0 + 0x758) == 0) {
        return -1;
    }
    if (*(s32 *)(arg0 + 0x75C) == 0) {
        return -1;
    }
    return *(s32 *)(arg0 + 0xDF0 + 0x14) - 1;
}
