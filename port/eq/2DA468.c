#include "common.h"

void func_002DA468(u8 *arg0, u8 *arg1, u32 arg2) {
    u8 *dst;
    u8 *src;
    s32 count;
    u32 blocks;
    s32 i;

    dst = arg0;
    src = arg1;
    count = arg2 & 0x1F;
    while (count != 0) {
        *dst = *src;
        dst += 1;
        src += 1;
        count -= 1;
    }

    blocks = arg2 >> 5;
    while (blocks != 0) {
        for (i = 0; i < 32; i++) {
            dst[i] = src[i];
        }
        dst += 0x20;
        src += 0x20;
        blocks -= 1;
    }
}
