#include "m2c_macros.h"

extern f32 D_00386CFC;
extern f32 D_00386D00;

f32 func_00240ED8(void *arg0, s32 arg1) {
    return (M2C_FIELD(((arg1 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x1530), s32 *, 0x98C)), f32 *, 0x7C) / 180.0f) * D_00386CFC * D_00386D00;
}
