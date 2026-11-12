#include "m2c_macros.h"

extern f32 D_00386CF4;

f32 func_00240DD0(void *arg0, s32 arg1) {
    return ((M2C_FIELD(((arg1 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x98C)), f32 *, 0x4C) * 10.0f * 1000.0f) / 3600.0f) * D_00386CF4;
}
