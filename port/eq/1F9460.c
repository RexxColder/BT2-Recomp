#include "common.h"

void func_001F9460(s32 arg0, s32 arg1, u8 *arg2, s8 arg3) {
    *(s8 *)(arg2 + arg1 * 0x14 + arg0 + 0xAFE) = arg3;
}
