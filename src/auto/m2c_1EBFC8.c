#include "m2c_macros.h"

extern void *D_0038790C;

void BtlPool_SetCurrent(s32 arg0) {
    M2C_FIELD(D_0038790C, s32 *, 0x64) = arg0;
}
