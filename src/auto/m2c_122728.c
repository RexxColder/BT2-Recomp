#include "m2c_macros.h"

void func_00122728(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | arg1);
}
