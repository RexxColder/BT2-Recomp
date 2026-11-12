#include "m2c_macros.h"

void func_001DD1E8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_a2;
    void *temp_a3;

    temp_a2 = (arg2 * 0x10) + arg1;
    temp_a3 = (arg3 * 0x10) + arg1;
    M2C_FIELD(arg0, s64 *, 0xA0) = (s64) M2C_FIELD(temp_a2, s64 *, 0);
    M2C_FIELD(arg0, s64 *, 0xA8) = (s64) M2C_FIELD(temp_a2, s64 *, 8);
    M2C_FIELD(arg0, s64 *, 0xB0) = (s64) M2C_FIELD(temp_a3, s64 *, 0);
    M2C_FIELD(arg0, s64 *, 0xB8) = (s64) M2C_FIELD(temp_a3, s64 *, 8);
}
