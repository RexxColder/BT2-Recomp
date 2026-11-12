#include "common.h"

s32 func_0024ACE8(s32 arg0, s32 *arg1, s32 arg2);

void func_0024AEA0(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 temp_a2;
    s32 temp_v1;

    for (;;) {
        temp_v1 = *arg2 - 1;
        temp_a2 = (temp_v1 >= 0) ? temp_v1 : (arg3 - 1);
        *arg2 = temp_a2;
        if ((u32)(*(s32 *)((u8 *)arg0 + (temp_a2 * 7 + *arg1) * 0x2C) - 0x83) >= 3U) {
            return;
        }
        if (func_0024ACE8(arg0, arg1, temp_a2) != 0) {
            return;
        }
    }
}
