#include "m2c_macros.h"

M2C_UNK func_002B6208();                            /* extern */
extern s32 D_00345340 __attribute__((section(".data")));

void func_002B6590(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    if (D_00345340 != 0) {
        D_00345340 = 0;
        func_002B6208(r_a0);
    }
}
