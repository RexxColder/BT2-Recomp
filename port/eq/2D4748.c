#include "common.h"

s32 func_002D45E8(s32 arg0, s32 arg1);
s32 func_002D4888(s32 arg0, s32 arg1);

void func_002D4748(u8 *arg0, s32 arg1, s32 *arg2) {
    s32 temp_s0;

    *arg2 = 0;
    temp_s0 = *(s32 *)(arg0 + 0x4);
    if (func_002D45E8((s32)arg0, arg1) != 0) {
        if (func_002D4888(temp_s0, arg1 & 0xFF) != 0) {
            *arg2 = 1;
            return;
        }
        *arg2 = 0;
    }
}
