#include "m2c_macros.h"

void *func_0023FFD8();                              /* extern */

f32 func_00240678(unsigned long r_a0, unsigned long r_a1) { /* asm: a0, a1 arrive and pass through untouched */
    return M2C_FIELD(func_0023FFD8(r_a0, r_a1), f32 *, 0x18) * 30.0f;
}
