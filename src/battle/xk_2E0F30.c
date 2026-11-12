#include "m2c_macros.h"

void func_002E0F30(void *arg0, s8 arg1, s8 arg2, s8 arg3) {
    void *temp_a0;

    temp_a0 = arg0 + 0x14;
    M2C_FIELD(temp_a0, s8 *, 0) = arg1;
    M2C_FIELD(temp_a0, s8 *, 1) = arg2;
    M2C_FIELD(temp_a0, s8 *, 2) = arg3;
}
