#include "common.h"

/* 0x002C00A8: copies the 16 bytes at arg3 (unaligned ok) to arg0 + arg1 * 0x74 + 0x1320 + arg2 * 16. */
void func_002C00A8(u8 *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u8 *dst = arg0 + arg1 * 0x74 + 0x1320 + arg2 * 16;
    s32 k;

    for (k = 0; k < 16; k++) {
        dst[k] = arg3[k];
    }
}
