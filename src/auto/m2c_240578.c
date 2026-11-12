#include "m2c_macros.h"

void *func_0023FF80();                              /* extern */
extern f32 D_00386CC8;

f32 func_00240578(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return ((M2C_FIELD(func_0023FF80(r_a0), f32 *, 0x14) / 30.0f) / 180.0f) * D_00386CC8;
}
