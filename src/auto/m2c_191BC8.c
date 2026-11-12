#include "m2c_macros.h"

void func_00191BC8(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_a2;
    void *temp_a3;

    temp_a2 = (arg2 * 0x10) + arg1;
    temp_a3 = (arg3 * 0x10) + arg1;
    M2C_FIELD(arg0, s64 *, 0x1C8) = (s64) M2C_FIELD(temp_a2, s64 *, 0);
    M2C_FIELD(arg0, s64 *, 0x1D0) = (s64) M2C_FIELD(temp_a2, s64 *, 8);
    M2C_FIELD(arg0, s64 *, 0x1D8) = (s64) M2C_FIELD(temp_a3, s64 *, 0);
    M2C_FIELD(arg0, s64 *, 0x1E0) = (s64) M2C_FIELD(temp_a3, s64 *, 8);
}
