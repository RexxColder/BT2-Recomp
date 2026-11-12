#include "m2c_macros.h"

void *BtlKiBlast_Get();                             /* extern */
extern f32 D_00386CB8;

f32 func_00240480(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return M2C_FIELD(BtlKiBlast_Get(r_a0), f32 *, 0x10) * 10.0f * D_00386CB8;
}
