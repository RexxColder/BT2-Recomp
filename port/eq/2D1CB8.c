#include "common.h"

void func_002D1CB8(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    *arg2 = (*(s32 *)(arg1 + 0x10) * arg0)
          + (*(s16 *)(arg1 + 0x1E) * 0x1F4)
          + ((*(s32 *)(arg1 + 0x8) * arg0 * 0xE10)
             + (*(s32 *)(arg1 + 0xC) * arg0 * 0x3C)
             + ((*(s32 *)(arg1 + 0x14) + *(s32 *)(arg1 + 0x18)) * 0x3E8));
    *arg3 = arg0;
}
