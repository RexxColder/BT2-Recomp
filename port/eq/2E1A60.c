#include "common.h"

void func_002E1A60(s32 *arg0, s32 *arg1, u32 arg2) {
    s32 *dst;
    s32 *src;
    u32 rem;
    u32 blocks;
    s32 i;

    dst = arg0;
    src = arg1;
    rem = arg2 & 0xF;
    if (rem != 0) {
        do {
            *dst = *src;
            src += 1;
            rem -= 1;
            dst += 1;
        } while (rem != 0);
    }
    blocks = arg2 >> 4;
    while (blocks != 0) {
        for (i = 0; i < 16; i++) {
            dst[i] = src[i];
        }
        dst += 16;
        src += 16;
        blocks -= 1;
    }
}
