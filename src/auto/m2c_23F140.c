#include "m2c_macros.h"

void *Battle_GetSetup();                            /* extern */
extern f32 D_00386CA4;

f32 func_0023F140(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return M2C_FIELD(Battle_GetSetup(r_a0), f32 *, 0x3C) * 10.0f * D_00386CA4;
}
