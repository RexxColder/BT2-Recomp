#include "common.h"

void *func_00202DC0(s32 arg0);

s32 func_001F9670(s32 arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0_2 = *(s32 *)((u8 *)func_00202DC0(arg0) + 0x1C);
    temp_v0 = (temp_v0_2 >= 0x32) ? 0x31 : temp_v0_2;
    return (temp_v0 < 0) ? 0 : temp_v0;
}
