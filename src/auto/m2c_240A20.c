#include "m2c_macros.h"

void *BtlKiBlast_Get();                             /* extern */

s32  func_00240A20(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return (s8)(M2C_FIELD(BtlKiBlast_Get(r_a0), s8 *, 0x32));
}
