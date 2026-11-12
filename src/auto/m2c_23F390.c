#include "m2c_macros.h"

void *Battle_GetSetup();                            /* extern */

s32  func_0023F390(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return (s8)(M2C_FIELD(Battle_GetSetup(r_a0), s8 *, 0x5C));
}
