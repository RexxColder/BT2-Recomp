#include "m2c_macros.h"

void func_002E0F48(void *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    void *temp_a0;

    temp_a0 = arg0 + 0x14;
    *arg1 = M2C_FIELD(arg0, u8 *, 0x14);
    *arg2 = M2C_FIELD(temp_a0, u8 *, 1);
    *arg3 = M2C_FIELD(temp_a0, u8 *, 2);
}
