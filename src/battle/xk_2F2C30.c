#include "m2c_macros.h"

s32 func_002F2C30(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x1C) = arg1;
    M2C_FIELD(arg0, s32 *, 0x18) = arg2;
    return 1;
}
