#include "common.h"

s32 func_0024ACE8(s32 arg0, s32 *arg1, s32 arg2);

void func_0024ADE8(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 temp_v0;
    s32 temp_v0_2;

    for (;;) {
        temp_v0 = *arg2 + 1;
        *arg2 = temp_v0;
        if ((arg3 - 1) < temp_v0) {
            *arg2 = 0;
        }
        temp_v0_2 = *arg2;
        if ((u32)(*(s32 *)((u8 *)arg0 + (temp_v0_2 * 7 + *arg1) * 0x2C) - 0x83) >= 3U) {
            return;
        }
        if (func_0024ACE8(arg0, arg1, temp_v0_2) != 0) {
            return;
        }
    }
}
