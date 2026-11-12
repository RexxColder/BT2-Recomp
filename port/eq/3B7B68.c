#include "m2c_macros.h"

void *memset(void *, s32, u32);

void func_003B7B68(void *arg0, s32 arg1) {
    memset(arg0, 0, 0x18);
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}
