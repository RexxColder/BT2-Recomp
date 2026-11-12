#include "m2c_macros.h"

s32 Gsc_FindTask();                                 /* extern */

s32 func_0029F6F8(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
    return Gsc_FindTask(r_a0) != 0;
}
