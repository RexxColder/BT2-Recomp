#include "common.h"

/* 0x00217490: the word at 0xC10 + 4 * i of arg0, i = (word at +0x1010) - 1, or 0xFF when that is negative. */
s32 func_00217490(u8 *arg0) {
    s32 i = *(s32 *)(arg0 + 0x1010) - 1;

    if (i < 0) {
        i = 0xFF;
    }
    return *(s32 *)(arg0 + i * 4 + 0xC10);
}
