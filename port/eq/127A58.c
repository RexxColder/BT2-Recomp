#include "common.h"

s32 func_00127A58(void *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_2;

    if (*(s32 *)((u8 *)arg0 + 0x68) != 0) {
        return 0;
    }
    temp_a0 = *(u8 **)((u8 *)arg0 + 0x64);
    if (temp_a0 == NULL) {
        return 0;
    }
    temp_a0_2 = *(u8 **)(temp_a0 + 0x20);
    if (*(s32 *)(temp_a0_2 + 0x4) != 0) {
        return *(s32 *)(temp_a0_2 + 0x8) == 7;
    }
    if (*(s32 *)(temp_a0_2 + 0x8) == 4) {
        return 1;
    }
    return 0;
}
