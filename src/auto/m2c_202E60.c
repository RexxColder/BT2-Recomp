#include "m2c_macros.h"

s32 func_00202DA0();                                /* extern */

s32 func_00202E60(unsigned long r_a0, unsigned long r_a1) { /* asm: a0, a1 arrive and pass through untouched */
    return func_00202DA0(r_a0, r_a1) + 0x38;
}
