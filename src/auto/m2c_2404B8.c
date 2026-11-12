#include "m2c_macros.h"

void *func_0023FF80();                              /* extern */
extern f32 D_00386CBC;

f32 func_002404B8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return M2C_FIELD(func_0023FF80(r_a0), f32 *, 0x10) * 10.0f * D_00386CBC;
}
