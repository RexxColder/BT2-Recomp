#include "common.h"

/* 0x002F2C30: stores a2 at +0x18 and a1 at +0x1C of a0, returns 1. */
s32 func_002F2C30(void *a0, s32 a1, s32 a2) {
    *(s32 *)((u8 *)a0 + 0x18) = a2;
    *(s32 *)((u8 *)a0 + 0x1C) = a1;
    return 1;
}
