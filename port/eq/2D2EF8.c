#include "common.h"

void func_002D2EF8(s32 arg0, s32 arg1, s32 arg2) {
    *(s32 *)((u8 *)arg0 + arg2 * 0x44 + 0x1F40) = arg1;
    *(s32 *)((u8 *)arg0 + arg1 * 0x74 + 0x1360) = arg2;
}
