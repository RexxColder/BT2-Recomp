#include "m2c_macros.h"

void func_002E7D58(void *arg0, s16 arg1, s16 arg2, s16 arg3) {
    M2C_FIELD(arg0, s16 *, 0xA0) = arg1;
    M2C_FIELD(arg0, s16 *, 0xA2) = arg2;
    M2C_FIELD(arg0, s16 *, 0xA4) = arg3;
}
