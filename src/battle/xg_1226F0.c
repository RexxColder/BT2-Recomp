#include "m2c_macros.h"

/* Sets word +0x2C of the sub-object at arg0+0xFE0 to arg1 and clears words +0x30 and +0x34. */
void func_001226F0(s32 arg0, s32 arg1) {
    void *temp_a0;

    temp_a0 = arg0 + 0xFE0;
    M2C_FIELD(temp_a0, s32 *, 0x2C) = arg1;
    M2C_FIELD(temp_a0, s32 *, 0x30) = 0;
    M2C_FIELD(temp_a0, s32 *, 0x34) = 0;
}
