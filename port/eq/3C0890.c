#include "m2c_macros.h"

extern void *D_00421C98 __attribute__((section(".data")));

void func_003C0890(s32 arg0) {
    if (arg0 == 0) {
        M2C_FIELD(D_00421C98, s32 *, 0xCC) = 0;
        M2C_FIELD(D_00421C98, s32 *, 0xD0) = 0;
        M2C_FIELD(D_00421C98, s32 *, 0xD4) = 0;
        return;
    }
    M2C_FIELD(D_00421C98, s32 *, 0xD8) = 0;
    M2C_FIELD(D_00421C98, s32 *, 0xDC) = 0;
    M2C_FIELD(D_00421C98, s32 *, 0xE0) = 0;
}
