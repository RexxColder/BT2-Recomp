#include "m2c_macros.h"

void func_002B2388(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0x30) | arg1);
}
