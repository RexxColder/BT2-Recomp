#include "m2c_macros.h"

s32 func_00240EA8(void *arg0, s32 arg1) {
    return (s32) M2C_FIELD(((arg1 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x98C)), s32 *, 0x70) / 30;
}
