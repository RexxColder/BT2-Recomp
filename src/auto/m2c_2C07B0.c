#include "m2c_macros.h"

void func_002C07B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    void *temp_a0;

    temp_a0 = arg0 + (arg1 * 0x74) + 0x1320;
    temp_v0 = M2C_FIELD(temp_a0, s32 *, 0x24);
    if (temp_v0 >= 0) {
        M2C_FIELD(temp_a0, s32 *, 0x24) = (s32) (temp_v0 + arg2);
    }
}
