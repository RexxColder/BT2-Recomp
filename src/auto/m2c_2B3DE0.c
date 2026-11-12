#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B6700(M2C_UNK);                     /* extern */
s32 func_002CE500();                                /* extern */
extern M2C_UNK D_00377FC8 __attribute__((section(".data")));

void func_002B3DE0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    if (func_002CE500(r_a0) != 0) {
        func_002B6700(-0x132);
        Rand_Range(&D_00377FC8);
    }
}
