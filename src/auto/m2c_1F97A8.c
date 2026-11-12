#include "m2c_macros.h"

s32 func_001F9530();                                /* extern */
extern void *D_00387930;

s32 func_001F97A8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return (s16) M2C_FIELD((((0x31 - func_001F9530(r_a0)) * 2) + M2C_FIELD(D_00387930, s32 *, 0x1C)), s16 *, 0x64) / 30;
}
