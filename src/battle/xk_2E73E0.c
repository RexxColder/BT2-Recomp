#include "m2c_macros.h"

void *memset(void *, s32, u32);                 /* extern */

void func_002E73E0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xCC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE0) = 0;
    M2C_FIELD(arg0, s16 *, 0xE2) = -0x80;
    M2C_FIELD(arg0, s16 *, 0xE4) = -0x80;
    memset(arg0 + 0xD0, 0, 0x10);
}
