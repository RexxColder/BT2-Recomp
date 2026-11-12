#include "common.h"

/* 0x0011FD48: resets the record at arg0 + 0x38: word 0 = -1, word +4 = 1, words +0x108 / +0x10C / +0x110 / +0x114 /
 * +0x118 = 0 and word +0x11C = -1 (relative to the record). */
void func_0011FD48(u8 *arg0) {
    u8 *p = arg0 + 0x38;

    *(s32 *)(p + 0x11C) = -1;
    *(s32 *)(p + 4) = 1;
    *(s32 *)(p + 0x10C) = 0;
    *(s32 *)(arg0 + 0x38) = -1;
    *(s32 *)(p + 0x110) = 0;
    *(s32 *)(p + 0x114) = 0;
    *(s32 *)(p + 0x118) = 0;
    *(s32 *)(p + 0x108) = 0;
}
