#include "m2c_macros.h"

s32 func_00300150();                                /* extern */

s32 BtlSeq_IsFighting(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return func_00300150(r_a0) == 3;
}
