#include "common.h"

void func_002D1F28(s32 arg0, u8 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_t0;

    temp_t0 = *(s32 *)(arg1 + 0xC);
    *arg2 = (((((*(s32 *)(arg1 + 0x10) * 0x1E) + (temp_t0 / 10)) * 2) + ((*(s32 *)(arg1 + 8) * 0x34B54) + (temp_t0 * 0xE0E)) + (*(s32 *)(arg1 + 0x14) + *(s32 *)(arg1 + 0x18))) * 0x3E8) + (*(s16 *)(arg1 + 0x1E) * 0x1F4);
    *arg3 = arg0;
}
