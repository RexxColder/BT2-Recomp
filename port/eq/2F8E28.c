#include "common.h"

/* 0x002F8E28: if the word at +0xC is 0, stores arg4 at +0x24, arg1 at +0x18, arg2 at +0x1C, arg3 at +0x20 and 1 at
 * +0x14, and returns 1; otherwise returns 0. */
s32 func_002F8E28(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (*(s32 *)(arg0 + 0xC) != 0) {
        return 0;
    }
    *(s32 *)(arg0 + 0x24) = arg4;
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x1C) = arg2;
    *(s32 *)(arg0 + 0x14) = 1;
    *(s32 *)(arg0 + 0x20) = arg3;
    return 1;
}
