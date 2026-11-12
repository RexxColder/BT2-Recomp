#include "m2c_macros.h"

void *Battle_GetSetup();                            /* extern */
extern f32 D_00386C90;

f32 func_0023F048(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return M2C_FIELD(Battle_GetSetup(r_a0), f32 *, 0x34) * 10.0f * D_00386C90;
}
