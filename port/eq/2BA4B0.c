#include "common.h"

void func_002BA4B0(u8 *arg0, s32 *arg1, s32 *arg2) {
    u8 *temp_a0;
    temp_a0 = arg0 + 0x194;
    *arg2 = *(s32 *)(temp_a0 + 8);
    *arg1 = *(s32 *)(temp_a0 + 4);
}
