#include "m2c_macros.h"

s32 func_002C23F8();                                /* extern */

s32 func_002C23D0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return func_002C23F8(r_a0) == 0x1BF;
}
