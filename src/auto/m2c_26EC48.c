#include "m2c_macros.h"

M2C_UNK func_00270438(s32, s32 *, M2C_UNK);         /* extern */

/* asm: lw v0,0(a1); bltz; lw a0,0x1c(a0); j 0x270438 -- a1/a2 pass through (were dropped) */
void func_0026EC48(void *arg0, s32 *arg1, M2C_UNK arg2) {
    if (*arg1 >= 0) {
        func_00270438(M2C_FIELD(arg0, s32 *, 0x1C), arg1, arg2);
    }
}
