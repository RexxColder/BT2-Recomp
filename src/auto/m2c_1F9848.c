#include "m2c_macros.h"

s32 func_001F9670();                                /* extern */
extern void *D_00387930;

s32 func_001F9848(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return (s16) M2C_FIELD((((0x31 - func_001F9670(r_a0)) * 2) + M2C_FIELD(D_00387930, s32 *, 0x1C)), s16 *, 0x2BC) / 30;
}
