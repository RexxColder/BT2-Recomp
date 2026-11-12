#include "m2c_macros.h"

void *func_0023FF80();                              /* extern */

s32  func_00240728(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return (s8)(M2C_FIELD(func_0023FF80(r_a0), s8 *, 0x24));
}
