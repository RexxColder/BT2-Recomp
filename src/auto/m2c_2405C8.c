#include "m2c_macros.h"

void *func_0023FFD8();                              /* extern */
extern f32 D_00386CCC;

f32 func_002405C8(unsigned long r_a0, unsigned long r_a1) { /* asm: a0, a1 arrive and pass through untouched */
    return ((M2C_FIELD(func_0023FFD8(r_a0, r_a1), f32 *, 0x14) / 30.0f) / 180.0f) * D_00386CCC;
}
