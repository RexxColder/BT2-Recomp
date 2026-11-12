#include "m2c_macros.h"

s32 func_002B81C8();                                /* extern */
s32 func_002BD618(s32);                             /* extern */

s32 func_002BD350(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return func_002BD618(func_002B81C8(r_a0)) != 1;
}
