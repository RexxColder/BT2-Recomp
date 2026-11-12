#include "m2c_macros.h"

void func_002D7058(void *arg0, u32 arg1) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = ((s32) ((arg1 >> 0x1F) + arg1) >> 1) * 2;
    temp_v1 = temp_v0 >> 1;
    M2C_FIELD(arg0, s32 *, 0x1C) = temp_v1;
    M2C_FIELD(arg0, s32 *, 0x2C) = temp_v1;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_v0;
}
