#include "common.h"

/* 0x001E6DE8: copies words 0..3 of arg1 to arg0 + 0xC..0x18, arg1 +0x30 -> arg0 +0x1C, arg1 +0x34 -> arg0 +0x20,
 * sets arg0 +0x24 = 1 and clears arg0 +0x30, +0x34, +0x38, +0x3C. */
void func_001E6DE8(u8 *arg0, u8 *arg1) {
    s32 k;

    for (k = 0; k < 4; k++) {
        *(s32 *)(arg0 + 0xC + k * 4) = *(s32 *)(arg1 + k * 4);
    }
    *(s32 *)(arg0 + 0x1C) = *(s32 *)(arg1 + 0x30);
    *(s32 *)(arg0 + 0x20) = *(s32 *)(arg1 + 0x34);
    *(s32 *)(arg0 + 0x24) = 1;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x38) = 0;
    *(s32 *)(arg0 + 0x3C) = 0;
}
