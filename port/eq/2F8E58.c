#include "common.h"

/* 0x002F8E58: as 0x002F8E28, but stores 2 at +0x14. */
s32 func_002F8E58(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (*(s32 *)(arg0 + 0xC) != 0) {
        return 0;
    }
    *(s32 *)(arg0 + 0x24) = arg4;
    *(s32 *)(arg0 + 0x18) = arg1;
    *(s32 *)(arg0 + 0x1C) = arg2;
    *(s32 *)(arg0 + 0x14) = 2;
    *(s32 *)(arg0 + 0x20) = arg3;
    return 1;
}
