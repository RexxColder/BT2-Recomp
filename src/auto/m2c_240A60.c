#include "m2c_macros.h"

void *func_0023FFD8();                              /* extern */

s32  func_00240A60(unsigned long r_a0, unsigned long r_a1) { /* asm: a0, a1 arrive and pass through untouched */
    return (s8)(M2C_FIELD(func_0023FFD8(r_a0, r_a1), s8 *, 0x32));
}
