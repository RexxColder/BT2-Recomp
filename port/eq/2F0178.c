#include "common.h"

/* 0x002F0178: reset of a record at arg0: +0x3C = -1, +0x38 = 0x7FFFFFFF, +0x2C/30/34/40/44/98/A0/A4 = 0, byte +0x3 = 0. */
void func_002F0178(u8 *arg0) {
    *(s32 *)(arg0 + 0x3C) = -1;
    *(s32 *)(arg0 + 0x38) = 0x7FFFFFFF;
    *(s32 *)(arg0 + 0xA4) = 0;
    *(s32 *)(arg0 + 0x98) = 0;
    *(s32 *)(arg0 + 0x2C) = 0;
    *(s32 *)(arg0 + 0x30) = 0;
    *(s32 *)(arg0 + 0x34) = 0;
    *(s32 *)(arg0 + 0x40) = 0;
    *(s32 *)(arg0 + 0x44) = 0;
    *(u8 *)(arg0 + 0x3) = 0;
    *(s32 *)(arg0 + 0xA0) = 0;
}
