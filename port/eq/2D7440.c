#include "common.h"

void func_002D7440(void *arg0, s32 *arg1, s32 *arg2) {
    u8 *temp_a0;

    temp_a0 = (u8 *)arg0 + 0x8;
    if (*(s32 *)temp_a0 == 1) {
        *arg2 = *(s32 *)(temp_a0 + 8);
        *arg1 = *(s32 *)(temp_a0 + 4);
        return;
    }
    *arg1 = 0;
    *arg2 = 0;
}
