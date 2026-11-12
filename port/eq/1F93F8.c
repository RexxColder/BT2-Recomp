#include "common.h"

/* 0x001F93F8: two stores into the table at arg0: a word at 4 * (5 * arg1 + arg2) + 0xB04 = arg4, and a byte at
 * arg0 + arg2 + 20 * arg1 + 0xAFA = arg3. */
void func_001F93F8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    *(s32 *)(arg0 + (5 * arg1 + arg2) * 4 + 0xB04) = arg4;
    *(u8 *)(arg0 + arg2 + arg1 * 20 + 0xAFA) = (u8)arg3;
}
