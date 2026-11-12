#include "m2c_macros.h"

M2C_UNK func_002B78B0();                            /* extern */
M2C_UNK func_002B78E8(M2C_UNK *);                   /* extern */
extern M2C_UNK func_002B26E8 __attribute__((section(".data")));

void func_002B26C0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    func_002B78B0(r_a0);
    func_002B78E8(&func_002B26E8);
}
