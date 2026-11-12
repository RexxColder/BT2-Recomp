#include "m2c_macros.h"

void func_002B1CA8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 0x2C) | arg1);
}
