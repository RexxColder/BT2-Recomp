#include "m2c_macros.h"

void func_002F3140(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (arg1 << 0xB);
}
