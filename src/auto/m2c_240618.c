#include "m2c_macros.h"

void *BtlKiBlast_Get();                             /* extern */

f32 func_00240618(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return M2C_FIELD(BtlKiBlast_Get(r_a0), f32 *, 0x18) * 30.0f;
}
