#include "common.h"

/* 0x00260108: flips the double buffer index at +0x58 (0 <-> 1) and points the two 0x20-byte buffers at +0x50 / +0x54
 * (buffer + 0x10). GUESS/layout: the pointers are 32-bit in the original and are stored as u8 * here. */
void func_00260108(u8 *arg0) {
    s32 idx = *(s32 *)(arg0 + 0x58);
    s32 nidx = idx ^ 1;

    *(u8 **)(arg0 + 0x50) = arg0 + idx * 32 + 0x10;
    *(u8 **)(arg0 + 0x54) = arg0 + nidx * 32 + 0x10;
    *(s32 *)(arg0 + 0x58) = nidx;
}
