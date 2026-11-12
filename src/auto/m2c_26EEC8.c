#include "m2c_macros.h"

M2C_UNK func_00270568(s32, s32 *, s32, s32);   /* extern */

/* asm: lw v0,0(a1); bltz; lw a0,0x1c(a0); j 0x270568 -- a1..a3 pass through (were dropped) */
void func_0026EEC8(void *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    if (*arg1 >= 0) {
        func_00270568(M2C_FIELD(arg0, s32 *, 0x1C), arg1, arg2, arg3);
    }
}
