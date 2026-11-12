#include "m2c_macros.h"

s32 func_00101A88();                                /* extern */

/* Returns word 0x58 of record arg1 (0x58 bytes each) in the table from func_00101A88. */
s32 func_0010CD98(s32 arg0, s32 arg1) {
    return M2C_FIELD(((arg1 * 0x58) + func_00101A88(arg0)), s32 *, 0x58);
}
