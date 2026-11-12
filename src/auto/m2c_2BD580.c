#include "m2c_macros.h"

s32 func_002F1ED0();                                /* extern */

s32 BtlSeq_IsFinish(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return func_002F1ED0(r_a0) == 4;
}
