#include "common.h"

void func_00210618(void *arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_v1;

    temp_a2 = arg1 - 0x3C1B;
    if (temp_a2 < 0) {
        temp_a2 = 0;
    }
    if ((u32)temp_a2 < 0x20U) {
        temp_v1 = temp_a2 >> 3;
        *((u8 *)arg0 + temp_v1 + 0x364) = (u8)(*((u8 *)arg0 + temp_v1 + 0x364) | (1 << (temp_a2 - temp_v1 * 8)));
    }
}
