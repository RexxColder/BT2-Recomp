#include "common.h"

extern u8 *D_00387B00;

s32 func_002824A0(u32 arg0) {
    u32 idx;

    idx = (arg0 >= 4U) ? 0U : arg0;
    return *(u8 *)(D_00387B00 + idx * 0x60 + 0x58) & 1;
}
