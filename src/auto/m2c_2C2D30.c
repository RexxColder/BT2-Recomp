#include "m2c_macros.h"

void func_002C2D30(s32 arg0) {
    void *temp_a0;
    void *temp_a1;

    temp_a1 = arg0 + 0x98;
    temp_a0 = arg0 + 0x90C;
    M2C_FIELD(temp_a0, s32 *, 0x24) = (s32) M2C_FIELD(temp_a1, s32 *, 4);
    M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(temp_a1, s32 *, 8);
    M2C_FIELD(temp_a0, s32 *, 0x2C) = (s32) M2C_FIELD(temp_a1, s32 *, 0xC);
}
