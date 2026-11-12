#include "m2c_macros.h"

void *Battle_GetSetup();                            /* extern */
extern f32 D_00386CAC;

f32 func_0023F1B8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return (M2C_FIELD(Battle_GetSetup(r_a0), f32 *, 0x44) / 180.0f) * D_00386CAC;
}
