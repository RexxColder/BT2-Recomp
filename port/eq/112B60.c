#include "common.h"

void func_00112B60(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    s64 temp_a0;
    s32 temp_a1;

    temp_a1 = ((s32)((u32)arg1 << 16) >> 10) + *(s32 *)(arg0 + 0x10);
    temp_a0 = *(s64 *)(temp_a1 + 0x30);
    if (arg2 != NULL) {
        *arg2 = 1 << (((s64)(temp_a0 << 6) >> 0x20) & 0xF);
    }
    if (arg3 != NULL) {
        *arg3 = 1 << (((s64)(temp_a0 * 4) >> 0x20) & 0xF);
    }
}
