#include "common.h"

void func_002D2EB8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(s32 *)(arg0 + arg1 * 0x44 + arg2 * 4 + 0x1F44) = arg3;
    *(s32 *)(arg0 + arg3 * 0x74 + 0x135C) = arg1;
}
