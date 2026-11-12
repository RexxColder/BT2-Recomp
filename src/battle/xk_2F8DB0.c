#include "m2c_macros.h"

void func_002F8DB0(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0x34) = arg1;
    M2C_FIELD(arg0, s16 *, 0x36) = arg2;
    M2C_FIELD(arg0, s16 *, 0x38) = arg3;
}
