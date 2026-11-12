#include "common.h"

/* 0x001CB5F0: copy two 16-byte entries (a1[a2], a1[a3]) to +0xA0/+0xB0; store a3 at +4. */
void func_001CB5F0(u8 *a0, u8 *a1, s32 a2, s32 a3) {
    s64 *src0 = (s64 *)(a1 + a2 * 16);
    s64 *src1 = (s64 *)(a1 + a3 * 16);
    *(s64 *)(a0 + 0xA0) = src0[0];
    *(s64 *)(a0 + 0xA8) = src0[1];
    *(s64 *)(a0 + 0xB0) = src1[0];
    *(s64 *)(a0 + 0xB8) = src1[1];
    *(s32 *)(a0 + 4) = a3;
}
