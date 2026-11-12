#include "m2c_macros.h"

void func_002608E8(s32 arg0) {
    s32 temp_v1;
    void *temp_a0;

    temp_a0 = arg0 + 0xEF0;
    temp_v1 = M2C_FIELD(temp_a0, s32 *, 0x58);
    M2C_FIELD(temp_a0, s32 *, 0x54) = 0;
    M2C_FIELD(temp_a0, s32 *, 0x58) = (s32) (temp_v1 ^ 1);
    M2C_FIELD(temp_a0, void **, 0x50) = (void *) (temp_a0 + (temp_v1 << 5) + 0x10);
}
