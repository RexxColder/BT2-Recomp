#include "m2c_macros.h"

void *func_0023FF80();                              /* extern */

f32 func_00240648(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return M2C_FIELD(func_0023FF80(r_a0), f32 *, 0x18) * 30.0f;
}
