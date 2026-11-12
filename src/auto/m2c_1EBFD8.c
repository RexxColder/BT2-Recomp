#include "m2c_macros.h"

extern void *D_0038790C;

s32 BtlPool_GetCurrent(void) {
    return M2C_FIELD(D_0038790C, s32 *, 0x64);
}
