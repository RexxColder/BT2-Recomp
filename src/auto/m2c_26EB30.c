#include "m2c_macros.h"

void func_0026EB30(void *arg0, s32 arg1) {
    if (arg1 & 0xFF) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) & ~4);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(arg0, s32 *, 0x14) | 4);
}
