#include "m2c_macros.h"

void func_001EC3A0(void *arg0, s32 arg1) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x68) & ~1;
    M2C_FIELD(arg0, s32 *, 0x68) = temp_v1;
    if (arg1 & 0xFF) {
        M2C_FIELD(arg0, s32 *, 0x68) = (s32) (temp_v1 | 1);
    }
}
